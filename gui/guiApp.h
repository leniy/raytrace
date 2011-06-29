/***************************************************************
 * Name:      guiApp.h
 * Purpose:   Defines Application Class
 * Author:    Leniy (m@leniy.info)
 * Created:   2010-09-21
 * Copyright: Leniy (http://leniy.info)
 * License:
 **************************************************************/

#ifndef GUIAPP_H
#define GUIAPP_H

#include <wx/app.h>

class guiApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // GUIAPP_H
