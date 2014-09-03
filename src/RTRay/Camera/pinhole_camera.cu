/* Sergeev Artemiy
 * Realtime ray tracing system for rendering photo realistic scenes
 * Ray generation module
 * SPbSTU, IAMM, 2014
 */

#include <optix.h>
#include <optix_math.h>
#include <optixu/optixu_math_namespace.h>

#include "../rttypes.h"

rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );
rtDeclareVariable(uint2, launch_dim,   rtLaunchDim, );

rtBuffer<float4, 2> output_buffer;

rtDeclareVariable(unsigned int, radiance_ray_type, , );
rtDeclareVariable(float, scene_epsilon, , );

rtDeclareVariable(float3, cam_dir, , );
rtDeclareVariable(float3, cam_right, , );
rtDeclareVariable(float3, cam_up, , );
rtDeclareVariable(float3, cam_pos, , );

rtDeclareVariable(float, screen_half_width, , );
rtDeclareVariable(float, screen_half_height, , );

rtDeclareVariable(rtObject, top_object, , );

RT_PROGRAM void pinhole_camera()
{
  float2 d = make_float2(launch_index) / make_float2(launch_dim) * 2.f - 1.f;
  float3 ray_origin = cam_pos;
  float3 ray_direction = normalize(d.x * cam_right + d.y * cam_up + cam_dir);
  optix::Ray ray(ray_origin, ray_direction, radiance_ray_type, scene_epsilon, RT_DEFAULT_MAX);

  PerRayData_radiance prd;
  prd.importance = 1.f;
  prd.depth = 0;

  rtTrace(top_object, ray, prd);

  output_buffer[launch_index] = make_float4(prd.result, 1);
}

rtDeclareVariable(PerRayData_radiance, prd_radiance, rtPayload, );
rtDeclareVariable(float3, bg_color, , );
RT_PROGRAM void miss()
{
  prd_radiance.result = bg_color;
}

rtDeclareVariable(float3, bad_color, , );
RT_PROGRAM void exception()
{
  const unsigned int code = rtGetExceptionCode();
  output_buffer[launch_index] = make_float4(bad_color, 1);
  rtPrintf("Caught exception 0x%X at launch index (%d,%d)\n", code, launch_index.x, launch_index.y );
}
