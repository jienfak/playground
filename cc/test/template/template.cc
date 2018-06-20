#include <iostream>

using namespace std;


template<typename T>
void sort(T array[], int size){
	T t;
	for(int i=0 ; i< size-1 ; ++i){
		for(int j= size-1 ; j>i ; --j){
			if(array[j] < array[j-1]){
				t = array[j] ;
				array[j] = array[j-1] ;
				array[j-1] = t ;
			}
		}
	}
}

template<size_t ArrayLength, typename SomeValueType>class SomeClass{
	SomeValueType SomeValue;
	SomeValueType SomeArray[ArrayLength];
	void f(){
		cout <<"f!"<< endl;
	}
};

int main(void){
	SomeClass<64, char> oc ;
	SomeClass<64, int> oi ;
	SomeClass<64, double> od;
	cout <<"size of object 'oc' "<< sizeof(oc) << endl;
	cout <<"size of object 'oi' "<< sizeof(oi) << endl;
	cout <<"size of object 'od' "<< sizeof(od) << endl;

	int iarr[] = {
		5, 6, 2, 1, 3, 4
	} ;
	char carr[] = {
		'a', 'd', 'c', '1', '5', '4', '3'
	} ;
	double darr[] = {
		123.23, 6.21, 534, 2
	} ;

	sort(iarr, 6);
	for(int i=0 ; i<6 ; ++i){
		cout<< iarr[i] <<" ";
	}
	cout<< endl;

	sort(carr, 7);
	for(int i=0 ; i<7 ; ++i){
		cout<< carr[i] <<" ";
	}
	cout<< endl;

	sort(darr, 4);
	for(int i=0 ; i<4 ; ++i){
		cout<< darr[i] <<" ";
	}
	cout<< endl;

	// succesful exit
	return 0;
}
