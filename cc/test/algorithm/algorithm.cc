#include <algorithm>
#include <iostream>
#include <vector>

using namespace std ;

struct Sum {
	Sum(){ sum = 0 ; }
	void operator()(int n){ sum += n ; }

	int sum;
};

int main(void){
	vector<int> nums{3, 4, 2, 9, 15, 267} ;

	cout<<"Before: ";
	for( auto n : nums )
		cout << n <<" ";
	cout<< endl;

	for_each( nums.begin(), nums.end(),  [](int &n){ n++; } );//anonym function
	Sum s = for_each( nums.begin(), nums.end(), Sum() );

	std::cout <<"After: ";
	for(auto n : nums)
		cout<< n <<" ";

	cout<< endl;
	cout<<"Sum = "<< s.sum << endl;

	// Succesful exit
	return 0 ;
}
