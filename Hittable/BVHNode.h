//
// Created by user on 2/28/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: BVHNode.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/28/2021
 * End Header --------------------------------------------------------*/


#ifndef EYE_BVHNODE_H
#define EYE_BVHNODE_H
#include "IHittable.h"
#include "../AABB.h"

class HittableList;
class BVHNode : public IHittable {
public:
    BVHNode() = default;
    BVHNode(HittableList const & list, double time0, double time1);

    BVHNode(
            std::vector<shared_ptr<IHittable>> const & srcObjects,
            size_t start, size_t end, double time0, double time1
            );
    virtual bool Hit(Ray const & r, double t_min, double t_max, HitRecord& rec) const override;
    virtual bool BoundingBox(double time0, double tim1, AABB& outputBox) const override;

public:
    shared_ptr<IHittable> left;
    shared_ptr<IHittable> right;
    AABB box;
};


#endif //EYE_BVHNODE_H
