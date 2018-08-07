#include "./header.hh"

int main(int argc, char **argv){
	string input;
	while(true){
		cout<<">"; cin>>input;
		cout<< Calc::expr(input) <<endl;
	}

	// Succesful exit
	return 0 ;
}
