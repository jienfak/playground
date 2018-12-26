#include <irrlicht.h>
#include <iostream>
#include <cmath>

using namespace irr ;
using namespace core ;
using namespace scene ;
using namespace video ;
using namespace io ;
using namespace gui ;
using namespace std ;

class EventReceiver : public IEventReceiver {
	// Realisation of standard event receiver of irrlicht
	//
	struct SMouseState {
		core::position2di Position;
		bool LeftButtonDown ;
		SMouseState() : LeftButtonDown(false){}
	} MouseState ;	

	public:
		virtual bool OnEvent(const SEvent& event){
			// When something happens
			//
			if (event.EventType == irr::EET_KEY_INPUT_EVENT){
				// Keyboard states
				//
				KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown ;
			}else if( event.EventType == irr::EET_MOUSE_INPUT_EVENT){
				// Mouse states
				//
				switch(event.MouseInput.Event){
					case EMIE_LMOUSE_PRESSED_DOWN:
						MouseState.LeftButtonDown = true ;
						break;
					case EMIE_LMOUSE_LEFT_UP:
						break;
					case EMIE_MOUSE_MOVED:
						MouseState.Position.X = event.MouseInput.X ;
						MouseState.Position.Y = event.MouseInput.Y ;
						break;
				}
			}

			return false;
		}
	
		virtual bool IsKeyDown(EKEY_CODE keyCode) const {
			// This is used to check whether a key is being held down
			//
			return KeyIsDown[keyCode];
		}
		
		EventReceiver(){}
	private:
		// We use this array to store the current state of each key
		bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

vector3df getCurrentView(ICameraSceneNode *cam){
	return cam->getTarget()-cam->getPosition() ;
}

int main(){
	// This function starts first
	//

	EventReceiver rec;

	/* Start up the engine */
	IrrlichtDevice *device = (
        	createDevice(
			EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false, false, false, &rec
		)
	) ;
	device->setWindowCaption(L"You suck!");// Window title

	IVideoDriver *driver = device->getVideoDriver () ;
	ISceneManager *smgr = device->getSceneManager () ;	

	/*SIrrlichtCreationParameters params;
	params.AntiAlias		= 0 ;
	params.Bits			= 32 ;
	params.Fullscreen		= false ;
	params.Stencilbuffer	= 0 ;
	params.Vsync 		= false ;
	params.WindowSize.Height 	= 480 ;
	params.WindowSize.Width 	= 640 ;
	params.Stereobuffer 	= false ;
	params.ZBufferBits 		= 1 ;
	params.DriverType = 	EDT_OPENGL ;
	params.EventReceiver = 	&rec ; */


	SKeyMap key_map[4];
	key_map[0].Action = EKA_MOVE_FORWARD ;
	key_map[0].KeyCode = KEY_KEY_W ;

	key_map[1].Action = EKA_MOVE_BACKWARD ;
	key_map[1].KeyCode = KEY_KEY_S ;

	key_map[2].Action = EKA_STRAFE_LEFT ;
	key_map[2].KeyCode = KEY_KEY_A ;

	key_map[3].Action = EKA_STRAFE_RIGHT ;
	key_map[3].KeyCode = KEY_KEY_D ;

	ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS(
		// Camera parameters.
		0, // Parent.
		100, // Rotation speed.
		0.5f, // Movement speed.
		-1, // ID
		key_map, // Key map.
		4 // Size of key map.
	) ;


	/*ICameraSceneNode *camera = smgr->addCameraSceneNode();
	camera->bindTargetAndRotation(true);*/

	scene::ISceneNode *node = smgr->addCubeSceneNode(50.f) ;
	if( node ){
		node->setPosition( core::vector3df(0, 0, 30) );
		node->setMaterialFlag(video::EMF_LIGHTING, false);
	}

	scene::ISceneNode *node2 = smgr->addCubeSceneNode() ;
	if( node2 ){
		node2->setPosition(vector3df(0,30,30));
		node2->setMaterialFlag(EMF_LIGHTING, false);
	}

	device->getCursorControl()->setVisible(false);
	u32 then = device->getTimer()->getTime() ;

	long iteration = 0 ;
	//driver->beginScene( true, true, SColor(255, 113, 113, 113) );

	while( device->run() ){
		// Main cycle.
		//

		// Work out a frame delta time.	
		bool was_pressed = false ;
		const u32 now = device->getTimer()->getTime() ;
		const f32 frame_delta_time = (f32)(now-then) / 1000.f ;
		then = now ;

		/*if(was_pressed){
			cout<<"--------------"<<endl
				<<"Target:"<<endl
				<<"X="<<Next_Camera_Target.X<<":"\
				<<"Y="<<Next_Camera_Target.Y<<":"\
				<<"Z="<<Next_Camera_Target.Z<<endl
				<<"Rotation:"<<endl
				<<"X="<<Next_Camera_Rotation.X<<":"\
				<<"Y="<<Next_Camera_Rotation.Y<<":"\
				<<"Z="<<Next_Camera_Rotation.Z<<endl
				<<"Position:"<<endl
				<<"X="<<Next_Camera_Position.X<<":"\
				<<"Y="<<Next_Camera_Position.Y<<":"\
				<<"Z="<<Next_Camera_Position.Z<<endl
			;
		}*/

		/*camera->setPosition(Next_Camera_Position);
		camera->setTarget(Next_Camera_Target);
		camera->setRotation(Next_Camera_Rotation);*/

		driver->beginScene( true, true, SColor(0, 0, 0, 0) );
		smgr->drawAll();	
		driver->endScene();	
	}
	device->drop();// Stop the engine

	return 0;
}
