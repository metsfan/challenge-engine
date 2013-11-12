__author__ = 'Adam'

import sys
import os
from xml.dom import minidom

class VS2012Project:

    def __init__(self, filename):
        self.filename = filename
        self.document = minidom.parse(filename)
        self.root = self.document.getElementsByTagName("Project")[0]

    def addBuildScript(self, command):


        # Get all ItemDefinitionGroup nodes
        itemDefinitionGroup = self.root.getElementsByTagName("ItemDefinitionGroup")

        for item in itemDefinitionGroup:
            # If PostBuildEvent doesn't exist, create it
            postBuildNode = item.getElementsByTagName("PostBuildEvent")
            if postBuildNode.length == 0:
                postBuildNode = self.document.createElement("PostBuildEvent")
                item.appendChild(postBuildNode)
            else:
                postBuildNode = postBuildNode[0]


            # If Command node doesn't exist, create it
            commandNode = postBuildNode.getElementsByTagName("Command")
            commandText = ""
            if commandNode.length == 0:
                commandNode = self.document.createElement("Command")
                postBuildNode.appendChild(commandNode)
            else:
                # If Command node exists, add new line for new command node
                commandNode = commandNode[0]
                if commandNode.childNodes.length > 0:
                    commandText = "\n"

            # Create new text node
            commandText += command
            textNode = self.document.createTextNode(commandText)
            commandNode.appendChild(textNode)

    def addIncludeDirectory(self, directory):
        itemDefinitionGroup = self.root.getElementsByTagName("ItemDefinitionGroup")

        for item in itemDefinitionGroup:
            clCompileNode = item.getElementsByTagName("ClCompile")[0]
            includesNode = clCompileNode.getElementsByTagName("AdditionalIncludeDirectories")
            if includesNode.length == 0:
                includesNode = self.document.createElement("AdditionalIncludeDirectories")
                clCompileNode.appendChild(includesNode)
            else:
                includesNode = includesNode[0]

            includesNode.appendChild(self.document.createTextNode(";" + directory))



    def write(self):
        # Write to file
        self.document.writexml(open(self.filename, "w"))

