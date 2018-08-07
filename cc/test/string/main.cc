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

	string s1 = "012345678" ;
	cout<<s1.substr(2, 5)<<endl;

	return 0;
}
