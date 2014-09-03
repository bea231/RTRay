/* Sergeev Artemiy
 * Realtime ray tracing system for rendering photo realistic scenes
 * Render canvas class implementation module
 * SPbSTU, IAMM, 2014
 */

#include "rendercanvas.h"

using namespace rtray;

BEGIN_EVENT_TABLE(render_canvas_t, wxGLCanvas)
  EVT_SIZE     (render_canvas_t::resized)
  EVT_PAINT    (render_canvas_t::render)
END_EVENT_TABLE()

render_canvas_t::render_canvas_t( wxFrame *parent, int *attributes )
  : wxGLCanvas(parent, wxID_ANY, attributes, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
  context_ = new wxGLContext(this);
}

render_canvas_t::~render_canvas_t( void )
{
  if (context_)
    delete context_;
}

void render_canvas_t::resized( wxSizeEvent & event )
{
  glViewport(0, 0, GetSize().x, GetSize().y);
}

void render_canvas_t::render( wxPaintEvent & event )
{
  wxGLCanvas::SetCurrent(*context_);
  wxPaintDC(this);

  glClearColor(0.f, 0.f, 0.f, 0.f);
  glClear(GL_COLOR_BUFFER_BIT);

  /*glBegin(GL_QUADS);
    glColor3f(1.f, 0.f, 0.f);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, 0.5);
  glEnd();*/

  rtray_.RenderFrame();

  glFinish();
  SwapBuffers();
}
