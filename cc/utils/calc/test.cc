#include "./header.hh"

int main(void){
	Calc calc = Calc () ;
	cout<<"isDigit():"<<endl;
	for(char c='0' ; c<('9'+5) ; ++c){
		cout<<"\t '"<< c <<"' = "<< calc::isDigit(c) <<endl;
	}

	string string_arr[] = {
		"num?", "1234", "2356", "2342 3 4",
		"words + other + words", "scuk\t12,fd",
		"+123", "-23", "234+3423-323", "23*34-23"
	} ;
	cout<<"isNum():"<<endl;
	for( string str : string_arr ){
		cout<<"\t\""<< str <<"\" = "<< Calc::isNum(str) <<endl;
	}

	cout<<"delSpaces():"<<endl;
	for( string str : string_arr){
		cout<<"\t\""<< str <<"\" = \""<< Calc::delSpaces(str) <<"\""<<endl;
	}

	cout<<"findNextToken():"<<endl;
	for( string str : string_arr){
		cout<<"\t\""<< str <<"\" = "<< Calc::findNextToken(str) <<endl;
	}

	string string_arr1[] = {
		"2 + 23 + 4", "12 - 16 * 8", "34234+32/124", "123"
	} ;

	cout<<"expr():"<<endl;
	for( string str : string_arr1 ){
		cout<<"\t\""<< str <<"\" = "<< calc.expr(str) <<endl;
	}
	// Succesful exit
	return 0 ;
}
