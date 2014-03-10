__author__ = 'Adam'

from application import Application

def main(args):
    projectDir = args[2]
    outputDir = args[3]

    print("Moving Assets")

    app = Application(projectDir)
    app.process(outputDir)

    return 0