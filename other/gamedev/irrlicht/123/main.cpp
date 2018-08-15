#include <irrlicht.h>
#include <iostream>

using namespace irr ;
using namespace core ;
using namespace scene ;
using namespace video ;
using namespace io ;
using namespace gui ;
using namespace std ;

class MyReceiver : public IEventReceiver {
public:
	virtual bool OnEvent(const SEvent &event){
		if(event.EventType == EET_KEY_INPUT_EVENT){
			KeyIsDown[event.KeyInput.Key] = true ;
			if(event.KeyInput.PressedDown && KeyAcceptPressed[event.KeyInput.Key]){
				KeyIsPressed[event.KeyInput.Key] = true ;
				KeyAcceptPressed[event.KeyInput.Key] = false ;
				anyKey = true ;
			}
			if(!event.KeyInput.PressedDown){
				anyKey = false ;
				KeyIsPressed[event.KeyInput.Key] = false ;
				KeyAcceptPressed[event.KeyInput.Key] = true ;
			}
		}
		return false ;
	}

	virtual bool IsKeyPress(EKEY_CODE keycode){
		bool pressed = KeyIsPressed[keycode] ;
		KeyIsPressed[keycode] = false ;

		return pressed ;
	}

	virtual bool IsAnyKeyDown()const{
		return anyKey ;
	}

	virtual bool IsKeyDown(EKEY_CODE keycode)const{
		return KeyIsDown[keycode] ;
	}

	MyReceiver(void){
		for( u32 i=0 ; i<KEY_KEY_CODES_COUNT ; ++i ){
			KeyIsDown[i] = false ;
			KeyIsPressed[i] = false ;
			KeyAcceptPressed[i] = true ;
		}
		anyKey = false ;
	}
private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	bool KeyIsPressed[KEY_KEY_CODES_COUNT];
	bool KeyAcceptPressed[KEY_KEY_CODES_COUNT];
	bool anyKey;
};


int main(int argc, char **argv){
    //start up the engine
    IrrlichtDevice *device = (
        createDevice(EDT_OPENGL, dimension2du(640, 480), 16,
            false, false, false, 0
        )
    );
    device->setWindowCaption(L"You suck!");// Window title

    IVideoDriver *driver = device->getVideoDriver () ;
    ISceneManager *smgr = device->getSceneManager () ;


    MyReceiver myRec;

    SIrrlichtCreationParameters params;
    params.AntiAlias = 0 ;
    params.Bits = 32 ;
    params.Fullscreen = false ;
    params.Stencilbuffer = 0 ;
    params.Vsync = false ;
    params.WindowSize.Height = 480 ;
    params.WindowSize.Width = 640 ;
    params.Stereobuffer = false ;
    params.ZBufferBits = 1 ;
    params.DriverType = EDT_OPENGL ;
    params.EventReceiver = &myRec ;

    ISceneNode *camera = smgr->addCameraSceneNode(
	    0, vector3df(0,30, -40), vector3df(0, 5, 0)
        )
    ;

    IMeshSceneNode *cube = smgr->addCubeSceneNode() ;
    cube->setMaterialTexture(0, driver->getTexture("cube.png"));
    cube->setMaterialFlag(EMF_LIGHTING, 0);

    while( device->run() ){//main cycle
		driver->beginScene( true, true, SColor(0, 200, 200, 200));//driver start drawing a scene

        if( myRec.IsKeyDown(KEY_KEY_W) ){
			camera->setPosition(camera->getPosition() + vector3df(0, 0, 1));
			cout <<"You pressed key 'W'"<< endl;
        }

        cout<<"Cycle iteration"<< endl;
        cube->setRotation( cube->getRotation() + vector3df(0, 0, 1) );

        driver->beginScene( true, true, SColor(0, 120, 120, 120) );
        smgr->drawAll();
        driver->endScene();
    }
    device->drop();// Stop the engine

    return 0;
}
