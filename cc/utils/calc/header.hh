#pragma once
//*************************************************

// includes
#include <iostream>
#include <string>
#include <map> 

//#define IS_DBG

using namespace std ;

namespace Calc {
	double	calculate(string);
	double	calculateToken(double, double, char);
	string	delSpaces(string);
	double 	expr(string);
	bool	isNum(string);
	bool	isDigit(char);
	bool	hasOtherChars(string, string);
	int	findNextToken(string);

	const map<char, int> tokens = {
		{'+', 1}, {'-', 1},
		{'*', 2}, {'/', 2}
	} ;
   
	const string able_chars = "0123456789+-*/" ;
}

//*************************************************
