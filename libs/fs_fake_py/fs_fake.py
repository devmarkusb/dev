TESTFILE_TXT = "testfile.txt"

def write_file():
    with open(TESTFILE_TXT, "w") as f:
        f.write("1st line\n")
        f.write("2nd\n")
        f.write("3rd\n")

def dump_file():
    with open(TESTFILE_TXT, "r") as f:
        print(f.read())
