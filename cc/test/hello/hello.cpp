#include <iostream>

using namespace std;

class student{
	public:
		int num;
		student(void){
			cout<<"making student void"<<endl;
			num = 1;
		}
};
class gr_student : public student{
	public:
		gr_student(int nu){
			cout<<"making gr_student unvoid"<<endl;
			num = nu;	
		}gr_student(void){
			cout<<"making gr_student void"<<endl;
			num = 2;
		}
};

int main(int argc, char *argv[]){	
	student ammy = student();
	std::cout<<ammy.num<<endl;
	gr_student sam  = gr_student(16);
	cout<<sam.num<<endl;
	//default exit
	return 0;
};
