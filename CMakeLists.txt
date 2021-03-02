cmake_minimum_required(VERSION 3.17)
project(Eye)

set(MSVC_CXX_FLAGS "/openmp")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MSVC_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 17)

add_executable(Eye main.cpp ray.cpp Hittable/IHittable.cpp Hittable/Sphere.cpp Hittable/IHittable.cpp
        Hittable/HittableList.cpp Camera.cpp Material/Material.cpp
        Material/Lambertian.cpp Material/Metal.cpp Material/Dielectric.cpp Hittable/MovingSphere.cpp AABB.cpp
        Utility.cpp Hittable/BVHNode.cpp Textures/Texture.cpp Perlin.cpp
        Textures/NoiseTexture.cpp Textures/ImageTexture.cpp Material/DiffuseLight.cpp Hittable/AARect.cpp
        Hittable/Box.cpp Hittable/Translate.cpp Hittable/Translate.h)
add_subdirectory(deps/)
target_link_libraries(Eye PRIVATE glm_static)
target_link_libraries(Eye PRIVATE stb_image)

# Copy assets folder to cmake build
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
        )
add_dependencies(Eye copy_assets)