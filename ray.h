#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// GENERAL RAYTRACER LOGIC: A ray is like a function P(t) = A + tb. A is the origin
//, b is the direction, and t moves the ray along a line. This is what the at method is doing

// As ray is a class, we can call the functions by .origin and .direction
// the functions return an immutable reference to their members
class ray
{
    public:
    ray() {}

    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    // we can call origin and direction from outside the class normally
    const point3& origin() const { return orig; }
    const vec3& direction() const { return dir; }

    // takes in 2 vectors for origin and direction, multiplies the direction by a scalar
    point3 at(double t) const
    {
        return orig + t*dir;
    }

    private: // if we wanna call these, we have to call them by going ray::orig, and ray::dir
    point3 orig;
    vec3 dir;
};

#endif // RAY_H