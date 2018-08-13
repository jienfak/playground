#pragma once
//*************************************************

// includes
#include <iostream>
#include <string>
#include <map> 

//#define IS_DBG

using namespace std ;

class Calc {
	public:
		// Return calculated value of expression
		double 	expr(string);
		/* Check for unright symbols and return first not right
		   or -1 if not found any errors */
		int	ck(string);
	private:
		static double	calculate(string);
		static double	calculateToken(double, double, char);
		static string	delSpaces(string);	
		static bool	isNum(string);
		static bool	isDigit(char);
		static bool	hasOtherChars(string, string);
		static int	findNextToken(string);
		static bool	hasCharOfStr(string, string);
		static int	findChar(string, char);

		static const map<char, int> tokens; 
	   
		static const string able_chars;
};

//*************************************************
