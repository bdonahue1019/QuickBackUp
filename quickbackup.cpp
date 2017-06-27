#include<sstream>
#include<string>
#include<fstream>
#include<iostream>
#include<dirent.h>
#include<cstdlib>

using namespace std;
using std::cout;
using std::endl;

int main(int argc, char* argv[]){
	//open ifstream for CFG file
	std::string cDrive = "C:\\";
	std::string fileToOpen = cDrive+argv[1];
	std::ifstream configFile(fileToOpen.c_str());
	
	//check if file opened correctly
	if(!configFile){
		cout << "Cannot open input file.\n";
		return 1;
	}
	
	//strings for file paths
	std::string line;
	std::string sourceFolder;
	std::string targetFolder;
	
	//loop for reading file
	while(getline(configFile, line)){
		
		//istringstream for reading file
		std::istringstream iss(line);
		//check if sourceFolder string is empty
		if(sourceFolder.empty()){
			//if not store first folder in string
			iss >> sourceFolder;
			cout << "this is source\n";
			cout << sourceFolder << endl;
		}
		//if so store the next folder path in target folder
		else{
			iss >> targetFolder;
			cout << "This is target\n";
			cout << targetFolder << endl;
		}
		
	} 

	//close CFG file
	configFile.close();
	
	//initialise directories
	DIR *code = NULL;
	DIR *backups = NULL;
	
	//initialise struct for directories 
	struct dirent *pent = NULL;
	struct dirent *pentBack = NULL;
	
	code = opendir(sourceFolder.c_str());
	backups = opendir(targetFolder.c_str());
	
	if(code == NULL){
		cout << "\nERROR! code could not be initialised correctly";
		exit(3);
		
	}
	
	if(backups == NULL){
		cout << "\nERROR! backups could not be initialised correctly";
		exit(3);
		
	}
	
	while(pent = readdir(code)){
		if(pent == NULL){
			cout << "\nERROR! pointer was not correctly initialised";
			exit(3);
		}
		cout << pent->d_name << endl;
	}
	
	while(pentBack = readdir(backups)){
		if(pentBack == NULL){
			cout << "\nERROR! pointer was not correctly initialised";
			exit(3);
		}
		cout << pentBack->d_name << endl;
	}
	std::string copy = "copy";
	std::string command = copy+" "+sourceFolder+" "+targetFolder;
	
	system(command.c_str());
	
	
	closedir(code);
	closedir(backups);
	
	cin.get();
	
	return 0;
}
