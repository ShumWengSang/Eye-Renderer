//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Ray.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/


#ifndef GNU_RAY_H
#define GNU_RAY_H
#include "glm/glm.hpp"

class Ray {
public:
    Ray(vec3 const & origin, vec3 const & direction, double time = 0.0);
    Ray() = default;
    vec3 Origin() const;
    vec3 Direction() const;
    vec3 At(double t) const;
    double Time() const;
public:
    vec3 origin;
    vec3 direction;
    double time;
};


#endif //GNU_RAY_H
