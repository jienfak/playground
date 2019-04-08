// wxWidgets "Hello, World" program.
//
// For compilers that support precompilation, includes "wx/wx.h".
//
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

class MyApp : public wxApp {
	public:
		virtual bool OnInit();
};

class MyFrame : public wxFrame {
	public:
		MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
	private:
		void OnHello(wxCommandEvent &event);
		void OnExit(wxCommandEvent &event);
		void OnAbout(wxCommandEvent &event);

	wxDECLARE_EVENT_TABLE();
};

enum{
	ID_Hello = 1
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(ID_Hello,  MyFrame::OnHello)
	EVT_MENU(wxID_EXIT, MyFrame::OnExit)
	EVT_MENU(wxID_ABOUT,MyFrame::OnAbout)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit(){
	MyFrame *frame = new MyFrame("Hello, World!", wxPoint(50, 50), wxSize(450, 340)) ;
	frame->Show(true);
	return true ;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
		: wxFrame(NULL, wxID_ANY, title, pos, size){
	wxMenu *menu_file = new wxMenu ;
	menu_file->Append(ID_Hello, "&Hello...\tCtnl-H",
		"Help string shown in status bor for this menu item."
	);
	menu_file->AppendSeparator();
	menu_file->Append(wxID_EXIT);

	wxMenu *menu_help = new wxMenu ;
	menu_help->Append(wxID_ABOUT);

	wxMenuBar *menu_bar = new wxMenuBar ;
	menu_bar->Append(menu_file, "&File");
	menu_bar->Append(menu_help, "&Help");

	SetMenuBar(menu_bar);

	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");
}

void MyFrame::OnExit(wxCommandEvent &event){
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &event){
	wxMessageBox("This is a wxWidgets 'Hello, World' sample",
		"About Hello World", wxOK | wxICON_INFORMATION
	);
}
