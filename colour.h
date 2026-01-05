#ifndef COLOUR_H
#define COLOUR_H

#include "interval.h"
#include "vec3.h"


using colour = vec3;

inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}

// using vectors as colours because we do not need to reinvent the wheel lmao
void write_colour(std::ostream& out, const colour& pixel_colour)
{
    // using auto just... feels wrong :sob:
    auto r = pixel_colour.x();
    auto g = pixel_colour.y();
    auto b = pixel_colour.z();

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const interval intensity(0.000, 0.999);
    // r, g and b are only going to be between 0 and 1
    int rbyte = int(255.999 * intensity.clamp(r));
    int gbyte = int(255.999 * intensity.clamp(g));
    int bbyte = int(255.999 * intensity.clamp(b));

    // write the colour out
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif // COLOUR_H
