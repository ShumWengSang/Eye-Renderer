//
// Created by user on 3/1/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: ImageTexture.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 3/1/2021
 * End Header --------------------------------------------------------*/


#ifndef EYE_IMAGETEXTURE_H
#define EYE_IMAGETEXTURE_H
#include "Texture.h"

class ImageTexture : public Texture {
public:
    const static int bytesPerPixel = 3;

    ImageTexture() = default;
    explicit ImageTexture(const char* filename);
    ~ImageTexture();

    Color Value(double u , double v, vec3 const & p) const override;
private:
    unsigned char *data = nullptr;
    int width = 0, height = 0;
    int bytesPerScanLine = 0;
};


#endif //EYE_IMAGETEXTURE_H
