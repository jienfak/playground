#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>

using namespace irr ;
using namespace core ;
using namespace scene ;
using namespace video ;
using namespace io ;
using namespace gui ;
using namespace std ;

class EvRec : public IEventReceiver {
	// Realisation of standard event receiver of irrlicht
	public:
		// This is the one method that we have to implement
		virtual bool OnEvent(const SEvent& event){
			// Remember whether each key is down or up
			if (event.EventType == irr::EET_KEY_INPUT_EVENT)
				KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown ;

			return false;
		}

		// This is used to check whether a key is being held down
		virtual bool IsKeyDown(EKEY_CODE keyCode) const {
			return KeyIsDown[keyCode];
		}
		
		EvRec(){}

	private:
		// We use this array to store the current state of each key
		bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main(){
	EvRec rec;

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

	scene::ISceneNode *node = smgr->addSphereSceneNode() ;
	if( node ){
		node->setPosition( core::vector3df(0, 0, 30) );
		node->setMaterialFlag(video::EMF_LIGHTING, false);
	}

	smgr->addCameraSceneNodeFPS();
	device->getCursorControl()->setVisible(false);
	u32 then = device->getTimer()->getTime() ;

	const f32 MOVEMENT_SPEED = 5.f ;

	while( device->run() ){
		// Main cycle
		//
		// Work out a frame delta time.
		bool was_pressed = false ;
		const u32 now = device->getTimer()->getTime() ;
		const f32 frameDeltaTime = (f32)(now-then) / 1000.f ;
		then = now ;

		core::vector3df nodePosition = node->getPosition() ;

		if( rec.IsKeyDown(irr::KEY_KEY_W) ){
			nodePosition.X += MOVEMENT_SPEED*frameDeltaTime ;
			was_pressed = true ;
		}else if(rec.IsKeyDown(irr::KEY_KEY_S)){
			nodePosition.X -= MOVEMENT_SPEED*frameDeltaTime ;
			was_pressed = true ;
		}else if(rec.IsKeyDown(irr::KEY_KEY_A)){
			nodePosition.Y -= MOVEMENT_SPEED*frameDeltaTime ;
			was_pressed = true ;
		}else if(rec.IsKeyDown(irr::KEY_KEY_D)){
			nodePosition.Y += MOVEMENT_SPEED*frameDeltaTime ;
			was_pressed = true ;
		}

		if( was_pressed ){
			std::cout<<"Y="<<nodePosition.Y<<":"
				"X="<<nodePosition.X<<":"
				"Z="<<nodePosition.Z<<std::endl;
		}

		node->setPosition(nodePosition);

		driver->beginScene( true, true, SColor(255, 113, 113, 113) );
		smgr->drawAll();
		driver->endScene();
	}
	device->drop();// Stop the engine

	return 0;
}
