#include "../include/ImagePanel.h"

ImagePanel::ImagePanel(wxWindow *parent,
               wxWindowID winid,
               const wxPoint& pos,
               const wxSize& size,
               long style,
               const wxString& name) : wxPanel (parent,winid,pos,size,style,name)
{
    wxInitAllImageHandlers();
    // инициалзиуется камера
    mCapture = cvCreateCameraCapture(CV_CAP_ANY);

    // подключение методов к событиям
    Connect(wxEVT_PAINT, (wxObjectEventFunction)&ImagePanel::paintNow,0,this);
    Connect(wxEVT_MOTION, (wxObjectEventFunction)&ImagePanel::MouseMotion,0,this);

    p  = 0; // параметр необходимый для отсутствия последней отрисовки, котор
    if (!mCapture) {
        p=1;
        wxMessageBox(wxString()<<"Camera is not avaible");
    }
    else assert( mCapture );

    cvSetCaptureProperty(mCapture , CV_CAP_PROP_FRAME_WIDTH, 640);
    cvSetCaptureProperty(mCapture , CV_CAP_PROP_FRAME_HEIGHT, 480);
    StartY = EndX = this->GetSize().GetHeight()/2; // начальное значение велечины "Y" и последнее значение величины "Высота"
//    img.LoadFile("google_logo.jpg");
//    bm =  new wxBitmap(this->img);
}

void ImagePanel::paintNow(wxPaintEvent &e){ //отрисовка на панельки
    wxPaintDC dc(this); // dc расшифровывается как Device context
    if(p==0){ //отрисывается пока окно не закрывается, приходится контролировать вручную, потому что отрисовка проходит после удаления объекта из "кучи"
        //видимо недочет wxWidgets
        SetBgImage(dc); //говорящий метод
        render(dc);
        Refresh(); //команда вызывающая отрисовку
    }
}

void ImagePanel::render(wxDC& dc) //получение изображения с камеры
{
    wxBitmap m_pBitmap; //сюда будут сохранятся данные для вывода
    mFrame = cvQueryFrame( mCapture );

    if (!mFrame) wxMessageBox(wxString()<<"Error with mFrame");

    if( mFrame ){
        IplImage* pSrcImg = cvCloneImage( mFrame );
        IplImage* pDstImg = cvCreateImage( cvSize(pSrcImg->width,  pSrcImg->height),pSrcImg->depth, 3 );

        cvCvtColor(pSrcImg,pDstImg,CV_RGB2BGR); // это преобразование надо для OpenCV, он рассматривает модель не RGB а BGR

        int nCamWidth = mFrame->width; //преобазований не было
        int nCamHeight = mFrame->height; //просто решил сохранить

        uchar *rawData = NULL;
        CvSize roiSize;
        int step = 0;
        cvGetRawData( pDstImg, &rawData, &step, &roiSize );

        wxImage pWxImg = wxImage( nCamWidth, nCamHeight, rawData, TRUE ); //получаем картинку в объект wxWidgets
        pWxImg.InitAlpha(); // здесь я подключил к изображению альфа-канал, это я не смог сделать на OpenGL, поэтому и пришлось использовать стандартные средства
        DrawMasks(nCamWidth, nCamHeight, pWxImg); //метод с говорящим названием
        m_pBitmap = wxBitmap( pWxImg.Scale(nCamWidth, nCamHeight) ); //помещение обработанных в контейнер для отображения

        cvReleaseImage( &pDstImg ); //очистка памяти
        cvReleaseImage( &pSrcImg );

        dc.DrawBitmap(m_pBitmap,0,0); // отрисовка контейнера
    }
}

void ImagePanel::MouseMotion(wxMouseEvent&e){
    double h = this->GetSize().GetHeight(); //решил сразу занести в переменные,
    double w = this->GetSize().GetWidth(); //потому что потом приходилось делать явные преобразования
    if (e.GetPosition().y <= h/2 && e.GetPosition().y >= 0){ //это для величины "Y"
        StartY = e.GetPosition().y;
    }

    if (e.GetPosition().x>=0 && e.GetPosition().x<=w ){ // это для величины "высота"
        EndX = (w-(w-e.GetPosition().x*(h/w)))+(h/2)/(w/(w-e.GetPosition().x)); //упростить дальше не смог, зато никаких условий нет
    }
}

inline void ImagePanel::SetBgImage(wxDC& dc){ // описание метода с говорящим именем
    wxBitmap bg;
    bg.LoadFile("google_logo.jpg", wxBITMAP_TYPE_JPEG);
    dc.DrawBitmap(bg, 10, 100);
}

inline void ImagePanel::DrawMasks(int w, int h, wxImage &img){ //отрисовка масок, методы ничего особенного не делают, поэтому я поставил inline
    for (int i=0; i<w; ++i){
        for (int j=StartY; j<EndX; ++j){
            img.SetAlpha(i,j,100);
        }
    }

    for (int i=0; i<w; ++i){
        for (int j=EndX; j<h; ++j){
            img.SetAlpha(i,j,0);
        }
    }
}

ImagePanel::~ImagePanel()
{
    cvReleaseCapture(&mCapture);
}
