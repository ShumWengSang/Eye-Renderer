//
// Created by user on 2/28/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: AABB.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/28/2021
 * End Header --------------------------------------------------------*/


#ifndef EYE_AABB_H
#define EYE_AABB_H

class Ray;

class AABB {
public:
    AABB() = default;
    AABB(vec3 const & min, vec3 const & max);
    vec3 Min() const;
    vec3 Max() const;

    bool Hit(Ray const & r, double tMin, double tMax) const;


    vec3 minimum;
    vec3 maximum;

};


#endif //EYE_AABB_H
