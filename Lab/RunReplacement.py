counter = 0
counterMax = 0

def Update(*a):
    global counter
    counter += 1
    logging.info("Finished (" + str(counter) + "/" + str(counterMax) + ")")

import logging
import os
import multiprocessing
import subprocess
import sys

from lab.experiment import get_run_dir
from lab import tools

tools.configure_logging()

SHUFFLED_TASK_IDS = []

# Make sure we're in the experiment directory.
os.chdir(os.path.dirname(os.path.abspath(__file__)))


def get_run_id(task_id):
    return SHUFFLED_TASK_IDS[task_id - 1]


def process_task(task_id):
    run_id = get_run_id(task_id)
    run_dir = get_run_dir(run_id)
    error = False
    driver_log_file = os.path.join(run_dir, "driver.log")

    if os.path.exists(driver_log_file):
        logging.info(f"The run in {run_dir} has already been started --> skip it")
        return False

    with open(driver_log_file, "w") as driver_log:
        with open(os.path.join(run_dir, "driver.err"), "w") as driver_err:
            logging.info(f"Starting run {run_id} (TASK_ID {task_id}) in {run_dir}")
            try:
                subprocess.check_call(
                    [tools.get_python_executable(), "run"],
                    cwd=run_dir, stdout=driver_log, stderr=driver_err)
            except subprocess.CalledProcessError:
                error = True

    # driver.log always has content for a successful run, so we never delete it.
    if os.path.getsize(driver_err.name) == 0:
        os.remove(driver_err.name)
    else:
        error = True

    return error


def main():
    pool = multiprocessing.Pool(processes=12)
    num_tasks = len(SHUFFLED_TASK_IDS)
    global counterMax
    counterMax = num_tasks
    for num in range(1,num_tasks + 1):
        result = pool.apply_async(process_task, (num,), callback=Update)
    pool.close()
    logging.info("Joining pool processes")
    pool.join()


if __name__ == "__main__":
    main()
