#include "./header.hh"

int main(int argc, char **argv){
	string input;
	// For interactive mode.
	string prompt = ">" ;
	int prompt_len = prompt.length() ;
	Calc calc = Calc () ;

	while( !cin.eof() ){
		cerr<<prompt ; cin>>input;

		// Do while is not end of file.
		//if( cin.eof() ){ break; }

		// Checking for unknown chars.
		int unright_index = calc.ck(input) ;
		#ifdef IS_DBG
		cout<<unright_index<<endl;
		#endif
		if( unright_index>=0 ){
			for( int i=0 ; i<unright_index+prompt_len ; ++i ){
				cerr<<" ";
			}
			cerr<<"^: Unknown token!"<<endl;
			continue;
		}

		// Calculate and output
		cout<< calc.expr(input) <<endl;
	}

	// Succesful exit
	return 0 ;
}
