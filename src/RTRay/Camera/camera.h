/* Sergeev Artemiy
 * Realtime ray tracing system for rendering photo realistic scenes
 * Camera object declaraion module
 * SPbSTU, IAMM, 2014
 */

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>
#include <vector_functions.h>

namespace rtray
{
  class camera_t
  {
  public:
    camera_t( glm::vec3 eye, float phi = 0, float theta = 0 );
    camera_t( glm::vec3 eye, glm::vec3 look_at );

    float3 eye() const;
    float3 dir() const;
    float3 up() const;
    float3 right() const;

    void translate( glm::vec3 const &point );
    void move_right_left( float step ); /* step > 0 -> move right, otherwise -> move left */
    void move_up_down( float step ); /* step > 0 -> move up, otherwise -> move down */
    void rotate_up_down( float angle ); /* angle > 0 -> rotate direction up, otherwise -> rotate down */
    void rotate_right_left( float angle ); /* angle > 0 -> rotate direction right, otherwise -> rotate left */
  private:
    void update( void );
  private:
    /* Main camera's parameters */
    float phi_;
    float theta_;
    glm::vec3 eye_;

    /* Camera parameters, witch will be updated, when main parameters update */
    float3 dir_;
    float3 up_;
    float3 right_;
  };
}

#endif /* _CAMERA_H_ */
