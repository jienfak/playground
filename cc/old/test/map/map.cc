#include <iostream>
#include <map>

using namespace std ;

int main(void){
	map<char, int> m = {
		{'+', 1},{'-', 1},
		{'*', 2},{'/', 2}
	} ;

	cout<< m.at('+') <<endl
		<< m.at('-') <<endl
		<< m.at('*') << endl
		<< m.at('/') << endl
	;

	cout<<endl;

	cout<< m.count('+') << endl;
	cout<< m.count('2') << endl;
	// Default exit
	return 0 ;
}
