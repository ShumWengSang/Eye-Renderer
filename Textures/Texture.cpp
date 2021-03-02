//
// Created by user on 2/28/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Texture.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/28/2021
 * End Header --------------------------------------------------------*/
#include "../stdafx.h"
#include "Texture.h"

SolidColor::SolidColor(Color c) : colorValue(c) {

}

SolidColor::SolidColor(double red, double green, double blue) : colorValue(red, green, blue){

}

Color SolidColor::Value(double u, double v, const vec3 &p) const {
    return colorValue;
}

CheckerTexture::CheckerTexture(const shared_ptr<Texture> &even, const shared_ptr<Texture> &odd) : even(even), odd(odd) {

}

CheckerTexture::CheckerTexture(Color c1, Color c2) : even(make_shared<SolidColor>(c1)), odd(make_shared<SolidColor>(c2)){

}

Color CheckerTexture::Value(double u, double v, const vec3 &p) const {
    auto sines = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
    if(sines < 0)
        return odd->Value(u,v,p);
    else
        return even->Value(u,v,p);
}
