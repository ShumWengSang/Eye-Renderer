//
// Created by user on 3/1/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: XY_Rect.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 3/1/2021
 * End Header --------------------------------------------------------*/
#include "../stdafx.h"
#include "AARect.h"
#include "../AABB.h"
#include "../Material/Material.h"
#include  "../Ray.h"

bool XY_Rect::Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    auto t = (k - r.Origin().z) / r.Direction().z;
    if(t < t_min || t > t_max)
        return false;

    auto x = r.Origin().x + t * r.Direction().x;
    auto y = r.Origin().y + t * r.Direction().y;

    if(x < x0 || x > x1 || y < y0 || y > y1)
        return false;

    // We have hit for sure now
    rec.u = (x - x0) / (x1 - x0); // Rectangle UV
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;

    auto outwardNormal = vec3(0,0,1);
    rec.SetFaceNormal(r, outwardNormal);
    rec.matPtr = mp;
    rec.p = r.At(t);
    return true;
}

bool XY_Rect::BoundingBox(double time0, double tim1, AABB &outputBox) const {
    // Bounding box must have non-zero width in each dimension, so pad the Z dimension
    outputBox = AABB(vec3(x0, y0, k - 0.001), vec3(x1, y1, k + 0.001));
    return true;
}

XY_Rect::XY_Rect(double x0, double x1, double y0, double y1, double k, shared_ptr<Material> const & mat)
    : x0(x0), x1(x1), y0(y0), y1(y1), k(k), mp(mat) {

}

XZ_Rect::XZ_Rect(double x0, double x1, double z0, double z1,double k, const shared_ptr<Material> &mat)
        : x0(x0), x1(x1), z0(z0), z1(z1), k(k), mp(mat) {

}

bool XZ_Rect::Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    auto t = (k - r.Origin().y) / r.Direction().y;
    if(t < t_min || t > t_max)
        return false;

    auto x = r.Origin().x + t * r.Direction().x;
    auto z = r.Origin().z + t * r.Direction().z;

    if(x < x0 || x > x1 || z < z0 || z > z1)
        return false;

    // We have hit for sure now
    rec.u = (x - x0) / (x1 - x0); // Rectangle UV
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;

    auto outwardNormal = vec3(0,1,0);
    rec.SetFaceNormal(r, outwardNormal);
    rec.matPtr = mp;
    rec.p = r.At(t);
    return true;
}

bool XZ_Rect::BoundingBox(double time0, double tim1, AABB &outputBox) const {
    outputBox = AABB(vec3(x0, k - 0.001, z0), vec3(x1, k + 0.001, z1));
    return true;
}

YZ_Rect::YZ_Rect(double y0, double y1, double z0, double z1, double k, const shared_ptr<Material> &mat)
    : y0(y0), y1(y1), z0(z0), z1(z1), k(k), mp(mat) {

}

bool YZ_Rect::Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    auto t = (k - r.Origin().x) / r.Direction().x;
    if(t < t_min || t > t_max)
        return false;

    auto z = r.Origin().z + t * r.Direction().z;
    auto y = r.Origin().y + t * r.Direction().y;

    if(y < y0 || y > y1 || z < z0 || z > z1)
        return false;

    // We have hit for sure now
    rec.u = (y - y0) / (y1 - y0); // Rectangle UV
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;

    auto outwardNormal = vec3(1,0,0);
    rec.SetFaceNormal(r, outwardNormal);
    rec.matPtr = mp;
    rec.p = r.At(t);
    return true;
}

bool YZ_Rect::BoundingBox(double time0, double tim1, AABB &outputBox) const {
    outputBox = AABB(vec3( k - 0.001, y0, z0), vec3(k + 0.001, y1, z1));
    return true;
}
