// ModelReader.cpp : Defines the entry point for the console application.
//

#include "Globals.h"
#include "Model.h"

void write_model(std::string &inFile, std::string &outFile)
{
	std::cout << "Reading model file.\n";
	try {
		glm::mat4 transform = glm::rotate(glm::mat4(), 90.0f, glm::vec3(1.0f, 0.0, 0.0f));
		model::Model model(inFile, glm::mat4());
		
		std::cout << "Writing to output file.\n";
		std::ofstream outStream(outFile, std::ios::out | std::ios::binary);
		model.Serialize(outStream);

		std::cout << "Done!\n";
	} catch(const char *e) {
		std::cout << "ERROR: " << e << "\n";
		std::cout << "\n";
	}


}

int main(int argc, char* argv[])
{
	std::string inFile, outFile;

	std::cout << "=== Challenge Engine Model Converter ====\n";
	std::cout << "Convert any 3D model format supported by assimp (http://assimp.sourceforge.net/) into a compressed binary file to be used with the challenge engine. \n";
	std::cout << "\n\n";

	while(true) {
		std::cout << "Please enter a command: \n";
		std::cout << "1: Convert file\n";
		std::cout << "2: Help\n";
		std::cout << "3: Exit\n\n";
		int command = 4;
		//std::cin >> command;
		std::cout << "\n";
		if(command == 1) {
			std::cout << "Enter input filepath: \n";
			std::cin >> inFile;
			std::cout << "\n";

			std::cout << "Enter output filepath: \n";
			std::cin >> outFile;
			std::cout << "\n";

			write_model(inFile, outFile);
			break;
		} else if(command == 2) {
			std::cout << "Nothing here yet!\n\n";
		} else if(command == 3) {
			break;
		} else if(command == 4) { // Debug mode
			inFile = "C:/gamedev/engine-dev/Engine/ModelReader/Assets/dark_mage_maya.dae";
			outFile = "C:/gamedev/engine-dev/Engine/ModelReader/Assets/dark_mage.model";
			write_model(inFile, outFile);
			/*inFile = "C:/gamedev/engine-dev/Engine/ModelReader/Assets/sphere.dae";
			outFile = "C:/gamedev/engine-dev/Engine/ModelReader/Assets/sphere.model";
			write_model(inFile, outFile);

			inFile = "C:/gamedev/engine-dev/Engine/ModelReader/Assets/box.dae";
			outFile = "C:/gamedev/engine-dev/Engine/ModelReader/Assets/box.model";
			write_model(inFile, outFile);

			inFile = "C:/gamedev/engine-dev/Engine/ModelReader/Assets/cylinder.dae";
			outFile = "C:/gamedev/engine-dev/Engine/ModelReader/Assets/cylinder.model";
			write_model(inFile, outFile);

			inFile = "C:/gamedev/engine-dev/Engine/ModelReader/Assets/cone.dae";
			outFile = "C:/gamedev/engine-dev/Engine/ModelReader/Assets/cone.model";
			write_model(inFile, outFile);

			inFile = "C:/gamedev/engine-dev/Engine/ModelReader/Assets/torus.dae";
			outFile = "C:/gamedev/engine-dev/Engine/ModelReader/Assets/torus.model";
			write_model(inFile, outFile);*/
			int x;
			//std::cin >> x;
			break;
		} else {
			std::cout << "ERROR: Invalid command\n\n";
		}
	}

	return 0;
}

