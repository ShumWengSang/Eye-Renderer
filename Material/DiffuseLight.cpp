//
// Created by user on 3/1/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: DiffuseLight.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 3/1/2021
 * End Header --------------------------------------------------------*/
#include "../stdafx.h"
#include "DiffuseLight.h"
#include "../Textures/Texture.h"

bool DiffuseLight::Scatter(const Ray &r_in, const HitRecord &rec, vec3 &attenuation, Ray &scattered) const {
    return false;
}

DiffuseLight::DiffuseLight(shared_ptr<Texture> const & a) : emit(a){

}

DiffuseLight::DiffuseLight(Color c) : emit(make_shared<SolidColor>(c)){

}

Color DiffuseLight::Emitted(double u, double v, const vec3 &p) const {
    return emit->Value(u , v, p);
}
