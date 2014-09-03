/* Sergeev Artemiy
 * Realtime ray tracing system for rendering photo realistic scenes
 * RTRay main class impementation module
 * SPbSTU, IAMM, 2014
 */

#define NOMINMAX
#include <vector_functions.h>
#include <optixu/optixpp_namespace.h>
#include <optixu/optixu_math_namespace.h>

#include "rtray.h"

#include "Camera/camera.h"

using namespace rtray;
using namespace optix;

#define WIDTH 512
#define HEIGHT 512


static LPCWSTR get_wstr( std::string const & s )
{
  int len;
  int slength = (int)s.length() + 1;
  len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
  wchar_t* buf = new wchar_t[len];
  MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
  std::wstring r(buf);
  delete[] buf;
  return r.c_str();
}

rtray_t::rtray_t( void )
{
  try
  {
    context_ = optix::Context::create();
    context_->setRayTypeCount(1);
    context_->setEntryPointCount(1);

    context_->setPrintEnabled(true);
    context_->setPrintBufferSize(4096);

    context_["output_buffer"]->set(context_->createBuffer(RT_BUFFER_OUTPUT, RT_FORMAT_FLOAT4, WIDTH, HEIGHT));
    buffer_ = context_["output_buffer"]->getBuffer();
    context_["bad_color"]->setFloat(0.0f, 0.0f, 0.0f);
    context_["bg_color"]->setFloat(0.1f, 0.1f, 0.1f);
    context_["radiance_ray_type"]->setUint(0);
    context_["shadow_ray_type"]->setUint(1);
    context_["scene_epsilon"]->setFloat(1e-5f);

    camera_t camera(glm::vec3(3, 2, 0), glm::vec3(0, 0, 0));

    context_["cam_pos"]->setFloat(camera.eye());
    context_["cam_dir"]->setFloat(camera.dir());
    context_["cam_right"]->setFloat(camera.right());
    context_["cam_up"]->setFloat(camera.up() * HEIGHT / (float)WIDTH);

    Geometry sphere = context_->createGeometry();
    sphere->setPrimitiveCount(1u);
    sphere->setIntersectionProgram(context_->createProgramFromPTXFile("resources/box.cu.ptx", "intersect"));
    sphere->setBoundingBoxProgram(context_->createProgramFromPTXFile("resources/box.cu.ptx", "bounds"));
    sphere["boxmin"]->setFloat(-1.f, -1.f, -1.f);
    sphere["boxmax"]->setFloat(1.f, 1.f, 1.f);
    sphere->validate();
    geometry_.push_back(sphere);
    Material mat = context_->createMaterial();
    mat->setClosestHitProgram(0, context_->createProgramFromPTXFile("resources/constcolor.cu.ptx", "closest_hit_radiance"));
    mat["color"]->setFloat(1.f, 0.f, 0.f);
    GeometryInstance inst = context_->createGeometryInstance(sphere, &mat, &mat + 1);

    group_ = context_->createGeometryGroup();
    group_->setAcceleration(context_->createAcceleration("NoAccel", "NoAccel"));
    group_->setChildCount(1u);
    group_->setChild(0, inst);
    context_["top_object"]->set(group_);

    context_->setRayGenerationProgram(0, context_->createProgramFromPTXFile("resources/pinhole_camera.cu.ptx", "pinhole_camera"));
    context_->setExceptionProgram(0, context_->createProgramFromPTXFile("resources/pinhole_camera.cu.ptx", "exception"));
    context_->setMissProgram(0, context_->createProgramFromPTXFile("resources/pinhole_camera.cu.ptx", "miss"));
    buffer_->validate();
    context_->validate();
    context_->compile();
    context_->launch(0, WIDTH, HEIGHT);
  }
  catch (optix::Exception & e)
  {
    MessageBox(NULL, get_wstr(e.getErrorString()), L"ERROR", MB_ICONERROR | MB_OK);
  }
}

rtray_t::~rtray_t( void )
{
  buffer_->destroy();
  for (unsigned int  i = 0; i < geometry_.size(); ++i)
    geometry_[i]->destroy();
  context_->destroy();
}

void rtray_t::RenderFrame( void )
{
  void *rendered_data;
  RTsize w, h;
  GLenum gl_data_type;
  GLenum gl_format;
  RTformat format;

  try
  {
    buffer_->getSize(w, h);

    context_->launch(0, w, h);

    rendered_data = buffer_->map();
    format = buffer_->getFormat();

    switch (format)
    {
    case RT_FORMAT_UNSIGNED_BYTE4:
      gl_data_type = GL_UNSIGNED_BYTE;
      gl_format    = GL_RGBA;
      break;
    case RT_FORMAT_FLOAT:
      gl_data_type = GL_FLOAT;
      gl_format    = GL_LUMINANCE;
      break;
    case RT_FORMAT_FLOAT3:
      gl_data_type = GL_FLOAT;
      gl_format    = GL_RGB;
      break;
    case RT_FORMAT_FLOAT4:
      gl_data_type = GL_FLOAT;
      gl_format    = GL_RGBA;
      break;
    default:
      throw Exception("Invalid buffer format!");
      break;
    }

    glDrawPixels(w, h, gl_format, gl_data_type, rendered_data);
    buffer_->unmap();
  }
  catch (Exception * e)
  {
    MessageBox(NULL, get_wstr(e->getErrorString()), L"ERROR", MB_ICONERROR | MB_OK);
  }
}
