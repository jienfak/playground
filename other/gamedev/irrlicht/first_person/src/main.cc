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

	float buf;
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

	ICameraSceneNode *camera = smgr->addCameraSceneNode() ;
	camera->setTarget( core::vector3df(75, 75, 75) );
	camera->bindTargetAndRotation(true);

	scene::ISceneNode *node = smgr->addCubeSceneNode() ;
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

	const f32 MOVEMENT_SPEED = 10.f ;
	const f32 ROTATION_SPEED = 50.f ;

	long iteration = 0 ;
	driver->beginScene( true, true, SColor(255, 113, 113, 113) );

	while( device->run() ){
		// Main cycle
		//

		// Work out a frame delta time.	
		bool was_pressed = false ;
		const u32 now = device->getTimer()->getTime() ;
		const f32 frameDeltaTime = (f32)(now-then) / 1000.f ;
		then = now ;

		vector3df view = getCurrentView(camera) ;

		core::vector3df next_camera_rotation = camera->getRotation() ;
		core::vector3df next_camera_position = camera->getPosition() ;
		core::vector3df next_camera_target = camera->getTarget() ;
	
		// Arrows.
		if( rec.IsKeyDown(irr::KEY_UP) ){
			next_camera_rotation.X -= ROTATION_SPEED*frameDeltaTime ;
			was_pressed = true ;
		}if(rec.IsKeyDown(irr::KEY_DOWN)){
			next_camera_rotation.X += ROTATION_SPEED*frameDeltaTime ;
			was_pressed = true ;
		}if(rec.IsKeyDown(irr::KEY_LEFT)){
			next_camera_rotation.Y -= ROTATION_SPEED*frameDeltaTime ;
			was_pressed = true ;
		}if(rec.IsKeyDown(irr::KEY_RIGHT)){
			next_camera_rotation.Y += ROTATION_SPEED*frameDeltaTime ;
			was_pressed = true ;
		}
		camera->setRotation(next_camera_rotation);	

		// WASD.
		if(rec.IsKeyDown(irr::KEY_KEY_W)){
			//next_camera_position += next_camera_target*frameDeltaTime*MOVEMENT_SPEED ;
			next_camera_position += getCurrentView(camera) * MOVEMENT_SPEED * frameDeltaTime ;
			was_pressed = true ;
		}if(rec.IsKeyDown(irr::KEY_KEY_S)){
			next_camera_position -= getCurrentView(camera) * MOVEMENT_SPEED * frameDeltaTime ;
			was_pressed = true ;
		}if(rec.IsKeyDown(irr::KEY_KEY_D)){	
			vector3df vec; vec.X = view.Z ; vec.Z = -view.X ;
			next_camera_position += vec*MOVEMENT_SPEED*frameDeltaTime ;
		}if(rec.IsKeyDown(irr::KEY_KEY_A)){		
			vector3df vec; vec.X = view.Z ; vec.Z = -view.X ;
			next_camera_position -= vec*MOVEMENT_SPEED*frameDeltaTime ;
		}
		camera->setPosition(next_camera_position);

		if(rec.IsKeyDown(irr::KEY_KEY_F)){
			was_pressed = true ;
		}

		if( was_pressed ){
			std::cout<<"-----------------------"<<std::endl
				<<"X="<< next_camera_position.X <<":"\
				<<"Y="<< next_camera_position.Y <<":"\
				<<"Z="<< next_camera_position.Z <<std::endl
				<<"^"<<std::endl
				<<"X="<< next_camera_rotation.X <<":"\
				<<"Y="<< next_camera_rotation.Y <<":"\
				<<"Z="<< next_camera_rotation.Z <<std::endl
				<<"^"<<std::endl
				<<"X="<< next_camera_target.X <<":"\
				<<"Y="<< next_camera_target.Y <<":"\
				<<"Z="<< next_camera_target.Z <<std::endl;
		;
		}	
		driver->beginScene( true, true, SColor(255, 113, 113, 113) );
		smgr->drawAll();
		driver->endScene();
	}
	device->drop();// Stop the engine

	return 0;
}
