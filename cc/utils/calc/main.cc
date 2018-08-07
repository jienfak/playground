#include "./header.hh"

int main(int argc, char **argv){
	string input;
	Calc calc = Calc () ;
	while(true){
		cin>>input;
		if( cin.eof() ){ break; }
		cout<< calc.expr(input) <<endl;
	}

	// Succesful exit
	return 0 ;
}
