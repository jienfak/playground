#include <iostream>

class A {
	public:
		virtual void func1(void){
			std::cout<<"Calling func1 from A."<<std::endl;
		}
};

class B:A {
	public:
		void func1(void){
			std::cout<<"Calling func1 from B."<<std::endl;
		}
};

class C:public A {
	public:
};

int main(int argc, char **argv){
	A a; a.func1();
	B b; b.func1();
	std::cout<<"Not functions will be called from 'C' object."<<std::endl;
	C c;c.func1();

	return 0 ;
}
