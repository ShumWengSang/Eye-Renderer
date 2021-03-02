//
// Created by user on 3/1/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Translate.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 3/1/2021
 * End Header --------------------------------------------------------*/
#include "../stdafx.h"
#include "Translate.h"
#include "../Ray.h"
#include "../AABB.h"

Translate::Translate(const shared_ptr<IHittable> &p, const vec3 &displacement) : ptr(p), offset(displacement) {

}

bool Translate::Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    Ray moved_r (r.Origin() - offset, r.Direction(), r.Time());
    if(!ptr->Hit(moved_r, t_min, t_max, rec))
        return false;
    rec.p += offset;
    rec.SetFaceNormal(moved_r, rec.normal);
    return true;
}

bool Translate::BoundingBox(double time0, double time1, AABB &outputBox) const {
    if(!ptr->BoundingBox(time0, time1, outputBox))
        return false;
    outputBox = AABB(outputBox.Min() + offset, outputBox.Max() + offset);
    return true;
}

bool Rotate_Y::Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    auto origin = r.Origin();
    auto direction = r.Direction();

    origin[0] = cos_theta * r.Origin()[0] - sin_theta * r.Origin()[2];
    origin[2] = sin_theta * r.Origin()[0] + cos_theta * r.Origin()[2];

    direction[0] = cos_theta * r.Direction()[0] - sin_theta * r.Direction()[2];
    direction[2] = sin_theta * r.Direction()[0] + cos_theta * r.Direction()[2];

    Ray rotated_r(origin, direction, r.Time());

    if(!ptr->Hit(rotated_r, t_min, t_max, rec))
        return false;

    auto p = rec.p;
    auto normal = rec.normal;

    p[0] =  cos_theta * rec.p[0] + sin_theta * rec.p[2];
    p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

    normal[0] =  cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
    normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

    rec.p = p;
    rec.SetFaceNormal(rotated_r, normal);
    return true;
}

bool Rotate_Y::BoundingBox(double time0, double tim1, AABB &outputBox) const {
    outputBox = bbox;
    return hasBox;
}

Rotate_Y::Rotate_Y(shared_ptr<IHittable> const & p, double degreeAngles) : ptr(p) {
    auto radians = glm::radians(degreeAngles);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    hasBox = ptr->BoundingBox(0, 1, bbox);

    vec3 min(infinity, infinity, infinity);
    vec3 max(-infinity, -infinity, -infinity);

    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 2; ++j)
        {
            for(int k = 0; k < 2; ++k)
            {
                auto x = i * bbox.Max().x + (1 - i) * bbox.Min().x;
                auto y = j * bbox.Max().y + (1 - j) * bbox.Min().y;
                auto z = k * bbox.Max().z + (1 - k) * bbox.Min().z;

                auto newx = cos_theta * x + sin_theta * z;
                auto newz = -sin_theta * x + cos_theta * z;

                vec3 tester(newx, y, newz);

                for(int c = 0; c < 3; ++c)
                {
                    min[c] = std::min(min[c], tester[c]);
                    max[c] = std::max(max[c], tester[c]);
                }
            }
        }
    }

    bbox = AABB(min, max);
}
