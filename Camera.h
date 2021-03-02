//
// Created by user on 2/15/2021.
//

/* Start Header -------------------------------------------------------
 * Copyright (C) 2020 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents without the prior
 * written consent of DigiPen Institute of Technology is prohibited.
 * File Name: Camera.h
 * Purpose: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Language: C++, G++
 * Platform: g++ (Ubuntu 9.3.0-10ubuntu2) 9.3, ThinkPad T430u, Nvidia GT 620M,
 *           OpenGL version string: 4.6.0 NVIDIA 390.138
 * Project: gnu
 * Author: Roland Shum, roland.shum@digipen.edu
 * Creation date: 2/15/2021
 * End Header --------------------------------------------------------*/


#ifndef GNU_CAMERA_H
#define GNU_CAMERA_H

class Ray;

class Camera {
public:
    Camera(vec3 lookFrom, vec3 lookAt, vec3 up, double aspectRatio, double fov, double aperture, double focusDist,
           double time0 = 0, double time1 = 0);
    Ray getRay(double s, double t) const;
private:
    vec3 origin;
    vec3 lowerLeftCornor;
    vec3 horizontal;
    vec3 vertical;

    vec3 u,v,w;
    double lensRadius;
    double time0, time1; //Shutter open/close times
};


#endif //GNU_CAMERA_H
