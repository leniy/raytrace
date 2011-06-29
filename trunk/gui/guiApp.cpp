/***************************************************************
 * Name:      guiApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Leniy (m@leniy.info)
 * Created:   2010-09-21
 * Copyright: Leniy (http://leniy.info)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "guiApp.h"
#include "guiMain.h"

IMPLEMENT_APP(guiApp);

bool guiApp::OnInit()
{
    guiFrame* frame = new guiFrame(0L);
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();
    return true;
}
