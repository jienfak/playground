#include "./header.hh"

double Calc::calculate(string &expr){
	if(isNum(expr))
		return stod(expr) ;

}

string Calc::delSpaces(string &expr){
	string buf = "" ;

	char c;
	for( int i=0 ; i<expr.length() ; ++i ){
		c = expr.at(i) ;
		if((c == ' ')||(c == '\t')||(c == '\n'))
			continue;
		else
			buf += c ;
	}

	return buf ;
}

bool Calc::isNum(string &expr){
	char c;
	for( int i=0 ; i<expr.length() ; ++i ){
		c = expr.at(i) ;
		if(! isDigit(c) )
			return false ;
	}

	return true ;
}

bool Calc::isDigit(char c){
	if( (c>='0') && (c<='9'))
		return true ;
	else
		return false ;
}
