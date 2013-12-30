__author__ = 'Adam'

import os
from vs2012 import VS2012Project


def main(args):
    print("Creating new application")

    appName = args[2]
    print("App Name: ", appName)

    platform = args[3]

    enginePath = os.path.normpath(os.path.dirname(__file__) + "/..")
    scriptPath = os.path.dirname(__file__)

    directories = ("Source",
                   "Assets",
                   "Resources",
                   "Resources/Config",
                   "Resources/Layout",
                   "Resources/Strings",
                   "Resources/Shaders")

    if platform == "vs2012":
        projectFilePath = appName + "\\" + appName + ".vcxproj"

        if os.path.exists(projectFilePath):
            print("Project found!")
            project = VS2012Project(projectFilePath)

            scriptFile = scriptPath + "\\challenge build"
            project.addBuildScript(scriptFile + " $(ProjectDir) $(TargetDir)")

            project.addIncludeDirectory(enginePath + "\\Source")

            project.write()

            for dir in directories:
                newDir = appName + "\\" + dir
                if not(os.path.exists(newDir)):
                    os.mkdir(appName + "\\" + dir)

            print("Success!")
        else:
            print("Project not found! Exiting")