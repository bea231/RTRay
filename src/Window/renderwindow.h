/* Sergeev Artemiy
 * Realtime ray tracing system for rendering photo realistic scenes
 * Render window class definition module
 * SPbSTU, IAMM, 2014
 */

#ifndef _RENDERWINDOW_H_
#define _RENDERWINDOW_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include "rendercanvas.h"

namespace rtray
{
  class render_window_t : public wxFrame
  {
  public:
    render_window_t(const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize );
  protected:
    void resized( wxSizeEvent & event );
    wxDECLARE_EVENT_TABLE();
  private:
    render_canvas_t *canvas_;
  };
}

#endif /* _RENDERWINDOW_H_ */
