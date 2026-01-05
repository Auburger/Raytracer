
#ifndef VEC3_H 
#define VEC3_H


class vec3 { 
    public:
        double e[3]; 
        vec3() : e{0,0,0} {} // default constructor (0 vector)
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {} 
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        // OPERATOR OVERLOADS: 
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } 
        double operator[](int i) const { return e[i]; } // read-only operator: if vec3 v(1,2,3), doing vec[0] returns 1
        double& operator[] (int i) { return e[i]; } // like above, but can read and write

        // COMPOUND ASSIGNMENT OPERATORS: 
        vec3& operator+=(const vec3& v) { 
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this; 
        }

        vec3& operator*=(double t) { // scalar multiplication
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator /=(double t) { // using the method defined above for scalar division
            return *this *= 1/t;
        }

        // LENGTH CALCULATIONS:
        // it's just the magnitude of a vector
        double length() const {
            return std::sqrt(length_squared()); 
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        bool near_zero() const 
        {
            auto s = 1e-8;
            return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
        }
        static vec3 random()
        {
            return vec3(random_double(), random_double(), random_double());
        }

        static vec3 random(double min, double max)
        {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }
};

using point3 = vec3; // point3 is an alias for something of the type vec3, we can define point3 p(1,2,3) and it'll be like we defined a vec3 v(1,2,3)
// cool C++ feature

// ALL THESE FUNCTIONS are free functions, they create new objects instead of operating on and changing the input objects themselves
// They don't use the equal sign: i.e., +, -, *

// I think all of these operator overloads are redefining the above operator overloads, but as inline functions
// makes the runtime nicer in some cases, somehow (google later i'm tired)
inline std::ostream& operator<<(std::ostream& out, const vec3& v){ // overloads the << operator, returns a reference to the output stream (why? google later)
    // aliases: std::ostream is out, vec3 (unchangeable) is v
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2]; // prints vector in form "x y z"
}

// using the alias of u and v for vec3 objects again, idk why we're defining addition again
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// subtraction
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// multiplication
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// scalar multiplication
inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

// don't know why this is defined again, maybe c++ is weird with the order of multiplication
inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

// division
inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

// dot product
inline double dot(const vec3& u, const vec3& v) { // dot product
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

// cross product
inline vec3 cross(const vec3& u, const vec3& v) { // cross product
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// unit vector
inline vec3 unit_vector(const vec3& v) { // unit vector (1,1,1)
    return v / v.length();
}

inline vec3 random_in_unit_disk()
{
    while (true)
    {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}

inline vec3 random_unit_vector()
{
    while (true)
    {
        auto p = vec3::random(-1,1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1) //floating point imprecision
            return p / sqrt(lensq);
    }
}

inline vec3 random_on_hemisphere(const vec3& normal)
{
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

inline vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2*dot(v,n)*n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double ethi_etht)
{
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = ethi_etht * (uv + cos_theta*n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
#endif // ends the ifndef/define bit, preprocessor will skip to here if vec3_h was already imported
// once into a project
