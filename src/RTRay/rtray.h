/* Sergeev Artemiy
 * Realtime ray tracing system for rendering photo realistic scenes
 * RTRay main class definition module
 * SPbSTU, IAMM, 2014
 */

#ifndef _RTRAY_H_
#define _RTRAY_H_

#include <optix.h>
#include <optixu/optixpp_namespace.h>

#include <gl/GL.h>

#include <vector>

namespace rtray
{
  class rtray_t
  {
  public:
    rtray_t( void );
    ~rtray_t( void );

    void RenderFrame( void );
  private:
    optix::Context context_;
    optix::Buffer  buffer_;
    optix::GeometryGroup group_;

    std::vector<optix::Geometry> geometry_;
  };
}

#endif /* _RTRAY_H_ */
