//
// Created by user on 3/1/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Translate.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 3/1/2021
 * End Header --------------------------------------------------------*/


#ifndef EYE_TRANSLATE_H
#define EYE_TRANSLATE_H

#include "IHittable.h"
#include "../AABB.h"

class Translate : public IHittable {
public:
    Translate(shared_ptr<IHittable> const & p, vec3 const & displacement);

    bool Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    bool BoundingBox(double time0, double tim1, AABB &outputBox) const override;
public:
    shared_ptr<IHittable> ptr;
    vec3 offset;
};

class Rotate_Y : public IHittable {
public:
    Rotate_Y(shared_ptr<IHittable> const & p, double degreeAngles);

    bool Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    bool BoundingBox(double time0, double tim1, AABB &outputBox) const override;
public:
    shared_ptr<IHittable> ptr;
    double sin_theta;
    double cos_theta;
    bool hasBox;
    AABB bbox{};
};


#endif //EYE_TRANSLATE_H
