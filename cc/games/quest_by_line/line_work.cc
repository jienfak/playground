#include "header.hh"

uint64_t LineWork::numOfStartTabs(std::string &line){
	// Returns num of tabs at start of line.
	//

	// Checking
	if(line==""){
		return 0 ;
	}

	uint64_t i=0 ;
	while(line.at(i)=='\t'){ ++i; }
	return i ;
}

std::string LineWork::deleteStartTabs(std::string &line){
	// Returns line without tabs in start.
	//

	uint64_t i;
	// Returning for this id to end of line.
	return line.substr(i = LineWork::numOfStartTabs(line), line.length()-i-1 ) ;
}

std::string LineWork::getParagraph(std::vector<std::string> &lines, const uint64_t start_line_id){
	// Returns clear paragraph, which starts at start_line_id.
	//
	const uint64_t paragraph_tabs_num =
	    LineWork::numOfStartTabs(lines.at(start_line_id))
	;
	uint64_t cur_line_id = start_line_id ;

	std::string paragraph_ret = "" ;
	std::string cur_line ;
	while(// While we have equal biases.
	  ( LineWork::numOfStartTabs( cur_line = lines.at(cur_line_id++) )  ==  paragraph_tabs_num )
	  &&
	  ( cur_line != "" )
	){
		/* Adding to returned in the future to paragraph
		 * current line without tabs at start. */
		paragraph_ret += LineWork::deleteStartTabs(cur_line) + "\n" ;
		std::cout<<"Added line to paragraph..."<<std::endl;
	}
	
	// Deleting last char(it's '\n').
	paragraph_ret = paragraph_ret.substr(0, paragraph_ret.length()-1) ;
	return paragraph_ret ;
}


