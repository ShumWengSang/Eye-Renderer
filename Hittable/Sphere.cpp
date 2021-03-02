//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Sphere.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/
#include "../stdafx.h"
#include "Sphere.h"
#include "../Ray.h"
#include "../AABB.h"

Sphere::Sphere(vec3 Center, double r, std::shared_ptr<Material> m) : center(Center), radius(r), matPtr(m){

}

bool Sphere::Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    vec3 oc = r.Origin() - center;

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

    vec3 outwardNormal = (rec.p - center) / radius;
    rec.SetFaceNormal(r, outwardNormal);
    rec.matPtr = matPtr;
    GetSphereUV(outwardNormal, rec.u, rec.v);
    return true;
}

bool Sphere::BoundingBox(double time0, double time1, AABB &outputBox) const {
    outputBox = AABB(
            center - vec3(radius, radius, radius),
            center + vec3(radius, radius, radius));
    return true;
}

void Sphere::GetSphereUV(const vec3 &p, double &u, double &v) {
    auto theta = acos(-p.y);
    auto phi = atan2(-p.z, p.x) + pi;
    u = phi / (2 * pi);
    v = theta / pi;
}
