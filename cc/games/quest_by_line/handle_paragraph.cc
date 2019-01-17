#include "header.hh"

int8_t handleParagraph.cc(
	std::vector<std::string> &lines,
	const uint64_t paragraph_line_id
){
	uint64_t cur_line_id = paragraph_line_id ;
	std::string cur_line ;

	// Getting description of result and a question and printing it.
	std::string cur_paragraph = LineWork::getParagraph(lines, paragraph_line_id) ;
	std::cout<<cur_paragraph<<"\n\n";

	// Moving current line through paragraph.
	cur_line_id += cur_paragraph.size() + 2 ;
	// Not it's on next paragraph.

	// Getting questions and printing them.
	//
	uint64_t question_num_tabs = numOfStartTabs(lines.at(cur_line_id)) + 1 ;
	uint64_t cur_question_id = 1 ;
	while(
		numOfStartTabs( cur_line =lines.at(cur_line_id) )
		    ==
		question_num_of_tabs
	){
		/*
		 * While we don't meet paragraph with more than we need tabs and 
		 * not empty line.
		 */

		cur_paragraph = getParagraph(lines, cur_line_id) ;
		std::cout<< cur_question_id <<") "<<  <<std::endl<<std::endl;
		
		// Moving line to the next paragraph.
		cur_line_id += cur_paragraph.size() + 2 ;
	}

}
