//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Material.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/


#ifndef GNU_MATERIAL_H
#define GNU_MATERIAL_H

struct HitRecord;
class Ray;

class Material {
public:
    virtual bool Scatter(Ray const & r_in, HitRecord const & rec, vec3& attenuation, Ray& scattered) const = 0;
    virtual Color Emitted(double u, double v, vec3 const & p) const;
};


#endif //GNU_MATERIAL_H
