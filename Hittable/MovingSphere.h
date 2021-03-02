//
// Created by user on 2/28/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: MovingSphere.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/28/2021
 * End Header --------------------------------------------------------*/


#ifndef EYE_MOVINGSPHERE_H
#define EYE_MOVINGSPHERE_H

#include "IHittable.h"

class MovingSphere : public IHittable{
public:
    MovingSphere() = default;
    MovingSphere(vec3 cen0, vec3 cen1, double time0, double time1, double r, shared_ptr<Material> const & m);
    bool Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
    bool BoundingBox(double time0, double time1, AABB &outputBox) const override;
    vec3 center(double time) const;

public:
    vec3 center0, center1;
    double time0, time1;
    double radius;
    shared_ptr<Material> matPtr;
};


#endif //EYE_MOVINGSPHERE_H
