//
// Created by user on 3/1/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: XY_Rect.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 3/1/2021
 * End Header --------------------------------------------------------*/


#ifndef EYE_AARECT_H
#define EYE_AARECT_H
#include "IHittable.h"
class Material;
class XY_Rect : public IHittable {
public:
    XY_Rect() = default;
    XY_Rect(double x0, double x1, double y0, double y1, double k, shared_ptr<Material> const & mat);
    bool Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
    bool BoundingBox(double time0, double tim1, AABB &outputBox) const override;

public:
    shared_ptr<Material> mp;
    double x0 = 0, x1 = 0, y0 = 0, y1 = 0, k = 0;
};

class XZ_Rect : public IHittable {
public:
    XZ_Rect() = default;
    XZ_Rect(double x0, double x1, double z0, double z1, double k, shared_ptr<Material> const & mat);
    bool Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
    bool BoundingBox(double time0, double tim1, AABB &outputBox) const override;
public:
    shared_ptr<Material> mp;
    double x0 = 0, x1 = 0, z0 = 0, z1 = 0, k = 0;
};

class YZ_Rect : public IHittable {
public:
    YZ_Rect() = default;
    YZ_Rect(double y0, double y1, double z0, double z1, double k, shared_ptr<Material> const & mat);
    bool Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
    bool BoundingBox(double time0, double tim1, AABB &outputBox) const override;
public:
    shared_ptr<Material> mp;
    double y0 = 0, y1 = 0, z0 = 0, z1 = 0, k = 0;
};

#endif //EYE_AARECT_H
