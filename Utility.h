//
// Created by user on 2/28/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Utility.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/28/2021
 * End Header --------------------------------------------------------*/


#ifndef EYE_UTILITY_H
#define EYE_UTILITY_H


#include "Hittable/IHittable.h"

double degreesToRadians(double degrees);


// Random from [0,1)
double randomDouble();

double randomDouble(double min, double max);

float randomFloat();

float randomFloat(float min, float max);

vec3 randomVec3();

vec3 randomVec3(double min, double max);

vec3 randomInSphere();

vec3 randomUnitVector();

vec3 randomInHemisphere(vec3 const & normal);

bool vecNearZero(vec3 const & vec);

vec3 Reflect(vec3 const & v, vec3 const & n);

vec3 Refract(vec3 const & uv, vec3 const & n, double k);

vec3 RandomUnitDisk();

float randomInt();

float randomInt(float min, float max);

class AABB;
AABB SurroundingBox(AABB box0, AABB box1);

class IHittable;
bool box_compare(const shared_ptr<IHittable>& a, const shared_ptr<IHittable> &b, int axis);

bool box_x_compare (const shared_ptr<IHittable> &a, const shared_ptr<IHittable>& b);

bool box_y_compare (const shared_ptr<IHittable> &a, const shared_ptr<IHittable> &b);

bool box_z_compare (const shared_ptr<IHittable> &a, const shared_ptr<IHittable> &b);
#endif //EYE_UTILITY_H
