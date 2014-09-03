#include "../rttypes.h"

#include <optix_math.h>

rtDeclareVariable(float3, color, , );
rtDeclareVariable(float3, shading_normal,   attribute shading_normal, ); 
rtDeclareVariable(PerRayData_radiance, prd_radiance, rtPayload, );

RT_PROGRAM void closest_hit_radiance()
{
  prd_radiance.result = normalize(rtTransformNormal(RT_OBJECT_TO_WORLD, shading_normal))*0.5f + 0.5f;;
}