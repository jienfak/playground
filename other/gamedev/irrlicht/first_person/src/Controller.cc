#include <irrlicht.h>
#include <iostream>

using namespace irr ;
using namespace core ;
using namespace scene ;
using namespace video ;
using namespace io ;
using namespace gui ;
using namespace std ;

class Controller {
	public:
		Controller(ICameraSceneNode *cam, IEventReceiver *rec){
			this->cam = cam ;
			this->rec = rec ;
		}
	private:
		ICameraSceneNode *cam;
		IEventReceiver *rec;
} ;

