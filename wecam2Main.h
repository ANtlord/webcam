/***************************************************************
 * Name:      wecam2Main.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2012-06-30
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef WECAM2MAIN_H
#define WECAM2MAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wecam2App.h"
#include "include/ImagePanel.h"

class wecam2Frame: public wxFrame
{
    public:
        wecam2Frame(wxFrame *frame, const wxString& title);
        ~wecam2Frame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
        ImagePanel *Panel;
};


#endif // WECAM2MAIN_H
