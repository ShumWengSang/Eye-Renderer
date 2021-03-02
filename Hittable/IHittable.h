//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: IHittable.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/


#ifndef GNU_IHITTABLE_H
#define GNU_IHITTABLE_H

class Ray;
class Material;
class AABB;

struct HitRecord
{
    vec3 p;
    vec3 normal;
    double t;
    double u;
    double v;

    bool frontFace;
    std::shared_ptr<Material> matPtr;
    void SetFaceNormal(Ray const & r, vec3 const & outwardNormal);
};

class IHittable {
public:
    virtual ~IHittable() = default;
    virtual bool Hit(Ray const & r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual bool BoundingBox(double time0, double tim1, AABB& outputBox) const = 0;
};


#endif //GNU_IHITTABLE_H
