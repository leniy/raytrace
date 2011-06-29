///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 17 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	mbar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* menuFileOpen;
	menuFileOpen = new wxMenuItem( fileMenu, idMenuOpen, wxString( wxT("打开(&O)") ) + wxT('\t') + wxT("Ctrl+O"), wxT("打开文件"), wxITEM_NORMAL );
	fileMenu->Append( menuFileOpen );
	
	wxMenuItem* menuFileSave;
	menuFileSave = new wxMenuItem( fileMenu, idMenuSave, wxString( wxT("保存(&S)") ) + wxT('\t') + wxT("Ctrl+S"), wxT("保存数据"), wxITEM_NORMAL );
	fileMenu->Append( menuFileSave );
	
	wxMenuItem* m_separator1;
	m_separator1 = fileMenu->AppendSeparator();
	
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("退出(&Q)") ) + wxT('\t') + wxT("Alt+F4"), wxT("退出本程序"), wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );
	
	mbar->Append( fileMenu, wxT("文件(&F)") ); 
	
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("关于(&A)") ) + wxT('\t') + wxT("F1"), wxT("关于"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	
	mbar->Append( helpMenu, wxT("帮助(&H)") ); 
	
	this->SetMenuBar( mbar );
	
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	sys_data = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	sys_data->CreateGrid( 1, 5 );
	sys_data->EnableEditing( true );
	sys_data->EnableGridLines( true );
	sys_data->EnableDragGridSize( false );
	sys_data->SetMargins( 0, 0 );
	
	// Columns
	sys_data->SetColSize( 0, 72 );
	sys_data->SetColSize( 1, 85 );
	sys_data->SetColSize( 2, 81 );
	sys_data->SetColSize( 3, 83 );
	sys_data->SetColSize( 4, 80 );
	sys_data->EnableDragColMove( false );
	sys_data->EnableDragColSize( false );
	sys_data->SetColLabelSize( 30 );
	sys_data->SetColLabelValue( 0, wxT("表面数N") );
	sys_data->SetColLabelValue( 1, wxT("入瞳距lpw") );
	sys_data->SetColLabelValue( 2, wxT("孔阑直径2a") );
	sys_data->SetColLabelValue( 3, wxT("视场角2W") );
	sys_data->SetColLabelValue( 4, wxT("普通光线条数") );
	sys_data->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	sys_data->AutoSizeRows();
	sys_data->EnableDragRowSize( false );
	sys_data->SetRowLabelSize( 80 );
	sys_data->SetRowLabelValue( 0, wxT("系统参数") );
	sys_data->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	sys_data->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	fgSizer1->Add( sys_data, 0, wxALL, 5 );
	
	len_data = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	len_data->CreateGrid( 4, 5 );
	len_data->EnableEditing( true );
	len_data->EnableGridLines( true );
	len_data->EnableDragGridSize( false );
	len_data->SetMargins( 0, 0 );
	
	// Columns
	len_data->SetColSize( 0, 69 );
	len_data->SetColSize( 1, 93 );
	len_data->SetColSize( 2, 71 );
	len_data->SetColSize( 3, 88 );
	len_data->SetColSize( 4, 83 );
	len_data->EnableDragColMove( false );
	len_data->EnableDragColSize( true );
	len_data->SetColLabelSize( 30 );
	len_data->SetColLabelValue( 0, wxT("曲面半径r") );
	len_data->SetColLabelValue( 1, wxT("与下一面间距d") );
	len_data->SetColLabelValue( 2, wxT("折射率n") );
	len_data->SetColLabelValue( 3, wxT("F光折射率nF") );
	len_data->SetColLabelValue( 4, wxT("C光折射率nC") );
	len_data->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	len_data->EnableDragRowSize( true );
	len_data->SetRowLabelSize( 80 );
	len_data->SetRowLabelValue( 0, wxT("0(空气/物面)") );
	len_data->SetRowLabelValue( 1, wxT("1") );
	len_data->SetRowLabelValue( 2, wxT("2") );
	len_data->SetRowLabelValue( 3, wxT("3") );
	len_data->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	len_data->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	fgSizer1->Add( len_data, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	putong_data = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	putong_data->CreateGrid( 4, 3 );
	putong_data->EnableEditing( true );
	putong_data->EnableGridLines( true );
	putong_data->EnableDragGridSize( false );
	putong_data->SetMargins( 0, 0 );
	
	// Columns
	putong_data->EnableDragColMove( false );
	putong_data->EnableDragColSize( true );
	putong_data->SetColLabelSize( 30 );
	putong_data->SetColLabelValue( 0, wxT("L") );
	putong_data->SetColLabelValue( 1, wxT("U") );
	putong_data->SetColLabelValue( 2, wxT("H") );
	putong_data->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	putong_data->EnableDragRowSize( true );
	putong_data->SetRowLabelSize( 80 );
	putong_data->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	putong_data->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	fgSizer3->Add( putong_data, 0, wxALL, 5 );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 3, 1, 0, 0 );
	
	btRefresh = new wxButton( this, wxID_ANY, wxT("已自动刷新"), wxDefaultPosition, wxDefaultSize, 0 );
	btRefresh->Enable( false );
	
	gSizer1->Add( btRefresh, 0, wxALL, 5 );
	
	btCal = new wxButton( this, wxID_ANY, wxT("计算"), wxDefaultPosition, wxDefaultSize, 0 );
	btCal->SetDefault(); 
	gSizer1->Add( btCal, 0, wxALL, 5 );
	
	btDraw = new wxButton( this, wxID_ANY, wxT("画图"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( btDraw, 0, wxALL, 5 );
	
	fgSizer3->Add( gSizer1, 1, wxALIGN_LEFT, 5 );
	
	fgSizer1->Add( fgSizer3, 1, wxEXPAND, 5 );
	
	this->SetSizer( fgSizer1 );
	this->Layout();
	fgSizer1->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( menuFileOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnOpen ) );
	this->Connect( menuFileSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSave ) );
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	btRefresh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnRefresh ), NULL, this );
	btCal->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnCal ), NULL, this );
	btDraw->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnDraw ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnOpen ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSave ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	btRefresh->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnRefresh ), NULL, this );
	btCal->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnCal ), NULL, this );
	btDraw->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnDraw ), NULL, this );
	
}

DrawDlg::DrawDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	bSizer5->SetMinSize( wxSize( 400,400 ) ); 
	fgSizer3->Add( bSizer5, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 2, 5, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	ButtonSph = new wxButton( this, wxID_ANY, wxT("球差曲线"), wxDefaultPosition, wxDefaultSize, 0 );
	ButtonSph->SetDefault(); 
	fgSizer4->Add( ButtonSph, 0, wxALL, 5 );
	
	m_button8 = new wxButton( this, wxID_ANY, wxT("场曲曲线"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_button8, 0, wxALL, 5 );
	
	m_button9 = new wxButton( this, wxID_ANY, wxT("畸变曲线"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_button9, 0, wxALL, 5 );
	
	
	fgSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button7 = new wxButton( this, wxID_ANY, wxT("保存"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_button7, 0, wxALL, 5 );
	
	m_button81 = new wxButton( this, wxID_ANY, wxT("保存"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_button81, 0, wxALL, 5 );
	
	m_button91 = new wxButton( this, wxID_ANY, wxT("保存"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_button91, 0, wxALL, 5 );
	
	
	fgSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	fgSizer3->Add( fgSizer4, 1, wxEXPAND, 5 );
	
	this->SetSizer( fgSizer3 );
	this->Layout();
	fgSizer3->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DrawDlg::OnClose ) );
	ButtonSph->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DrawDlg::OnDrawSph ), NULL, this );
	m_button8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DrawDlg::OnDrawFld ), NULL, this );
	m_button9->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DrawDlg::OnDrawDis ), NULL, this );
	m_button7->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DrawDlg::OnSaveSph ), NULL, this );
	m_button81->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DrawDlg::OnSaveFld ), NULL, this );
	m_button91->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DrawDlg::OnSaveDis ), NULL, this );
}

DrawDlg::~DrawDlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DrawDlg::OnClose ) );
	ButtonSph->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DrawDlg::OnDrawSph ), NULL, this );
	m_button8->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DrawDlg::OnDrawFld ), NULL, this );
	m_button9->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DrawDlg::OnDrawDis ), NULL, this );
	m_button7->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DrawDlg::OnSaveSph ), NULL, this );
	m_button81->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DrawDlg::OnSaveFld ), NULL, this );
	m_button91->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DrawDlg::OnSaveDis ), NULL, this );
	
}
