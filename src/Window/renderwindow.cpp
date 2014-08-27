/* Sergeev Artemiy
 * Realtime ray tracing system for rendering photo realistic scenes
 * Render window class implementation module
 * SPbSTU, IAMM, 2014
 */

#include "renderwindow.h"

using namespace rtray;

BEGIN_EVENT_TABLE(render_window_t, wxFrame)
  EVT_SIZE     (render_window_t::resized)
END_EVENT_TABLE()

render_window_t::render_window_t(const wxString& title, const wxPoint& pos, const wxSize& size )
  : wxFrame(NULL, wxID_ANY, title, pos, size)
{
  new render_canvas_t(this);
}

void render_window_t::resized( wxSizeEvent & event )
{
  wxFrame::OnSize(event);
}
