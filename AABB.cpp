//
// Created by user on 2/28/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: AABB.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/28/2021
 * End Header --------------------------------------------------------*/
#include "stdafx.h"
#include "AABB.h"
#include "Ray.h"

AABB::AABB(const vec3 &min, const vec3 &max) : minimum(min), maximum(max){

}

vec3 AABB::Min() const {
    return this->minimum;
}

vec3 AABB::Max() const {
    return this->maximum;
}

bool AABB::Hit(const Ray &r, double tMin, double tMax) const {
    // Ray box intersection
    for(int i = 0; i < 3; i++)
    {
        auto invD = 1.0f / r.Direction()[i];
        double t0 = (Min()[i] - r.Origin()[i]) * invD;
        double t1 = (Max()[i] - r.Origin()[i]) * invD;

        if(invD < 0.0f)
            std::swap(t0, t1);

        tMin = std::max(t0, tMin);
        tMax = std::min(t1, tMax);

        if(tMax <= tMin)
            return false;
    }
    return true;
}
