#include <iostream>
#include <string>

using namespace std ;

int main(void){
	std::string str = "Hi";
	bool bl = str=="Hi";
	std::cout<<str+"dick"<<std::endl;

	string s = "String" ;
	s.at(3) = '\0' ;
	cout<< s <<endl;

	string s1 = "012345678"/*'\0'*/ ;
	cout<< s1.substr(0, 3) <<endl;

	cout<< string("1")*6 << endl;

	return 0;
}
