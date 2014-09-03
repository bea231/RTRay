/* Sergeev Artemiy
 * Realtime ray tracing system for rendering photo realistic scenes
 * Render canvas class definition module
 * SPbSTU, IAMM, 2014
 */

#ifndef _RENDERCANVAS_H_
#define _RENDERCANVAS_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/glcanvas.h>

#include "../RTRay/rtray.h"

namespace rtray
{
  class render_canvas_t : public wxGLCanvas
  {
  public:
    render_canvas_t( wxFrame *parent, int *attributes = NULL );
    ~render_canvas_t( void );
  protected:
    void resized( wxSizeEvent & event );
    void render( wxPaintEvent & event );

    DECLARE_EVENT_TABLE();
  private:
    wxGLContext *context_;

    rtray_t rtray_;
  };
}

#endif /* _RENDERCANVAS_H_ */
