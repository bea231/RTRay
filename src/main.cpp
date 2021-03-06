/* Sergeev Artemiy
 * Realtime ray tracing system for rendering photo realistic scenes
 * Entry point module
 * SPbSTU, IAMM, 2014
 */

#include "Window/renderwindow.h"

using namespace rtray;

namespace rtray
{
  class rtray_application_t : public wxApp
  {
    virtual bool OnInit();
  };

  bool rtray_application_t::OnInit()
  {
    render_window_t *window = new render_window_t(wxT("RTRay - simple raytracing application"), wxPoint(50,50), wxSize(200,200));

    window->Show(TRUE);
    return TRUE;
  }
}

IMPLEMENT_APP(rtray_application_t)
