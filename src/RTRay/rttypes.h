/* Sergeev Artemiy
 * Realtime ray tracing system for rendering photo realistic scenes
 * Global raytracing types definition module
 * SPbSTU, IAMM, 2014
 */

#include <optix.h>

struct PerRayData_radiance
{
  float3 result;
  float  importance;
  int depth;
};