/* Sergeev Artemiy
 * Realtime ray tracing system for rendering photo realistic scenes
 * Camera object implementation
 * SPbSTU, IAMM, 2014
 */

#include "camera.h"

using namespace rtray;
using namespace glm;

camera_t::camera_t( vec3 eye, float phi, float theta ) : eye_(eye), phi_(phi), theta_(theta)
{
  update();
}

camera_t::camera_t( vec3 eye, vec3 look_at ) : eye_(eye)
{
  vec3 const dir = look_at - eye;
  phi_ = atan(dir.z, dir.x);
  theta_ = asin(dir.y / length(dir));
  update();
}

float3 camera_t::eye() const
{
  return make_float3(eye_.x, eye_.y, eye_.z);
}

float3 camera_t::dir() const
{
  return dir_;
}

float3 camera_t::up() const
{
  return up_;
}

float3 camera_t::right() const
{
  return right_;
}

void camera_t::translate( vec3 const &point )
{

}

void camera_t::move_right_left( float step )
{

}

void camera_t::move_up_down( float step )
{

}

void camera_t::rotate_up_down( float angle )
{

}

void camera_t::rotate_right_left( float angle )
{

}

void camera_t::update( void )
{
  float sine_phi = sin(phi_), cosine_phi = cos(phi_);
  float sine_theta = sin(theta_), cosine_theta = cos(theta_);
  float length;
  float const eps = 1e-6f;

  length = glm::sqrt(1 + sine_theta * sine_theta);
  dir_.x = cosine_phi / length;
  dir_.y = sine_theta / length;
  dir_.z = sine_phi / length;

  right_.x = -sine_phi;
  right_.y = 0;
  right_.z = cosine_phi;

  vec3 up = cross(vec3(right_.x, right_.y, right_.z),
                  vec3(dir_.x, dir_.y, dir_.z));
  up_ = make_float3(up.x, up.y, up.z);
}
