//
// Created by user on 3/1/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Box.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 3/1/2021
 * End Header --------------------------------------------------------*/
#include "../stdafx.h"
#include "Box.h"
#include "AARect.h"
#include "../Material/Material.h"
#include "../AABB.h"

bool Box::Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    return sides.Hit(r, t_min, t_max, rec);
}

bool Box::BoundingBox(double time0, double tim1, AABB &outputBox) const {
    outputBox = AABB(boxMin, boxMax);
    return true;
}

Box::Box(const vec3 &p0, const vec3 &p1, const shared_ptr<Material> &ptr) : boxMin(p0), boxMax(p1) {
    sides.Add(make_shared<XY_Rect>(p0.x, p1.x, p0.y, p1.y, p1.z, ptr));
    sides.Add(make_shared<XY_Rect>(p0.x, p1.x, p0.y, p1.y, p0.z, ptr));

    sides.Add(make_shared<XZ_Rect>(p0.x, p1.x, p0.z, p1.z, p1.y, ptr));
    sides.Add(make_shared<XZ_Rect>(p0.x, p1.x, p0.z, p1.z, p0.y, ptr));

    sides.Add(make_shared<YZ_Rect>(p0.y, p1.y, p0.z, p1.z, p1.x, ptr));
    sides.Add(make_shared<YZ_Rect>(p0.y, p1.y, p0.z, p1.z, p0.x, ptr));
}
