import fs_fake
import os
from pyfakefs.fake_filesystem_unittest import Patcher
import pytest

def test_write_file():
    with Patcher() as patcher:
        fs_fake.write_file()
        assert os.path.exists(fs_fake.TESTFILE_TXT)
        fs_fake.dump_file()

def test_dump_file():
    with Patcher() as patcher:
        patcher.fs.create_file(fs_fake.TESTFILE_TXT, contents='test file content\nline #2\nlast line')
        assert os.path.exists(fs_fake.TESTFILE_TXT)
        fs_fake.dump_file()
        with open(fs_fake.TESTFILE_TXT, "r") as f:
            ls = list()
            for l in f:
                ls.append(l)
            ls_expected = ['test file content\n', 'line #2\n', 'last line']
            assert ls == ls_expected
