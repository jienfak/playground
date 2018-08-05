#include <iostream>

using namespace std ;

int f(){
	throw 123;
	return 1 ;
}

int main(void){
	// Succeful exit
	try{
		f();
	}catch(int err){
		cout<< err <<endl;
	}
	return 0 ;
}
