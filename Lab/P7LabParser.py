"""
Example of output
---- Run Report ----
Description                  Time Taken (ms) Time Taken (%) Notes
Finding reformulator         0.00            0.00                
Parsing PDDL Files           0.00            0.00                
Converison of PDDL format    0.00            0.00                
Solving Problem              650.00          98.93               
 Iteration 1                  650.00          100.00              
  Reformulation of PDDL        518.00          79.82               
   Walking                      502.00          97.10               
   Finding Entanglements        12.00           2.32                
   Generating Macros            3.00            0.58                
  Generating PDDL              6.00            0.92                
  Running FastDownward         125.00          19.26               
Validating reformulated plan 4.00            0.61           true 
Parse SAS plan               0.00            0.00                
Rebuild SAS plan             0.00            0.00                
Output SAS plan              0.00            0.00                
Validating rebuilded plan    3.00            0.46           true 
Total Time                   657.000
search time limit missing -> can't compute time scores
search memory limit missing -> can't compute memory score
planner_time_limit missing -> can't compute planner time score
planner_memory_limit missing -> can't compute planner memory score

"""

import re
from lab.parser import Parser

def get_times(content, props):
    """
    Only care about the ouput of P7 from:

    Description Time Taken (ms) Time Taken (%)
    ...
    Total Time
    """
    results = content.split("Notes\n")[1].split("Total Time")[0]

    results = re.findall(r"(([a-zA-Z\s0-9]+)\s+(\d+\.\d+)\s+(\d+\.\d+)\s+([a-zA-Z\s0-9]+)\n)",results)

    #The iterations have the same name so the values from all iterations are seperated by a comma and placed in the same cell.
    for result in results:
        description = "p7_" + result[1].strip().lower().replace(" ","_")
        if description + "_ms" in props:
            props[description + "_ms"] += ", " + result[2]
        else:
            props[description + "_ms"] = result[2]

        if description + "_procent" in props:
            props[description + "_procent"] += ", " + result[3]
        else:
            props[description + "_procent"] = result[3]

        if len(result) > 3:
            if description + "_notes" in props:
                props[description + "_notes"] += ", " + result[4]
            else:
                props[description + "_notes"] = result[4]


parser = Parser()
parser.add_function(get_times, file="run.log")
parser.parse()
