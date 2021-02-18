//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Camera.cpp
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/
#include "stdafx.h"
#include "Camera.h"
#include "Ray.h"


Ray Camera::getRay(double s, double t) const {
    vec3 rd = lensRadius * RandomUnitDisk();
    vec3 offset = u * rd.x + v * rd.y;
    return Ray(origin + offset, lowerLeftCornor + s * horizontal + t * vertical - origin - offset);
}

Camera::Camera(vec3 lookFrom, vec3 lookAt, vec3 up, double aspectRatio, double fov, double aperture, double focusDist) {

    const double theta = degreesToRadians(fov);
    const double h = tan(theta/2);
    const double viewportHeight = 2.0 * h;
    const double viewportWidth = aspectRatio * viewportHeight;

    w = glm::normalize(lookFrom - lookAt);
    u = glm::normalize(glm::cross(up, w));
    v = cross(w,u);

    origin = lookFrom;
    horizontal = focusDist * viewportWidth * u;
    vertical = focusDist * viewportHeight * v;
    lowerLeftCornor = origin - (horizontal / 2.0) - (vertical / 2.0) - focusDist * w;

    lensRadius = aperture / 2;
}
