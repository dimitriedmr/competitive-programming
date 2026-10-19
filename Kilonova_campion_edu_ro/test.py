from logging import basicConfig, getLogger, DEBUG
from os import access, X_OK, scandir, stat
from os.path import abspath, expanduser, isfile, join, splitext, basename,  dirname
from shutil import copyfile
from stat import S_IXUSR, S_IXGRP, S_IXOTH
from subprocess import run, CalledProcessError, PIPE, TimeoutExpired, CompletedProcess
from time import time
from typing import Tuple, List

# ANSI color codes
GREEN = "" #"\033[92m"  # Bright green
RED = "" #"\033[91m"  # Bright red
RESET = "" #"\033[0m"  # Reset to default color

# Minimal logging setup
basicConfig(level=DEBUG, format="%(message)s")
logger = getLogger(__name__)


class Test:

    def __init__(self, name:str = ''):
        self.dir_path = dirname(abspath(__file__))
        self.project_name = name # overide when <project_name>.in file isn't used
        self._f_in = ".in"
        self._f_out = ".out"
        self.build_dir = "build" # subdir of dir_path
        self.exe_path = ""
        self._timeout = 1  # s
        self.exe_out_f_path = ""
        self.exe_in_f_path = ""
        self.tests_dir = "Downloads"
        self.tests_paths: List[str] = []

    def _get_tests(self):
        """
        Find test (input&output) files.
        """
        for entry in scandir(join(expanduser("~"), self.tests_dir)):
            if isfile(entry.path) and self._f_in in entry.name:
                if any(char.isdigit() for char in entry.name):
                    self.tests_paths += [splitext(entry.path)[0]] # remove extension

    def _get_exe(self):
        """
        Find executable in build dir and tests. 
        """
        build_subdir_path = ""
        for entry in scandir(self.dir_path):
            if self.build_dir in entry.name and entry.is_dir():
                build_subdir_path = entry.path
                for subentry in scandir(entry.path):
                    if (subentry.is_file() and access(subentry.path, X_OK) and
                        stat(subentry.path).st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)):
                            self.exe_path = subentry.path
            if not self.project_name and isfile(entry.path) and self._f_in in entry.name:
                self.project_name = splitext(entry.name)[0] # remove extension
        assert build_subdir_path == join(self.dir_path, self.build_dir), "build directory not found. do build!"
        assert len(self.exe_path) > 1, "executable isn't found. do clean, rebuild!"

        self.exe_out_f_path = join(self.dir_path, self.project_name + self._f_out)
        self.exe_in_f_path = join(self.dir_path, self.project_name + self._f_in)

    def _execute(self) -> Tuple[int, str]:
        """
        Run an executable and calculate its execution time.
        """
        result: CompletedProcess[str] | str
        fail = 0
        try:
            start_time = time()
            result = run(
                [self.exe_path],
                stdout=PIPE,
                stderr=PIPE,
                check=True,
                timeout=self._timeout,
                text=True,
            )
            end_time = time()
            logger.info(f"Elapsed time: {end_time - start_time:.2f} s\t")
            result = result.stdout
        except CalledProcessError as e:
            result = f"Execution failed {e}\n"
            fail += 1
        except TimeoutExpired:
            result = f"TLE {self._timeout=}s"
            fail += 1
        except Exception as e:
            result = f"Exception{e}\n"
            fail += 1
        return fail, result

    def _compare(self, var1: str | bytes, var2: str | bytes) -> bool:
        """
        Compare two str or bytes str inputs.
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
        return fail != 0

    def _execute_and_compare(self) -> None:
        """
        Run an executable with the input file as stdin and compare its output.
        """
        passed = 0
        failed = 0

        self.tests_paths = self.tests_paths[
            ::-1
        ]  # revers to finalize with example input, #0

        for i, entry in enumerate(self.tests_paths):
            msg = f"#{i}\t{basename(self.exe_path)} "
            fail = 0

            test_in_f_path = entry + self._f_in
            assert isfile(test_in_f_path), "issue with input file"
            copyfile(test_in_f_path, self.exe_in_f_path)  # override
            msg += f"{basename(test_in_f_path)} "

            test_out_f_path = entry + self._f_out 
            expected_data = ""
            if not isfile(test_out_f_path):
                test_out_f_path = "" # output can be to stdout
            else:
                fout = open(test_out_f_path, "r")
                expected_data = fout.read()
                fout.close()
            msg += f"{basename(test_out_f_path)} "

            logger.info(msg)

            fail, msg = self._execute()

            if fail:
                logger.error(f"{RED}{msg}{RESET}")
            else:
                output_data = msg
                if len(output_data) < 1:
                    # if output isn't present in stdout, open out file
                    fout = open(self.exe_out_f_path, "r")
                    output_data = fout.read()
                    fout.close()

                fail += self._compare(expected_data, output_data)
                if fail:
                    logger.error(f"{RED}WA{RESET}")

            if fail:
                failed += 1
            else:
                passed += 1

        logger.info(f"Tests {passed=}, {failed=}")

    def run(self):

        self._get_tests()
        
        self._get_exe()

        if len(self.tests_paths) > 0:
            self._execute_and_compare()
        else:
            self._execute()
        logger.info("Note: elapsed time is higher than that shown on website.")


if __name__ == "__main__":
    """
    expected project tree:
    ./<project_name>.in
    ./<<number>_><name>.cpp <- e.g. 2911_cofetar.cpp or main.cpp; any name
    ./build/<number>_<name>.exe
    ./<project_name>.in  <- for Test() it is needed if, or Test(<project_name>)
    ./<project_name>.out <- it is created
    
    optional:
    <testNbr>-<name>.in
    <testNbr>-<name>.out
    I/O files related to executable, files are taken after one submission from kilonova.
    
    use cmake to build
    """
    try:
        Test().run()
    except Exception as e:
        logger.info(f"Error: {e}")
