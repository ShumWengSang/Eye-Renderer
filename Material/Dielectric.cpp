//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Dielectric.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/
#include "../stdafx.h"
#include "Dielectric.h"
#include "../Hittable/IHittable.h"
#include "../Ray.h"

bool Dielectric::Scatter(const Ray &r_in, const HitRecord &rec, vec3 &attenuation, Ray &scattered) const {
    attenuation = vec3(1.0,1.0,1.0);
    double refractionRatio = rec.frontFace ? (1.0 / ir) : ir;

    vec3 rayDir = glm::normalize(r_in.Direction());
    double cos_theta = fmin(dot(-rayDir, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refractionRatio * sin_theta > 1.0;
    vec3 direction;

    if (cannot_refract || Reflectance(cos_theta, refractionRatio) > randomDouble())
        direction = Reflect(rayDir, rec.normal);
    else
        direction = Refract(-rayDir, rec.normal, refractionRatio);

    scattered = Ray(rec.p, direction, r_in.Time());
    return true;
}

Dielectric::Dielectric(double indexOfRefreaction) : ir(indexOfRefreaction){

}

double Dielectric::Reflectance(double cosine, double ref_idx) {
    // Use Schlick's approximation
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}
