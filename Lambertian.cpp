//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Lambertian.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/
#include "stdafx.h"
#include "Lambertian.h"
#include "IHittable.h"
#include "Ray.h"

bool Lambertian::Scatter(const Ray &r_in, const HitRecord &rec, vec3 &attenuation, Ray &scattered) const {
    auto scatterDirection = rec.normal + randomUnitVector();

    // Catch degenerate scatter direction
    if(vecNearZero(scatterDirection))
    {
        scatterDirection = rec.normal;
    }

    scattered = Ray(rec.p, scatterDirection);
    attenuation = albedo;
    return true;
}

Lambertian::Lambertian(const vec3 &color) : albedo(color){

}
