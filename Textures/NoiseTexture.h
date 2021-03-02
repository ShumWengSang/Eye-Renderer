//
// Created by user on 2/28/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: NoiseTexture.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/28/2021
 * End Header --------------------------------------------------------*/


#ifndef EYE_NOISETEXTURE_H
#define EYE_NOISETEXTURE_H
#include "Texture.h"
#include "../Perlin.h"

class NoiseTexture : public Texture {
public:
    NoiseTexture() = default;
    NoiseTexture(double sc);
    virtual Color Value(double u, double v, vec3 const & p) const override;

public:
    Perlin noise;
    double scale;
};


#endif //EYE_NOISETEXTURE_H
