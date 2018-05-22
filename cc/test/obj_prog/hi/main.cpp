#include <iostream>
#include <string.h>

using namespace std;

class Integer{
	private:
		int value;
	public:
		Integer(int i): value(i){
			;
		}
		const int operator+(const Integer& rv) const{
			return value+rv.value;
		}
};

int main(void){
	Integer i = 2, x=3;
	int g = i+x;
	cout<<i+x;
	return 0;
}
