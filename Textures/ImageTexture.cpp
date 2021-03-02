//
// Created by user on 3/1/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: ImageTexture.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 3/1/2021
 * End Header --------------------------------------------------------*/
#include "../stdafx.h"
#include "ImageTexture.h"


ImageTexture::ImageTexture(const char *filename) {
    auto componentsPerPixel = bytesPerPixel;

    data = stbi_load(filename, &width, &height, &componentsPerPixel, componentsPerPixel);

    if(!data)
    {
        std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
        width = height = 0;
    }
    bytesPerScanLine = bytesPerPixel * width;
}

ImageTexture::~ImageTexture() {
    delete data;
}

Color ImageTexture::Value(double u, double v, const vec3 &p) const {
    // If no data, return cyan as debugging
    if(data == nullptr)
        return Color(0,1,1);

    // Clamp input texture coord to [0,1] x [1,0]
    u = std::clamp(u, 0.0, 1.0);
    v = 1.0 - std::clamp(v, 0.0, 1.0); // Flip V to image coordinates

    auto i = static_cast<int>(u * width);
    auto j = static_cast<int>(v * height);

    // Clamp integer mapping
    if(i >= width) i = width - 1;
    if(j >= height) j = height - 1;

    const auto colorScale = 1.0 / 255.0;
    auto pixel = data + j * bytesPerScanLine + i * bytesPerPixel;
    return colorScale * Color(pixel[0], pixel[1], pixel[2]);
}
