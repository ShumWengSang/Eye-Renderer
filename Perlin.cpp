//
// Created by user on 2/28/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Perlin.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/28/2021
 * End Header --------------------------------------------------------*/
#include "stdafx.h"
#include "Perlin.h"

Perlin::Perlin() {
    ranvec = new vec3[point_count];
    ranfloat = new double[point_count];
    for(int i = 0; i < point_count; ++i)
    {
        ranvec[i] = glm::normalize(randomVec3(-1, 1));
        ranfloat[i] = randomDouble();
    }
    perm_x = PerlineGeneratePerm();
    perm_y = PerlineGeneratePerm();
    perm_z = PerlineGeneratePerm();
}

Perlin::~Perlin() {
    delete[] ranfloat;
    delete[] perm_x;
    delete[] perm_y;
    delete[] perm_z;
    delete[] ranvec;
}

double Perlin::Noise(const vec3 &p) const {
    auto u = p.x - floor(p.x);
    auto v = p.y - floor(p.y);
    auto w = p.z - floor(p.z);

    auto i = static_cast<int>(floor(p.x));
    auto j = static_cast<int>(floor(p.y));
    auto k = static_cast<int>(floor(p.z));

    vec3 c[2][2][2];

    for(int di = 0; di < 2; di++)
    {
        for(int dj = 0; dj < 2; dj++)
        {
            for(int dk = 0; dk < 2; dk++)
            {
                c[di][dj][dk] = ranvec[
                        perm_x[ (i + di) & 255] ^
                        perm_y[ (j + dj) & 255] ^
                        perm_z[ (k + dk) & 255]
                        ];
            }
        }
    }

    return PerlinInterpolate(c, u, v, w);
}

int *Perlin::PerlineGeneratePerm() {
    // We can prob use std::generator here
    auto p = new int[point_count];
    for (int i = 0; i < Perlin::point_count; i++)
        p[i] = i;

    Permute(p, point_count);
    return p;
}

void Perlin::Permute(int *p, int n) {
    for (int i = n-1; i > 0; i--) {
        int target = randomInt(0, i);
        std::swap(p[i], p[target]);
    }
}

double Perlin::TrilinearInterpolate(double (*c)[2][2], double u, double v, double w) {
    auto accum = 0.0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                accum += (i * u + (1 - i) * (1 - u)) *
                         (j * v + (1 - j) * (1 - v)) *
                         (k * w + (1 - k) * (1 - w)) * c[i][j][k];
    return accum;
}

double Perlin::PerlinInterpolate(vec3 (*c)[2][2], double u, double v, double w) {
    // Hermite cubic
    auto uu = u * u * (3 - 2 * u);
    auto vv = v * v * (3 - 2 * v);
    auto ww = w * w * (3 - 2 * w);

    auto accum = 0.0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++) {
                vec3 weight_v(u - i, v - j, w - k);
                accum += (i * uu + (1 - i) * (1 - uu))
                         * (j * vv + (1 - j) * (1 - vv))
                         * (k * ww + (1 - k) * (1 - ww))
                         * dot(c[i][j][k], weight_v);
            }

    return accum;
}

double Perlin::Turbulance(const vec3 &p, int depth) const {
    auto accum = 0.0;
    auto temp_p = p;
    auto weight = 1.0;

    for(int i = 0; i < depth; ++i)
    {
        accum += weight * Noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }

    return fabs(accum);
}
