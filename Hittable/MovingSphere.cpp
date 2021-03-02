//
// Created by user on 2/28/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: MovingSphere.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/28/2021
 * End Header --------------------------------------------------------*/
#include "../stdafx.h"
#include "MovingSphere.h"
#include "../Material/Material.h"
#include "../Ray.h"
#include "../AABB.h"

MovingSphere::MovingSphere(vec3 cen0, vec3 cen1, double time0, double time1, double r, shared_ptr<Material> const & m)
    : center0(cen0), center1(cen1), time0(time0), time1(time1), radius(r), matPtr(m)
{

}

bool MovingSphere::Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    vec3 oc = r.Origin() - center(r.Time());

    // A simplified quadratic equation where 2 * half_b = b
    auto a = glm::length2(r.Direction());
    auto half_b = glm::dot(oc, r.Direction());
    auto c = glm::length2(oc) - radius * radius;
    ;
    float discriminant = half_b * half_b - a * c;
    if(discriminant < 0)
    {
        return false;
    }

    // Find the nearest root that lies in acceptable range
    auto sqrtd = sqrt(discriminant);
    auto root = (-half_b - sqrtd) / a;
    if(root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;
        if(root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.At(root);

    vec3 outwardNormal = (rec.p - center(r.Time())) / radius;
    rec.SetFaceNormal(r, outwardNormal);
    rec.matPtr = matPtr;
    return true;
}

vec3 MovingSphere::center(double time) const {
    // Linear interpolation between c0 and c1
    return center0 + ((time - time0) / (time1 - time0) * (center1 - center0));
}

bool MovingSphere::BoundingBox(double time0, double time1, AABB &outputBox) const {
    AABB box0(
            center(time0) - vec3(radius, radius, radius),
            center(time0) + vec3(radius, radius, radius));
    AABB box1(
            center(time1) - vec3(radius, radius, radius),
            center(time1) + vec3(radius, radius, radius));
    outputBox = SurroundingBox(box0, box1);
    return true;
}
