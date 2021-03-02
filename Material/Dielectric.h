//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Dielectric.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/


#ifndef GNU_DIELECTRIC_H
#define GNU_DIELECTRIC_H
#include "Material.h"

class Dielectric : public Material {
public:
    Dielectric(double indexOfRefreaction);

    bool Scatter(const Ray &r_in, const HitRecord &rec, vec3 &attenuation, Ray &scattered) const override;

public:
    static double Reflectance(double consine, double ref_idx);
    double ir; // Index of Refraction
};


#endif //GNU_DIELECTRIC_H
