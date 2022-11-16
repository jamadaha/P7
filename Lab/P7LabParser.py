"""
Example of output
---- Run Report ----
Description                  Time Taken (ms) Time Taken (%) Notes Int Values Bool Values
Finding reformulator         0.00            0.00           None  -1         None       
Checking Filepaths           0.00            0.00           None  -1         None       
Parsing PDDL Files           1.00            0.09           None  -1         None       
Converison of PDDL format    0.00            0.00           None  -1         None       
Solving Problem              1046.00         98.49          None  -1         true       
 Reformulation of PDDL        904.00          86.59          None  -1         None       
  Walking                      902.00          99.89          None  -1         None       
  Finding Entanglements        1.00            0.11           None  -1         None       
 Generating PDDL              0.00            0.00           None  -1         None       
 Running FastDownward         140.00          13.41          None  -1         None       
Validating reformulated plan 7.00            0.66           None  -1         true       
Parse SAS plan               1.00            0.09           None  125        None       
Rebuild SAS plan             0.00            0.00           None  125        None       
Macros Used                  0.00            0.00           None  0          None       
Output SAS plan              0.00            0.00           None  -1         None       
Validating rebuilded plan    7.00            0.66           None  -1         true       
Total Time                   1062.000

"""

import re
from lab.parser import Parser

ATTRIBUTES_NAME_MAP = [
    ('p7_solving_problem_ms', 'reformulation_time'),
    ('p7_validating_reformulated_plan_boolvalues', 'reformulated_plan_valid'),
    ('p7_validating_rebuilded_plan_boolvalues', 'rebuild_plan_valid'),
    ('p7_solving_problem_boolvalues', 'solvable'),
    ('p7_plan_length_difference_intvalues', 'plan_length_difference'),
    ('p7_macros_generated_intvalues', 'macros_generated'),
    ('p7_macros_used_intvalues', 'macros_used')
]

def get_times(content, props):
    """
    Only care about the ouput of P7 from:

    Description Time Taken (ms) Time Taken (%)
    ...
    Total Time
    """
    results = content.split("Values\n")[1].split("Total Time")[0]

    results = re.findall(r"(([a-zA-Z\s0-9]+)\s+(\d+\.\d+)\s+(\d+\.\d+)\s+([a-zA-Z\s]+)\s+([-0-9]+)\s+([a-zA-Z]+)\s+\n)",results)

    #The iterations have the same name so the values from all iterations are seperated by a comma and placed in the same cell.
    for result in results:
        description = "p7_" + result[1].strip().lower().replace(" ","_")
        checkName = check_map_name(description + "_ms")
        counter = 0
        while checkName in props:
            checkName = description + "_ms" + str(counter)
            counter += 1
        props[checkName] = float(result[2])

        checkName = check_map_name(description + "_procent")
        counter = 0
        while checkName in props:
            checkName = description + "_procent" + str(counter)
            counter += 1
        props[checkName] = result[3]

        note = result[4].strip()
        checkName = check_map_name(description + "_notes")
        counter = 0
        while checkName in props:
            checkName = description + "_notes" + str(counter)
            counter += 1
        props[checkName] = note

        note = result[5].strip()
        checkName = check_map_name(description + "_intvalues")
        counter = 0
        while checkName in props:
            checkName = description + "_intvalues" + str(counter)
            counter += 1
        props[checkName] = int(note)

        note = result[6].strip()
        checkName = check_map_name(description + "_boolvalues")
        counter = 0
        while checkName in props:
            checkName = description + "_boolvalues" + str(counter)
            counter += 1
        if note.upper() == "TRUE":
            props[checkName] = True
        else:
            props[checkName] = False

    check_errors(props)

def check_map_name(name):
    for target, newName in ATTRIBUTES_NAME_MAP:
        if target == name:
            return newName
    return name

def check_errors(props):
    if "reformulated_plan_valid" in props:
        if props["reformulated_plan_valid"] == False:
            props.add_unexplained_error("Reformulated plan was not valid!")
    if "rebuild_plan_valid" in props:
        if props["rebuild_plan_valid"] == False:
            props.add_unexplained_error("Rebuild plan was not valid!")

parser = Parser()
parser.add_function(get_times, file="run.log")
parser.parse()
