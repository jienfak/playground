#include <iostream>

class A {
	public:
	void func1(void){
		std::cout<<"Calling func1 from A class object."<<std::endl;
	}
	A(void){
		std::cout<<"Constructor of A called."<<std::endl;
	}
};

class B:A {
	public:
	void func1(void){
		((A*)this)->func1();
		std::cout<<"Calling func1 from B class object."<<std::endl;
	}
	B(void){
		std::cout<<"Constructor of B called."<<std::endl;
	}
};

int main(int argc, char **argv){
	A a;
	B b;
	a.func1();
	b.func1();
	return 0 ;
}
