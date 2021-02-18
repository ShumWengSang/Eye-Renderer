cmake_minimum_required(VERSION 3.17)
project(Eye)

set(CMAKE_CXX_STANDARD 17)

add_executable(Eye main.cpp ray.cpp IHittable.cpp Sphere.cpp IHittable.cpp HittableList.cpp Camera.cpp Material.cpp
        Lambertian.cpp Metal.cpp Dielectric.cpp )
add_subdirectory(deps/)
target_link_libraries(Eye PRIVATE glm_static)