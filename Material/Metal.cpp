//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Metal.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/
#include "../stdafx.h"
#include "Metal.h"
#include "../Ray.h"
#include "../Hittable/IHittable.h"

bool Metal::Scatter(const Ray &r_in, const HitRecord &rec, vec3 &attenuation, Ray &scattered) const {
    vec3 reflected = Reflect(glm::normalize(r_in.Direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzziness * randomInSphere(), r_in.Time());
    attenuation = albedo;
    return glm::dot(scattered.Direction(), rec.normal) > 0;
}

Metal::Metal(const vec3 &a, double f) : albedo(a), fuzziness(f){

}
