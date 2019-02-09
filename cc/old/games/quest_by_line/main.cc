#include "header.hh"

int main(int cli_argc, char **cli_argv){
	std::string quest_file_path(cli_argv[1]) ;
	std::vector<std::string> lines;
	uint64_t start_line = 0 ;

	FileSystem::getLinesToEnd(quest_file_path, lines);
	
	/*for( auto line : lines ){
		std::cout<<line<<std::endl;
	}*/

	bool result = LineWork::handleParagraph(lines, LineWork::nextNonEmpty(lines, start_line) );

	if( !result ){
		std::cout<<"You lost!"<<std::endl;
		return 1 ;
	}
	// Succesful exit, you won.
	std::cout<<"You won!"<<std::endl;
	return 0 ; 
}
