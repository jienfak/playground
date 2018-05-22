#include <iostream>

namespace myspace{
	class myclass{
		public:
			double dicklen;
			int bubssize;
			myclass(double dickln, int bubsize){
				dicklen = dickln;
				bubssize = bubsize;
			}
			myclass(void){
				dicklen = 1;
				bubssize = 2;
			}
			void showbubs(){
				std::cout<<"(.)(.)"<<std::endl;
			}
	};
}

int main(int argc, char **argv){
	myspace::myclass dicken;
	dicken.showbubs();
	std::cout<<"Hello, World!"<<std::endl;
	return 0;
}
