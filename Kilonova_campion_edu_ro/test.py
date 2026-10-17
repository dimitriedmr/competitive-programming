from os import scandir, stat as os_stat, access, X_OK, listdir
from os.path import isfile, join, splitext, basename, abspath, dirname
from stat import S_IXUSR, S_IXGRP, S_IXOTH
from subprocess import run, CalledProcessError, PIPE, TimeoutExpired
from typing import List
from logging import basicConfig, getLogger, DEBUG
from shutil import copyfile, move
from time import time

# ANSI color codes
GREEN = "\033[92m"  # Bright green
RED = "\033[91m"  # Bright red
RESET = "\033[0m"  # Reset to default color
TIMEOUT = 1  # s
# Minimal logging setup
basicConfig(level=DEBUG, format="%(message)s")
logger = getLogger(__name__)


def find_input_files(script_dir: str, executable_name: str) -> List[str]:
    """Find input and expected output files in script_dir based on executable name."""
    input_file = [""]
    for f in sorted(listdir(script_dir)):
        full_path = join(script_dir, f)
        if isfile(full_path):
            if executable_name in f and "in" in f:
                if any(char.isdigit() for char in f):
                    input_file += [splitext(full_path)[0]]
    return input_file[1:]

def scan_subdirectories(base_dir: str) -> List[str]:
    """Recursively find subdirectories under base_dir."""
    subdirs = []
    for entry in scandir(base_dir):
        if entry.is_dir(follow_symlinks=False):
            subdirs.append(entry.path)
            subdirs.extend(scan_subdirectories(entry.path))
    return subdirs

def is_executable(file_path: str) -> bool:
    """Check if a file is executable."""
    if isfile(file_path) and access(file_path, X_OK):
        mode = os_stat(file_path).st_mode
        return bool(mode & (S_IXUSR | S_IXGRP | S_IXOTH))
    return False

def process_subdirectories():
    """Find executable in subdirectories and run comparison."""
    script_dir = dirname(abspath(__file__))
    subdirs = scan_subdirectories(script_dir)

    for subdir in subdirs:
        files = [f.name for f in scandir(subdir) if f.is_file()]
        sorted_files = sorted(files)
        index = 0
        exe_path = None
        while index < len(sorted_files) and exe_path is None:
            candidate_path = join(subdir, sorted_files[index])
            if is_executable(candidate_path):
                exe_path = candidate_path
            index += 1
        if exe_path:
            break
    executable_name = (splitext(basename(exe_path))[0]).split("_")[1]
    input_file_paths = find_input_files(script_dir, executable_name)
    return exe_path, input_file_paths

def compare(var1, var2) -> bool:
    """
    Compare two variables.
    Supports str and bytes inputs.
    """
    fail = 0
    msg1 = ""
    msg2 = ""
    str1 = ""
    str2 = ""
    # Convert bytes to string using UTF-8 decoding
    if isinstance(var1, bytes):
        str1 = var1.decode("utf-8", errors="ignore")
    else:
        str1 = var1
    if isinstance(var2, bytes):
        str2 = var2.decode("utf-8", errors="ignore")
    else:
        str2 = var2
    str1 = " ".join(str1.split())
    str2 = " ".join(str2.split())
    len1 = len(str1)
    len2 = len(str2)
    i = 0
    j = 0
    while i < len1 and j < len2:
        msg1 += str1[i]
        if str1[i] == str2[j]:
            msg2 += f"{GREEN}{str2[j]}{RESET}"
        else:
            fail += 1
            msg2 += f"{RED}{str2[j]}{RESET}"
        i += 1
        j += 1
    while i < len1:
        msg1 += str1[i]
        i += 1
    while j < len2:
        msg2 += str2[j]
        j += 1
    logger.info(msg1)
    logger.info(msg2)
    return (fail != 0)

def execute(exe_path: str, input_file_paths:List[str]) -> None:
    """Execute the executable with the input file as stdin and compare output."""
    passed = 0
    failed = 0
    exe_input_path = input_file_paths[0]
    exe_input_path = join(dirname(exe_input_path), basename(exe_input_path).split('-')[1])
    exe_output_path = exe_input_path
    exe_input_path += ".in"
    exe_output_path += ".out"
    for i, input in enumerate(input_file_paths[::-1]): # in reverse, to finalize with test no. 0 (example input)
        test_file_path = input + ".in"
        copyfile(test_file_path, exe_input_path)
        expected_file_path = input + ".out"
        msg = f"#{i}\t"
        fail = 0
        if not isfile(exe_path):
            msg += "Exe file is missing"
            fail += 1
        if not isfile(expected_file_path):
            msg += "Output file is missing"
            fail += 1
        if not isfile(test_file_path):
            msg += "Input file is missing"
            fail += 1
        logger.info(msg +
            basename(exe_path)
            + " "
            + basename(test_file_path)
            + " "
            + basename(expected_file_path))

        if not fail:
            output_data = ""
            expected_data = ""
            try:
                with open(expected_file_path, "r") as ef:
                    expected_data = ef.read()
                start_time = time()
                result = run(
                    [exe_path],
                    stdout=PIPE,
                    stderr=PIPE,
                    check=True,
                    timeout=TIMEOUT,
                    text=True,
                )
                end_time = time()
                msg = f"{end_time - start_time:.2f} s\t"

                output_data = result.stdout
                if len(output_data) < 1:
                    with open(exe_output_path, "r") as ef:
                        output_data = ef.read()
                        
            except CalledProcessError as e:
                msg = "Execution failed" + f"{e}"
                fail += 1
            except TimeoutExpired:
                msg = f"TLE {TIMEOUT=}s"
                fail += 1
            except Exception as e:
                msg = f"{e}"
                fail += 1
            if fail:
                logger.error(f"{RED}{msg}{RESET}")
            else:
                logger.info(msg)
                fail += compare(expected_data, output_data)
                if fail:
                    logger.error(f"{RED}WA{RESET}")
            if fail:
                failed += 1
            else:
                passed += 1
    logger.info(f"Tests {passed=}, {failed=}\t time is 10x that website")
            
if __name__ == "__main__":
    try:
        """
        expected files: 
        <number>_<name>.cpp <number>_<name>.exe; e.g. 2911_cofetar.cpp 
        I/O files to executable: <name>.in; <name>.out
        kilonova files after one submission: <testNbr>-<name>.in; <testNbr>-<name>.out
        use cmake to test 1st time
        """
        exe_path, input_file_paths = process_subdirectories()
        # Move the file to the root directory
        new_exe_path = join(dirname(dirname(exe_path)), basename(exe_path))
        move(exe_path, new_exe_path)
        execute(new_exe_path, input_file_paths)
    except Exception as e:
        logger.info(f"{e}")
