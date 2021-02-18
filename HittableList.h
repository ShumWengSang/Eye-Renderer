//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: HittableList.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/


#ifndef GNU_HITTABLELIST_H
#define GNU_HITTABLELIST_H
#include "IHittable.h"

class HittableList : public IHittable {
public:
    HittableList() = default;
    HittableList(std::shared_ptr<IHittable> object);

    void Clear();
    void Add(std::shared_ptr<IHittable> object);

    virtual bool Hit(Ray const & r, double t_min, double t_max, HitRecord& rec) const override;

public:
    std::vector<std::shared_ptr<IHittable>> objects;
};


#endif //GNU_HITTABLELIST_H
