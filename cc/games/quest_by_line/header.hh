#ifndef HH_HEADER
#define HH_HEADER

#define IS_DBG

#include <iostream>
#include <fstream>
#include <vector>
#include <cinttypes>

namespace FileSystem {
	void getLinesToEnd(std::string &file_path, std::vector<std::string> &lines );
	//const uint64_t Max_File_Lines = 1024 ;
}

namespace LineWork {
	uint64_t numOfStartTabs(std::string &line);	
	std::string deleteStartTabs(std::string &line);
	std::string getParagraph(std::vector<std::string> &lines, const uint64_t start_line_id);
	bool isLineEmpty(std::string &line);
	uint64_t nextNonEmpty(std::vector<std::string> &lines, const uint64_t start_line_id);
}




#endif /* HH_HEADER */
