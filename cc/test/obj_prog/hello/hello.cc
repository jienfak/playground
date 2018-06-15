#include <iostream>
#include <string>

using namespace std;

class Person{
	public:
		//constructor
		Person(string name="(Unknown (Constructor with void arguments) )" , uint8_t age=1){
			this->name = name ;
			this->age = age ;

			cout <<"constructor: Person with name '"<< this->name << "' and age="<< to_string(this->age)<<" was created"<< endl;
		}

		//destructor
		~Person(){
			cout <<"destructor: Person with name '"<< this->name << "' and age="<< to_string(this->age)<<" was destroyed"<< endl;
		}

		//functions
		//
		void say(string phrase){
			cout << this->name <<": "<< phrase << endl;
		}

		void action(string act){
			cout << this->name <<" "<< act << endl;
		}

		
		//
	private:
		string name;	
		uint8_t age;
};

int main(int argc, char **argv){
	Person protogonist = Person("Samuel");
	protogonist.say("I'm alive!");
	protogonist.say("My age is "+ to_string( protogonist.getAge() )  );
	protogonist.action("suicide his self");

	// default exit
	return 0;
}
