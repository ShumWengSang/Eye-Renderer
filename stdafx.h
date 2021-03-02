//
// Created by user on 2/15/2021.
//

#ifndef GNU_STDAFX_H
#define GNU_STDAFX_H
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/norm.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/epsilon.hpp"

#include "omp.h"

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <array>

#include "RawStbImage.h"

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265359;

using vec3 = glm::dvec3;
using Color = glm::dvec3;

#include "Utility.h"

#endif //GNU_STDAFX_H
