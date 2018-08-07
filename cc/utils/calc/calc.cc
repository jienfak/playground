#include "./header.hh"

double Calc::expr(string expr){	
	string expr_cleared = Calc::delSpaces(expr) ;
	return Calc::calculate( expr_cleared ) ;
}

double Calc::calculate(string expr){
	if(isNum(expr)){ return stod(expr) ; }

	int dec_id = findNextToken(expr) ;

	#ifdef IS_DBG
	cout<<"dec_id="<<dec_id<<endl;
	cout<<	":1:\""<<expr.substr(0, dec_id)<<"\""<<
		":2:\""<<expr.substr(dec_id+1, expr.length()-1)<<"\""<<endl
	;
	#endif

	return calculateToken(
		calculate(expr.substr(0, dec_id) ),
		calculate( expr.substr(dec_id+1, expr.length()-1) ),
		expr.at(dec_id) 
	) ;
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
	if( (expr.at(0)=='-') || (expr.at(0)=='+')){
		bias = 1 ;
	}else{
		bias = 0 ;
	}

	for( int i=bias ; i<expr.length() ; ++i ){
		c = expr.at(i) ;
		if(! isDigit(c) )
			return false ;
	}

	return true ;
}

bool Calc::isDigit(char c){
	if( (c>='0') && (c<='9')){ return true ;}
	else{ return false ; }
}

int Calc::findNextToken(string expr){
	int cur_token_id = 0 ;
	char cur_token = '*' ;
	for( int i=expr.length()-1 ; i>0 ; --i ){
		char c = expr.at(i) ;
		if(!( Calc::tokens.count(c) )){
			continue;
		}

		// If we have this token and it has more prior
		if( Calc::tokens.at(c) <= Calc::tokens.at(cur_token) ){
			cur_token_id = i ;
			cur_token = c ;
		}
	}

	return cur_token_id ;
}

