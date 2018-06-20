#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv){
	// emulation of C massive of 10 elements type of int
	vector<int> v(10);

	//emulation C handling(does not give any exceptions)
	v[0] = 123 ;

	// C++ using
	v.at(1)	= 456 ;

	cout <<"v[0] = "<< v[0] << endl;
	cout <<"v.at(1) = "<< v.at(1) << endl;

	//exception getting
	try{
		v.at(11) = 890 ;

		cout <<"You would see that, if you had not an execption"<< endl;
	}catch(out_of_range){
		cout << "Here we got an execption" << endl;
	}

	// succesful exit
	return 0;
}
