#include <iostream>
#include <string>

using namespace std;

class Person{
	public:
		//constructor
		Person(string name="(Unknown (Constructor with void arguments) )" , uint8_t hp=100){
			this->name = name ;
			this->hp = hp ;

			cerr <<"[DBG]constructor: Person with name '"<< this->name <<" was created"<< endl;
		}

		//destructor
		~Person(){	
			cerr <<"[DBG]destructor: Person with name '"<< this->name <<"' was deleted"<< endl;
		}

		//functions
		//
		void say(string phrase){
			if( this->is_dead() ){
				cout 
				<< this->name <<"'s deadbody is trying to say something, "
				<<"but it's dead!";
				return;
			}

			cout << this->name <<": \""<< phrase <<"\""<< endl;
		}

		void act(string act){
			if( this->is_dead() ){
				cout 
				<< this->name <<"'s deadbody is trying to say something, "
				<<"but it's dead!"<< endl;
				return;
			}

			cout << this->name <<" "<< act << endl;
		}		

		void atk(Person &victim, unsigned int dmg){
			cout << this->name << " attacks "<< victim.name << endl;
			victim.get_dmg(dmg);
		}

	private:
		string name;	

		int hp;
		void ch_hp(int hp_changing){
			hp += hp_changing ;
		}
		void get_dmg(unsigned dmg){
			if( this->is_dead() ){
				return;
			}

			cout << this->name <<" got '"<< dmg << "' damage points"<< endl;

			this->ch_hp(-dmg);
			if( this->hp <= 0){
				case
				this->die();
			}
		}

		void get_healed(unsigned hp_up){
			if( this->is_dead() )
				return;
			cout << this->name <<" got healed for '"<< hp_up <<"' health points"<< endl;
			this->ch_hp(hp_up);
		}

		void die(string reason="unknown"){
			cout << this->name <<" died! ("<< reason <<")"<< endl;
		}

		bool is_dead(void){
			if(hp<=0)
				return true;
			else
				return false;
		}
};

int main(int argc, char **argv){
	Person protogonist = Person ("Samuel") ;

	protogonist.say("I'm alive!");
	protogonist.atk(protogonist, 99);
	protogonist.say();
	protogonist.act("suicide his self");

	// default exit
	return 0;
}
