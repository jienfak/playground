#include "./header.hh"

const map<char, int> Calc::tokens = {
	{'+', 1}, {'-', 1},
	{'*', 2}, {'/', 2}
} ;

const string Calc::able_chars = "0123456789+-*/()" ;

double Calc::expr(string expr){	
	expr = Calc::delSpaces(expr) ;
	return Calc::calculate( expr ) ;
}

int Calc::ck(string expr){
	for(int i=0 ; i<expr.length() ; ++i){
		char c = expr.at(i) ;
		#ifdef IS_DBG
		cerr<<"Checking '"<< c <<"'..."<<endl;
		#endif
		if( 0>findChar(Calc::able_chars, c) )  {
			return i ;
		}
	}
	return -1 ;
}

double Calc::calculate(string expr){
	while(  (expr.at(0)=='(') && ( expr.at(expr.length()-1)==')' )  ){
		expr = expr.substr(1, expr.length()-2) ;

		#ifdef IS_DBG
		cerr<<"After scobs deleting... expr = \""<< expr <<"\""<<endl;
		#endif
	}

	if(isNum(expr)){ return stod(expr) ; }

	// Parsing
	int dec_id = findNextToken(expr) ;
	string a = expr.substr(0, dec_id) ;
	string b = expr.substr(dec_id+1, expr.length()-dec_id) ;

	#ifdef IS_DBG
	cerr<<"dec_id="<<dec_id<<endl<<
		":1:\""<<a<<"\""<<
		":2:\""<<b<<"\""<<endl
	;
	#endif

	return calculateToken( calculate(a), calculate(b), expr.at(dec_id) ) ;
}

double Calc::calculateToken(double a, double b, char token){
	switch( token ){
		case '+': return a+b ;
		case '-': return a-b ;
		case '*': return a*b ;
		case '/': return a/b ;
		default:	return 0 ;
	}
}

string Calc::delSpaces(string expr){
	string buf = "" ;

	char c;
	for( int i=0 ; i<expr.length() ; ++i ){
		c = expr.at(i) ;
		if( (c == ' ')||(c == '\t')||(c == '\n') ){ continue; }
		else{ buf += c ;}//concatenate
	}

	return buf ;
}

bool Calc::isNum(string expr){
	char c;

	int bias;
	if(  (expr.at(0)=='-') || (expr.at(0)=='+')  ){ bias = 1 ; }
	else{ bias = 0 ; }

	for( int i=bias ; i<expr.length() ; ++i ){
		c = expr.at(i) ;
		if(! isDigit(c) ){ return false ; }
	}

	return true ;
}

bool Calc::isDigit(char c){
	if( (c>='0') && (c<='9')){ return true ;}
	else{ return false ; }
}

int Calc::findNextToken(string expr){
	int scobs_level = 0 ;
	int cur_token_id = 0 ;
	char cur_token = '*' ;
	for( int i=expr.length()-1 ; i>0 ; --i ){
		char c = expr.at(i) ;
		if(      c==')'	){ ++scobs_level; continue; }
		else if( c=='('	){ --scobs_level; continue; }
		else if(! tokens.count(c) ){ continue; }

		if( scobs_level ){ continue; }

		// If we have this token and it has more prior
		if( tokens.at(c) <= tokens.at(cur_token) ){
			cur_token_id = i ;
			cur_token = c ;
		}
	}

	return cur_token_id ;
}


bool Calc::hasCharOfStr(string expr, string chars){
	for(int i=0 ; i<expr.length() ; ++i){
		for(int x=0 ; x<chars.length() ; ++x){
			if(expr.at(i)==chars.at(x)){
				return true ;
			}
		}
	}
	return false ;
}

int Calc::findChar(string expr, char c){
	for(int i=0 ; i<expr.length() ; ++i){
		if(expr.at(i)==c){
			return i ;
		}
	}
	return -1 ;
}
