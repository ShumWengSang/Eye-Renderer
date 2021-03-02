//
// Created by user on 2/28/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Perlin.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/28/2021
 * End Header --------------------------------------------------------*/


#ifndef EYE_PERLIN_H
#define EYE_PERLIN_H


class Perlin {
public:
    Perlin();
    ~Perlin();
    double Noise(vec3 const & p) const;
    double Turbulance(vec3 const & p, int depth = 7) const;
private:
    static const int point_count = 256;
    double* ranfloat;
    int* perm_x;
    int* perm_y;
    int* perm_z;
    vec3 * ranvec;

    static int* PerlineGeneratePerm();
    static void Permute(int*p, int n);

    // Deprecated
    static double TrilinearInterpolate(double c[2][2][2], double u, double v, double w);
    static double PerlinInterpolate(vec3 c[2][2][2], double u, double v, double w);
};


#endif //EYE_PERLIN_H
