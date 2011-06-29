///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 17 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFrame__
#define __GUIFrame__

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define idMenuOpen 1000
#define idMenuSave 1001
#define idMenuQuit 1002
#define idMenuAbout 1003

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mbar;
		wxMenu* fileMenu;
		wxMenu* helpMenu;
		wxStatusBar* statusBar;
		wxGrid* sys_data;
		wxGrid* len_data;
		wxGrid* putong_data;
		wxButton* btRefresh;
		wxButton* btCal;
		wxButton* btDraw;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRefresh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCal( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDraw( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("光线追踪BETA"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DrawDlg
///////////////////////////////////////////////////////////////////////////////
class DrawDlg : public wxDialog 
{
	private:
	
	protected:
		wxButton* ButtonSph;
		wxButton* m_button8;
		wxButton* m_button9;
		
		
		wxButton* m_button7;
		wxButton* m_button81;
		wxButton* m_button91;
		
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnDrawSph( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDrawFld( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDrawDis( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveSph( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveFld( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveDis( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		DrawDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("画图"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~DrawDlg();
	
};

#endif //__GUIFrame__
