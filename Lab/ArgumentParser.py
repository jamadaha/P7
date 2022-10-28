from lab.experiment import ARGPARSER

import os

def set_arguments():
    ARGPARSER.add_argument(
        "--settings",
        required=True,
        help="Settings for P7"
    )

    return ARGPARSER.parse_args()

def abs_path(filelocation,filename):
    return os.path.join(os.path.dirname(os.path.abspath(filelocation)),filename)

#If argument is none the defaultargument will be used instead
def get_from_argument(argument, filelocation, defaultargument):
    if argument:
        return abs_path(filelocation, argument)
    else:
        return abs_path(filelocation, defaultargument)