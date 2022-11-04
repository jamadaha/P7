"""
Example of output
-------------------------
Running reformulator...
        INFO:  Finding reformulator algorithm...
        INFO:  Parsing PDDL files...
        INFO:  Converting PDDL format...
        INFO:  Reformulating PDDL...
        INFO:  Generating PDDL files...
        INFO:  Run new PDDL files with Fast Downward...
        INFO:  Parsing SAS Plan...
        INFO:  Rebuilding the SAS plan...
        INFO:  Output new SAS Plan...
Done!
---- Time Taken ----
Description               Time Taken (ms) Time Taken (%)
Finding Reformulator      0.974           0.125
Converison of PDDL format 0.854           0.109
Reformulation of PDDL     571.771         73.216
Generating PDDL           1.137           0.146
Running FastDownward      205.787         26.351
Parse SAS plan            0.253           0.032
Rebuild SAS plan          0.017           0.002
Output SAS plan           0.140           0.018
Total Time                780.934

Example of output with debug
---------------------------------
Running reformulator...
        INFO:  Finding reformulator algorithm...
(DEBUG) INFO:  Checking filepaths from the config...
        INFO:  Parsing PDDL files...
        INFO:  Converting PDDL format...
        INFO:  Reformulating PDDL...
(DEBUG) INFO:  	Walking
(DEBUG) INFO:  	|                                                  |
(DEBUG) INFO:  	 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

(DEBUG) INFO:  	[Walker] Total walk time:         500ms
(DEBUG) INFO:  	[Walker] Total walker iterations: 325 [650.000000/s]
(DEBUG) INFO:  	[Walker] Total actions Generated: 17296 [34592.000000/s]
(DEBUG) INFO:  	Finding Entanglements (level 31)
(DEBUG) INFO:  	|                                                  |
(DEBUG) INFO:  	 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

(DEBUG) INFO:  	Finding Entanglements (level 16)
(DEBUG) INFO:  	|                                                  |
(DEBUG) INFO:  	 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

(DEBUG) INFO:  	Finding Entanglements (level 8)
(DEBUG) INFO:  	|                                                  |
(DEBUG) INFO:  	 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
(DEBUG) INFO:  	Finding Entanglements (level 4)
(DEBUG) INFO:  	|                                                  |
(DEBUG) INFO:  	 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
(DEBUG) INFO:  	Finding Entanglements (level 2)
(DEBUG) INFO:  	|                                                  |
(DEBUG) INFO:  	 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
(DEBUG) INFO:  	[Entanglement Finder] Total search time:         74ms
(DEBUG) INFO:  	[Entanglement Finder] Found a total of 92 candidates out of 325 paths that has 3386 steps
        INFO:  Generating PDDL files...
        INFO:  Run new PDDL files with Fast Downward...
(DEBUG) INFO:  Validate reformulated SAS plan...
        INFO:  Parsing SAS Plan...
        INFO:  Rebuilding the SAS plan...
        INFO:  Output new SAS Plan...
(DEBUG) INFO:  Validate new SAS plan...
Done!
---- Time Taken ----
Description                      Time Taken (ms) Time Taken (%)
Finding Reformulator             0.003           0.000
Checking Filepaths               0.825           0.115
Converison of PDDL format        0.486           0.068
Reformulation of PDDL            576.779         80.662
Generating PDDL                  1.304           0.182
Running FastDownward             127.046         17.767
Validating reformulated SAS plan 3.962           0.554
Parse SAS plan                   0.263           0.037
Rebuild SAS plan                 0.018           0.003
Output SAS plan                  0.138           0.019
Validate new SAS plan            4.234           0.592
Total Time                       715.058
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
    results = content.split("(%)\n")[1].split("Total Time")[0]

    results = re.findall(r"(([a-zA-Z\s0-9]+)\s+(\d+\.\d+)\s+(\d+\.\d+))",results)

    #The iterations have the same name so the values from all iterations are seperated by a comma and placed in the same cell.
    for result in results:
        description = result[1].strip().lower().replace(" ","_")
        if description + "_ms" in props:
            props[description + "_ms"] += ", " + result[2]
        else:
            props[description + "_ms"] = result[2]
        if description + "_procent" in props:
            props[description + "_procent"] += ", " + result[3]
        else:
            props[description + "_procent"] = result[3]

parser = Parser()
parser.add_function(get_times, file="run.log")
parser.parse()
