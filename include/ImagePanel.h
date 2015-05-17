#pragma once
#ifndef IMAGEPANEL_H
#define IMAGEPANEL_H

#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <wx/colour.h>
#include <wx/panel.h>
#include <wx/dc.h>
#include <wx/dcclient.h>
#include <wx/msgdlg.h>

class ImagePanel : public wxPanel
{
public:
    ImagePanel(wxWindow *parent,
               wxWindowID winid = wxID_ANY,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = (wxTAB_TRAVERSAL | wxSIMPLE_BORDER),
               const wxString& name = wxPanelNameStr);
    void paintNow(wxPaintEvent &e);
    void render(wxDC& dc);

    char p;
    ~ImagePanel();



private:
    inline void SetBgImage(wxDC& dc);
    inline void DrawMasks(int, int, wxImage&);
    void MouseMotion(wxMouseEvent& e);

    short StartY;
    short EndX;
    CvCapture * mCapture ;
    IplImage * mFrame;
//    wxImage img;
//    wxBitmap* bm;
////    wxPaintDC *dc;
};

#endif // IMAGEPANEL_H
