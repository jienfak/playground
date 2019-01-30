/*
 * Unit test for line_work.cc.
 */

#include "header.hh"

int main(int cli_argc, char **cli_argv){
	std::vector<std::string> lines;
	std::cout<<"Starting tests of 'line_work' module."<<std::endl;

	std::string file_name("./unit_line_work_file") ;

	FileSystem::getLinesToEnd(file_name, lines);

	std::cout<<"Function numOfStartTabs checking..."<<std::endl;
	for( auto line : lines ){
		std::cout<<"numOfStartTabs('"<< line <<"') = '"<< LineWork::numOfStartTabs(line)<<"' ;"<<std::endl;
	}
	std::cout<<std::endl;

	std::cout<<"Function deleteStartTabs checking..."<<std::endl;
	for( auto line : lines ){
		std::cout<<"deleteStartTabs('"<< line <<"') = '"<< LineWork::deleteStartTabs(line) <<"' ;"<<std::endl;
	}

	std::cout<<"Function paragraph checking..."<<std::endl;
	for( int i=0 ; i<lines.size() ; ++i ){
		std::cout<<"getParagraph("<< i <<") = '"<< LineWork::getParagraph(lines, i) <<"' ;"<<std::endl;
	}

	std::cout<<"Function isLineEmpty checking..."<<std::endl;
	for( auto line : lines){
		std::cout<<"isLineEmpty('"<< line <<"' = '"<< LineWork::isLineEmpty(line) <<"' ;" << std::endl ;
	}

	std::cout<<"Function  nextNonEmpty checking..."<<std::endl;
	for( int i=0 ; i<lines.size() ; ++i){
		std::cout<<"nextNonEmpty("<< i <<") = "<< LineWork::nextNonEmpty(lines, i) <<std::endl;
	}

	std::cout<<"Function nextParagraph checking.."<<std::endl;
	for( int i=0 ; i<lines.size() ; ++i){
		std::cout<<"nextParagraph("<< i <<") = "<< LineWork::nextParagraph(lines, i) <<std:endl;
	}

	// Succesful exit.
	return 0 ;
}
