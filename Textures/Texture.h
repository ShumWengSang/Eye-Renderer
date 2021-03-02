//
// Created by user on 2/28/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Texture.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/28/2021
 * End Header --------------------------------------------------------*/


#ifndef EYE_TEXTURE_H
#define EYE_TEXTURE_H


class Texture {
public:
    virtual Color Value(double u, double v, vec3 const & p) const = 0;
};

class SolidColor: public Texture {
public:
    SolidColor() = default;
    SolidColor(Color c);
    SolidColor(double red, double green, double blue);

    virtual Color Value(double u, double v, vec3 const & p) const override;
private:
    Color colorValue;
};

class CheckerTexture : public Texture{
public:
    CheckerTexture() = default;
    CheckerTexture(shared_ptr<Texture> const & even, shared_ptr<Texture> const & odd);
    CheckerTexture(Color c1, Color c2);

    virtual Color Value(double u, double v, vec3 const & p) const override;

public:
    shared_ptr<Texture> odd;
    shared_ptr<Texture> even;
};


#endif //EYE_TEXTURE_H
