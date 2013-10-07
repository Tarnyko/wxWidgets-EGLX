// NOTE: To run, it is recommended not to be in Compiz or Beryl, they have shown some instability.

#include <stdio.h>
 
#include <wx/wx.h>
#include <wx/glcanvas.h>

extern "C" {
#include "jwzgles.h"
#include "EGLX.h"
}

#ifndef WIN32
#include <unistd.h> // FIXME: ¿This work/necessary in Windows?
                    //Not necessary, but if it was, it needs to be replaced by process.h AND io.h
#endif
 
class wxGLCanvasSubClass: public wxGLCanvas {

public:
    wxGLCanvasSubClass(wxFrame* parent);
    void Paintit(wxPaintEvent& event);
    void Render();
protected:
    DECLARE_EVENT_TABLE()
};
 
BEGIN_EVENT_TABLE(wxGLCanvasSubClass, wxGLCanvas)
    EVT_PAINT    (wxGLCanvasSubClass::Paintit)
END_EVENT_TABLE()
 
wxGLCanvasSubClass::wxGLCanvasSubClass(wxFrame *parent)
:wxGLCanvas(parent, wxID_ANY,  wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas")){
    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
 
}
 
void wxGLCanvasSubClass::Paintit(wxPaintEvent& WXUNUSED(event)){
    Render();
}
 
void wxGLCanvasSubClass::Render()
{
    SetCurrent();
    wxPaintDC(this);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
 
    glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, -0.5);
        glColor3f(0.4, 0.5, 0.4);
        glVertex2f(0.0, -0.8);
    glEnd();
 
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.1, 0.1);
        glVertex2f(-0.1, 0.1);
        glVertex2f(-0.1, -0.1);
        glVertex2f(0.1, -0.1);
    glEnd();

    glFlush();
    SwapBuffers();
}

class MyApp: public wxApp
{
    virtual bool OnInit();
    wxGLCanvas * MyGLCanvas;
};
 
 
IMPLEMENT_APP(MyApp)
 
 
bool MyApp::OnInit()
{
	EGLX_main(0);
    wxFrame *frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Hello GL World"), wxPoint(50,50), wxSize(200,200));
    wxGLCanvasSubClass *canvas = new wxGLCanvasSubClass(frame);

    frame->Show(TRUE);
    return TRUE;
}
