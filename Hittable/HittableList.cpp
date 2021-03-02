//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: HittableList.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/
#include "../stdafx.h"
#include "HittableList.h"
#include "../AABB.h"

HittableList::HittableList(std::shared_ptr<IHittable> const & object) {
    Add(object);
}

void HittableList::Clear() {
    objects.clear();
}

void HittableList::Add(std::shared_ptr<IHittable> const & object) {
    objects.emplace_back(object);
}

bool HittableList::Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for(const auto& object : objects)
    {
        if(object->Hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

bool HittableList::BoundingBox(double time0, double time1, AABB &output_box) const {
    if(objects.empty()) return false;

    AABB tempBox;
    bool firstBox = true;

    for(const auto& object : objects)
    {
        if(!object->BoundingBox(time0, time1, tempBox)) return false;
        output_box = firstBox ? tempBox : SurroundingBox(output_box, tempBox);
        firstBox = false;
    }
    return true;
}
