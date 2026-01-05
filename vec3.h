// this is a library defining vector-related operations
#ifndef VEC3_H //ifndef: checks if VEC3_H has been defined
#define VEC3_H // defines VEC3_H 
// ifndef and define are preprocessor directives, work together to implement header guards
// ifndef checks if VEC3_H has been defined, if so, the preprocessor will skip everything
// until #endif, so it doesn't get processed again
// if we code multiple libraries with this library, and then try to import them all into
// a project, these make sure they don't fuck up the compiler by trying to import vec3_h multiple times


class vec3 { // class declaration: introduces a class without providing its complete implementation
    // what's a class? it's like a struct (in C) with functions in it
    public:
        double e[3]; // data member declaration: data member is the variable that stores the state/data of an object
        // stores the 3 vector components of the vector (x,y,z), each vec3 object gets its own copy of this array
        // CONSTRUCTORS: initialize the objects (vec3s) in this case, as they're created
        // same name as the class, no return type, can have parameters
        // special method automatically called when an object is created
        // controls how objects are created
        vec3() : e{0,0,0} {} // default constructor (0 vector)
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {} // parametrized constructor (creates a vector with specific values)
        // you create a vec3 by using 3 doubles: ig the 2 case thing means that it'll work if you 
        // call vec3 v1 (with no values) and vec3 v1(1,2,3) it'll work? the first one shows you what the empty
        // case is supposed to be, the second how to assign values to it

    // ALL THESE FUNCTIONS (defined in the class) are MEMBER functions, they change the input itself
    // (Possibly why they use the *this pointer): even the ones that don't use the pointer use it implicitly
    // the methods with the = sign operate on the objects themselves

        // METHODS: operate on the object's data
        // the following 3 are acessor functions (they return each component)
        // const means they don't modify the object, provide controlled access to data
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        // OPERATOR OVERLOADS: Custom things we want our operators (+, -, etc) to do on the object
        // I guess the empty brackets mean it just operates on the object 
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } // negation: if vec3 v(1,2,3), doing -v results in (-1, -2, -3)
        double operator[](int i) const { return e[i]; } // read-only operator: if vec3 v(1,2,3), doing vec[0] returns 1
        double& operator[] (int i) { return e[i]; } // like above, but can read and write

        // COMPOUND ASSIGNMENT OPERATORS: Modify the object
        vec3& operator+=(const vec3& v) { //vec3&: returns a reference to the modified object
            // operator+= means += is the operator being overloaded 
            // const vec3& v : takes in a reference to another vec3, called v 
            // const means unchangeable, & is the reference: it's like an alias for the og variable: we modify it directly
            // & is like a pointer, but less bullshit
            e[0] += v.e[0]; // e is the object, v is what we're operating on (the other object passed in)
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this; // this is a pointer to the object that called the function -- we're returning the actual value of what "this" points to
            // i.e., we're returning the modified vec3 that called the function
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

        // LENGTH CALCULATIONS: kinda smart actually, length usees length squared
        // it's just the magnitude of a vector
        double length() const {
            return std::sqrt(length_squared()); // std:: is just saying the length_squared function is defined in the
            // standard library, basically means nothing, it's just to shut up the compiler
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