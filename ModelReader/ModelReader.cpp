// ModelReader.cpp : Defines the entry point for the console application.
//

#include "Globals.h"
#include "Model.h"

void write_model(std::string &inFile, std::string &outFile, const glm::mat4 &transform = glm::mat4())
{
	std::cout << "Reading model file.\n";
	try {
		//glm::mat4 transform = glm::rotate(glm::mat4(), 90.0f, glm::vec3(1.0f, 0.0, 0.0f));
		//transform = glm::scale(transform, glm::vec3(5));
		model::Model model(inFile, transform);
		
		std::cout << "Writing to output file.\n";
		std::ofstream outStream(outFile, std::ios::out | std::ios::binary);
		model.Serialize(outStream);

		std::cout << "Done!\n";
	} catch(const char *e) {
		std::cout << "ERROR: " << e << "\n";
		std::cout << "\n";
	}
}

void write_directory(const std::string &inDirectory, const std::string &outDirectory, const glm::mat4 &transform = glm::mat4())
{
	std::vector<std::string> mFiles;

	WIN32_FIND_DATAA fileData;
	HANDLE hd = FindFirstFileA((inDirectory + "/*").c_str(), &fileData);

	if(hd == INVALID_HANDLE_VALUE) {
		return;
	}

	do {
		if(strcmp(fileData.cFileName, ".") == 0 ||
			strcmp(fileData.cFileName, "..") == 0) 
		{
			continue;
		}

		std::string inFilepath = inDirectory + "/" + fileData.cFileName;
		int start = inFilepath.rfind('/');
		int len = inFilepath.rfind('.') - start;
		std::string outFilepath = outDirectory + inFilepath.substr(start, len) + ".model";
		printf("Writing %s to %s\n", inFilepath.c_str(), outFilepath.c_str());
		write_model(inFilepath, outFilepath, transform);
	} while(FindNextFileA(hd, &fileData));
};

int main(int argc, char* argv[])
{
	std::string inFile, outFile;

	std::cout << "=== Challenge Engine Model Converter ====\n";
	std::cout << "Convert any 3D model format supported by assimp (http://assimp.sourceforge.net/) into a compressed binary file to be used with the challenge engine. \n";
	std::cout << "\n\n";

	while(true) {
		std::cout << "Please enter a command: \n";
		std::cout << "1: Convert file\n";
		std::cout << "2: Convert Directory\n";
		std::cout << "3: Help\n";
		std::cout << "4: Exit\n\n";

		int command = 4;
		std::cin >> command;

		std::cout << "\n";
		if(command == 1) {
			std::cout << "Enter input filepath: \n";
			std::cin >> inFile;
			std::cout << "\n";

			std::cout << "Enter output filepath: \n";
			std::cin >> outFile;
			std::cout << "\n";

			write_model(inFile, outFile);
		} else if(command == 2) {
			std::cout << "Nothing here yet!\n\n";
		} else if(command == 3) {
			break;
		} else if(command == 4) { // Debug mode

			glm::mat4 transform = glm::rotate(glm::mat4(), 90.0f, glm::vec3(1, 0, 0));
			transform = glm::scale(transform, glm::vec3(5));
			/*write_directory(
				"C:/gamedev/dungeon-raider/DungeonRaider/Common/Media/Models/molten_chasm/objects/_3ds",
				"C:/gamedev/dungeon-raider/DungeonRaider/Common/Media/Models/molten_chasm/objects/challenge",
				transform
			);*/
			write_directory(
				"C:/gamedev/dungeon-raider/DungeonRaider/Common/Media/Models/skeletons/dae",
				"C:/gamedev/dungeon-raider/DungeonRaider/Common/Assets/Characters"
			);

			//inFile = "C:/gamedev/dungeon-raider/DungeonRaider/Common/Media/Models/dark_mage/dark_mage_maya.dae";
			//outFile = "C:/gamedev/dungeon-raider/DungeonRaider/Common/Assets/Characters/dark_mage.model";

			//inFile = "C:/gamedev/dungeon-raider/DungeonRaider/Common/Media/Models/molten_chasm/molten_chasm.DAE";
			//outFile = "C:/gamedev/dungeon-raider/DungeonRaider/Common/Media/Models/molten_chasm/molten_chasm.model";

			//write_model(inFile, outFile, transform);
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

