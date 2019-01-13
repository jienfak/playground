#include "header.hh"

int main(int cli_argc, char **cli_argv){
	std::string quest_file_path(cli_argv[1]) ; std::vector<std::string> lines;

	FileSystem::getLinesToEnd(quest_file_path, lines);
	
	/*for( auto line : lines ){
		std::cout<<line<<std::endl;
	}*/

	std::cout<< lines.at(0)<<std::endl;
	std::cout<<LineWork::getParagraph(lines, 0);

	// Succesful exit.
	return 0 ; 
}
