//
// Created by user on 2/28/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Utility.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/28/2021
 * End Header --------------------------------------------------------*/
#include "stdafx.h"
#include "Utility.h"
#include "AABB.h"

double degreesToRadians(double degrees) {
    return degrees * pi / 180.0;
}

double randomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

double randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}

float randomFloat() {
    return static_cast<float>(rand() / (RAND_MAX + 1.0f));
}

float randomFloat(float min, float max) {
    return min + (max - min) * randomDouble();
}

vec3 randomVec3() {
    return vec3(randomDouble(), randomDouble(), randomDouble());
}

vec3 randomVec3(double min, double max) {
    return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

vec3 randomInSphere() {
    while(true)
    {
        auto p = randomVec3(-1, 1);
        if(glm::length2(p) >= 1) continue;
        return p;
    }
}

vec3 randomUnitVector() {
    return glm::normalize(randomInSphere());
}

vec3 randomInHemisphere(const vec3 &normal) {
    vec3 inUnitSphere = randomInSphere();
    if(glm::dot(inUnitSphere, normal) > 0.0) // Same hemisphere as normal
        return inUnitSphere;
    else
        return -inUnitSphere;
}

bool vecNearZero(const vec3 &vec) {
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8; // Epsilon
    return (std::fabs(vec[0]) < s) && (std::fabs(vec[1]) < s) && (std::fabs(vec[2]) < s);
}

vec3 Reflect(const vec3 &v, const vec3 &n) {
    return v - 2 * dot(v, n) * n;
}

vec3 Refract(const vec3 &uv, const vec3 &n, double k) {
    float ndotv = dot(n, uv); // also known as cos(alpha_i)
    // t = [  k(n.v)   - ( 1-k^2   ( 1-(n.v)^2 ))^0.5  ] * n -   k*v
    return (k * (ndotv) - sqrt(1 - k * k * (1 - ndotv * ndotv))) * n - (k * uv);

/*    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = k * (uv + cos_theta * n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - glm::length2(r_out_perp))) * n;
    return r_out_perp + r_out_parallel;*/
}

vec3 RandomUnitDisk() {
    while(true)
    {
        auto p = vec3(randomDouble(-1, 1),randomDouble(-1, 1), 0);
        if(glm::length2(p) >= 1) continue;
        return p;
    }
}

AABB SurroundingBox(AABB box0, AABB box1) {
    vec3 smallPoint = glm::min(box0.Min(), box1.Min());
    vec3 bigPoint = glm::max(box0.Max(), box1.Max());
    return AABB(smallPoint, bigPoint);
}

// 0 to 1
float randomInt() {
    static std::uniform_int_distribution<> distribution(0, 1);
    static std::mt19937 generator;
    return distribution(generator);

}

float randomInt(float min, float max) {
    // return min + (max - min) * randomInt();
    return static_cast<int>(randomDouble(min, max+1));
}

bool box_x_compare(const shared_ptr<IHittable> &a, const shared_ptr<IHittable> &b) {
    return box_compare(a, b, 0);
}

bool box_y_compare(const shared_ptr<IHittable> &a, const shared_ptr<IHittable> &b) {
    return box_compare(a, b, 1);
}

bool box_z_compare(const shared_ptr<IHittable> &a, const shared_ptr<IHittable> &b) {
    return box_compare(a, b, 2);
}

bool box_compare(const shared_ptr<IHittable> &a, const shared_ptr<IHittable> &b, int axis) {
    AABB box_a;
    AABB box_b;

    if (!a->BoundingBox(0,0, box_a) || !b->BoundingBox(0,0, box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a.Min()[axis] < box_b.Min()[axis];
}
