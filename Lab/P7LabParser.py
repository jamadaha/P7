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
    ('p7_macros_used_intvalues', 'macros_used'),
    ('p7_unique_macros_used_intvalues', 'unique_macros_used'),
    ('p7_verifying_macros_boolvalues', 'macros_valid'),
    ('p7_verifying_paths_boolvalues', 'paths_valid'),
    ('p7_total_walker_paths_intvalues', 'total_walker_paths'),
    ('p7_total_walker_actions_generated_intvalues', 'total_walker_actions_generated'),
    ('p7_average_branching_factor_intvalues', 'walker_average_branching_factor'),
    ('p7_median_branching_factor_intvalues', 'walker_median_branching_factor'),
    ('p7_average_path_length_intvalues', 'walker_average_path_length'),
    ('p7_median_path_length_intvalues', 'walker_median_path_length'),
    ('p7_used_heuristic_notes','walker_heuristic'),
    ('p7_total_walker_time','walker_total_time'),
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
        generate_prop(description + "_ms", float(result[2]), props)
        generate_prop(description + "_procent", result[3], props)
        generate_prop(description + "_notes", result[4].strip(), props)
        generate_prop(description + "_intvalues", int(result[5].strip()), props)
        if result[6].strip().upper() == "TRUE":
            generate_prop(description + "_boolvalues", True, props)
        if result[6].strip().upper() == "FALSE":
            generate_prop(description + "_boolvalues", False, props)

def generate_prop(name, value, props):
    newName = name
    for target, replaceWith in ATTRIBUTES_NAME_MAP:
        if target in name:
            newName = replaceWith
            break

    check_errors(newName, value, props)

    counter = 1
    checkName = newName
    while checkName in props:
        checkName = newName + "_" + str(counter)
        counter += 1

    props[checkName] = value

def check_errors(name, value, props):
    if name == "reformulated_plan_valid":
        if value == False:
            props.add_unexplained_error("Reformulated plan was not valid!")
    if name == "rebuild_plan_valid":
        if value == False:
            props.add_unexplained_error("Rebuild plan was not valid!")
    if name == "macros_valid":
        if value == False:
            props.add_unexplained_error("Invalid macros was generated!")
    if name == "paths_valid":
        if value == False:
            props.add_unexplained_error("Invalid paths was generated!")

parser = Parser()
parser.add_function(get_times, file="run.log")
parser.parse()
