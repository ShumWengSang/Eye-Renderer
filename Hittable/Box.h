//
// Created by user on 3/1/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Box.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 3/1/2021
 * End Header --------------------------------------------------------*/


#ifndef EYE_BOX_H
#define EYE_BOX_H
#include "IHittable.h"
#include "HittableList.h"
class Material;

class Box : public IHittable {
public:
    Box() = default;
    Box(vec3 const & p0, vec3 const & p1, shared_ptr<Material> const & ptr);

    bool Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
    bool BoundingBox(double time0, double tim1, AABB &outputBox) const override;

public:
    vec3 boxMin;
    vec3 boxMax;
    HittableList sides;
};


#endif //EYE_BOX_H
