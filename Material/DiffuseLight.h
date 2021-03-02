//
// Created by user on 3/1/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: DiffuseLight.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 3/1/2021
 * End Header --------------------------------------------------------*/


#ifndef EYE_DIFFUSELIGHT_H
#define EYE_DIFFUSELIGHT_H
#include "Material.h"
class Texture;
class DiffuseLight : public Material {
public:
    explicit DiffuseLight(shared_ptr<Texture> const & a);
    explicit DiffuseLight(Color c);

    bool Scatter(const Ray &r_in, const HitRecord &rec, vec3 &attenuation, Ray &scattered) const override;
    Color Emitted(double u, double v, vec3 const & p) const override;
public:
    shared_ptr<Texture> emit;
};


#endif //EYE_DIFFUSELIGHT_H
