//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Metal.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/


#ifndef GNU_METAL_H
#define GNU_METAL_H
#include "Material.h"
#include "stdafx.h"

class Metal : public Material{
public:
    Metal(vec3 const & a, double f);

    bool Scatter(const Ray &r_in, const HitRecord &rec, vec3 &attenuation, Ray &scattered) const override;

public:
    vec3 albedo;
    double fuzziness;
};


#endif //GNU_METAL_H
