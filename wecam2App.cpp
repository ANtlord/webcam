/***************************************************************
 * Name:      wecam2App.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2012-06-30
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "wecam2App.h"
#include "wecam2Main.h"

IMPLEMENT_APP(wecam2App);

bool wecam2App::OnInit()
{
    wecam2Frame* frame = new wecam2Frame(0L, _("wxWidgets Application Template"));
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();
    
    return true;
}
