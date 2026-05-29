import fs_fake
import os
from pyfakefs.fake_filesystem_unittest import Patcher


def test_write_file():
    with Patcher():
        fs_fake.write_file()
        assert os.path.exists(fs_fake.TESTFILE_TXT)
        fs_fake.dump_file()


def test_dump_file():
    with Patcher() as patcher:
        patcher.fs.create_file(
            fs_fake.TESTFILE_TXT, contents="test file content\nline #2\nlast line"
        )
        assert os.path.exists(fs_fake.TESTFILE_TXT)
        fs_fake.dump_file()
        with open(fs_fake.TESTFILE_TXT) as f:
            ls = list()
            for line in f:
                ls.append(line)
            ls_expected = ["test file content\n", "line #2\n", "last line"]
            assert ls == ls_expected
