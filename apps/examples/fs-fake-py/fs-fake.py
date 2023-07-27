import os
import pytest
from pyfakefs.fake_filesystem_unittest import Patcher

TESTFILE_TXT= "testfile.txt"

def write_file():
    with open(TESTFILE_TXT, "w") as f:
        f.write("1st line\n")
        f.write("2nd\n")
        f.write("3rd\n")

def dump_file():
    with open(TESTFILE_TXT, "r") as f:
        print(f.read())

#######################################################################################################################

def test_write_file():
    with Patcher() as patcher:
        write_file()
        assert os.path.exists(TESTFILE_TXT)
        dump_file()

def test_dump_file():
    with Patcher() as patcher:
        patcher.fs.create_file(TESTFILE_TXT, contents='test file content\nline #2\nlast line')
        assert os.path.exists(TESTFILE_TXT)
        dump_file()
        with open(TESTFILE_TXT, "r") as f:
            ls = list()
            for l in f:
                ls.append(l)
            ls_expected = ['test file content\n', 'line #2\n', 'last line']
            assert ls == ls_expected

