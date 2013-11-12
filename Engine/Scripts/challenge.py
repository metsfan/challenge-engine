__author__ = 'Adam'

import sys
import build
import create
import help

def main(args):
    command = ""
    if len(args) > 1 :
        command = args[1]

    if command == "create":
        return create.main(args)
    elif command == "build":
        return build.main(args)
    else:
        return help.main(args)

if __name__ == "__main__":
    main(sys.argv)