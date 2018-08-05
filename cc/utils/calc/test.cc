#include "./header.hh"

int main(void){
	cout<<"isDigit():"<<endl;
	for(char c='0' ; c<('9'+5) ; ++c){
		cout<<"\t '"<< c <<"' = "<< Calc::isDigit(c) <<endl;
	}

	string string_arr[] = {
		"num?", "1234", "2356", "2342 3 4",
		"words + other + words", "scuk\t12,fd"
	} ;
	cout<<"isNum():"<<endl;
	for( string str : string_arr ){
		cout<<"\t\""<< str <<"\" = "<< Calc::isNum(str) <<endl;
	}

	cout<<"delSpaces():"<<endl;
	for( string str : string_arr){
		cout<<"\t\""<< str <<"\" = \""<< Calc::delSpaces(str) <<"\""<<endl;
	}
	// Succesful exit
	return 0 ;
}
