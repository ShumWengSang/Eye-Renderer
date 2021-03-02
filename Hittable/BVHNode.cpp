//
// Created by user on 2/28/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: BVHNode.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: Eye
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/28/2021
 * End Header --------------------------------------------------------*/
#include "../stdafx.h"
#include "BVHNode.h"
#include "HittableList.h"

BVHNode::BVHNode(const HittableList &list, double time0, double time1) : BVHNode(list.objects, 0, list.objects.size(),
                                                                                 time0, time1){

}

BVHNode::BVHNode(
        const std::vector<shared_ptr<IHittable>> &srcObjects, size_t start, size_t end, double time0, double time1
                ) {
    auto objects = srcObjects; // Modifiable local copy

    int axis = randomInt();
    auto comparator = (axis == 0) ? box_x_compare
                                  : (axis == 1) ? box_y_compare
                                                : box_z_compare;
    size_t objectSpan = end - start;

    if(objectSpan == 1)
    {
        left = right = objects[start];
    }
    else if(objectSpan = 2)
    {
        if(comparator(objects[start], objects[start + 1]))
        {
            left = objects[start];
            right = objects[start + 1];
        }
        else
        {
            left = objects[start + 1];
            right = objects[start];
        }
    }
    else
    {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);
        auto mid = start + (objectSpan / 2);
        left = std::make_shared<BVHNode>(objects, start, mid, time0, time1);
        right = std::make_shared<BVHNode>(objects, mid, end, time0, time1);
    }

    AABB leftBox, rightBox;
    if(!left->BoundingBox(time0, time1, leftBox)
    || !right->BoundingBox(time0, time1, rightBox))
        std::cerr << "No boundinb box in bvh_node constructor.\n";
    box = SurroundingBox(leftBox, rightBox);
}

bool BVHNode::Hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    if(!box.Hit(r, t_min, t_max))
        return false;
    bool hit_left = left->Hit(r, t_min, t_max, rec);
    bool hit_right = right->Hit(r, t_min, t_max, rec);

    return hit_left || hit_right;
}

bool BVHNode::BoundingBox(double time0, double tim1, AABB &outputBox) const {
    outputBox = box;
    return true;
}
