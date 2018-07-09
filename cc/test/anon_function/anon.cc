#include <iostream>

using namespace std ;

int main(void){
	//anonym function example
	int (*func)(void) = [](/* params */ void) ->/* ret type */ int {
		cout<<"Anon function!"<< endl;
		return 123 ;
	};

	int num = func() ;
	cout<< num << endl;
	// Succesful exit
	return 0 ;
}
