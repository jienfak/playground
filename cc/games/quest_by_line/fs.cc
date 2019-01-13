#include "header.hh"

void FileSystem::getLinesToEnd(std::string &file_name, std::vector<std::string> &lines){
	std::string line;
	std::ifstream input_file;
	input_file.open(file_name);

	while( getline(input_file, line) ){
		lines.push_back(line);
	}
}
