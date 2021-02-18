//
// Created by user on 2/15/2021.
//

#ifndef GNU_STDAFX_H
#define GNU_STDAFX_H
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/norm.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/epsilon.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <algorithm>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159;

inline double degreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}


// Random from [0,1)
inline double randomDouble()
{
    return rand() / (RAND_MAX + 1.0f);
}

inline double randomDouble(double min, double max)
{
    return min + (max - min) * randomDouble();
}

inline float randomFloat()
{
    return static_cast<float>(rand() / (RAND_MAX + 1.0f));
}

inline float randomFloat(float min, float max)
{
    return min + (max - min) * randomDouble();
}

using vec3 = glm::dvec3;

inline vec3 randomVec3()
{
    return vec3(randomDouble(), randomDouble(), randomDouble());
}

inline vec3 randomVec3(double min, double max)
{
    return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

inline vec3 randomInSphere()
{
    while(true)
    {
        auto p = randomVec3(-1, 1);
        if(glm::length2(p) >= 1) continue;
        return p;
    }
}

inline vec3 randomUnitVector()
{
    return glm::normalize(randomInSphere());
}

inline vec3 randomInHemisphere(vec3 const & normal)
{
    vec3 inUnitSphere = randomInSphere();
    if(glm::dot(inUnitSphere, normal) > 0.0) // Same hemisphere as normal
        return inUnitSphere;
    else
        return -inUnitSphere;
}

inline bool vecNearZero(vec3 const & vec) {
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8; // Epsilon
    return (std::fabs(vec[0]) < s) && (std::fabs(vec[1]) < s) && (std::fabs(vec[2]) < s);
}

inline vec3 Reflect(vec3 const & v, vec3 const & n)
{
    return v - 2 * dot(v, n) * n;
}

inline vec3 Refract(vec3 const & uv, vec3 const & n, double k)
{
    float ndotv = dot(n, uv); // also known as cos(alpha_i)
    // t = [  k(n.v)   - ( 1-k^2   ( 1-(n.v)^2 ))^0.5  ] * n -   k*v
    return (k * (ndotv) - sqrt(1 - k * k * (1 - ndotv * ndotv))) * n - (k * uv);

/*    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = k * (uv + cos_theta * n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - glm::length2(r_out_perp))) * n;
    return r_out_perp + r_out_parallel;*/
}

inline vec3 RandomUnitDisk()
{
    while(true)
    {
        auto p = vec3(randomDouble(-1, 1),randomDouble(-1, 1), 0);
        if(glm::length2(p) >= 1) continue;
        return p;
    }
}

#endif //GNU_STDAFX_H
