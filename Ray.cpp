//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Ray.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/
#include "stdafx.h"
#include "Ray.h"
Ray::Ray(const vec3 &orign, const vec3 &direction, double time)
    : origin(orign), direction(direction), time(time){

}

vec3 Ray::Origin() const {
    return origin;
}

vec3 Ray::Direction() const {
    return direction;
}

vec3 Ray::At(double t) const {
    return origin + t * direction;
}

double Ray::Time() const {
    return time;
}
