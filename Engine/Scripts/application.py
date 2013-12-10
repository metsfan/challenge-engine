__author__ = 'Adam'

import os;
from xml.dom import minidom

class Application:

    def __init__(self, projectDir):
        self.projectDir = projectDir

    def process(self, outDir):
        self.loadStrings()
        self.processLayout(outDir)

    def loadStrings(self):
        self.strings = {}

        stringsDir = self.projectDir + "/" + "Resources/Strings"

        files = os.listdir(stringsDir)
        for file in files:
            filepath = stringsDir + "/" + file;
            if os.path.isfile(filepath):
                doc = minidom.parse(filepath)
                if doc:
                    root = doc.getElementsByTagName("Strings")
                    if root.length == 1:
                        root = root[0]

                        strings = root.getElementsByTagName("String")

                        for string in strings:
                            name = string.getAttribute("name")
                            value = string.getAttribute("value")

                            if len(name) > 0 and len(value) > 0:
                                self.strings[name] = value

    def processLayout(self, outDir):
        layoutDir = self.projectDir + "/Resources/Layout"

        files = os.listdir(layoutDir)
        for file in files:
            filepath = layoutDir + "/" + file
            if os.path.isfile(filepath):
                fileContents = open(filepath).read()

                for name, value in self.strings.items():
                    fileContents = fileContents.replace("$" + name, value)

                outFilepath = outDir + "/" + file
                outfile = open(outFilepath, "w")
                outfile.write(fileContents)
                outfile.close()

    def processConfig(self, outDir):
        configDir = self.projectDir + "/Resources/Config"

        files = os.listdir(configDir)
        for file in files:
            filepath = configDir + "/" + file
            if os.path.isfile(filepath):
                fileContents = open(filepath).read()

                outFilepath = outDir + "/" + file
                outfile = open(outFilepath, "w")
                outfile.write(fileContents)
                outfile.close()