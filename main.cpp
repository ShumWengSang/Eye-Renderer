
#include "stdafx.h"
#include "Ray.h"
#include "IHittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

void writeColor(std::ostream& out, vec3 pixelColor, int samplesPerPixel)
{
    auto r = pixelColor.r;
    auto g = pixelColor.g;
    auto b = pixelColor.b;

    // Divde the color by the number of samples
    auto scale = 1.0 / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>( 256 * std::clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>( 256 * std::clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>( 256 * std::clamp(b, 0.0, 0.999)) << '\n';
}

vec3 RayColor(Ray const & r, const IHittable& world, int depth)
{
    // Exceed depth, no more light gathered
    if(depth <= 0)
        return vec3(0);

    HitRecord rec;
    if(world.Hit(r, 0.001, infinity, rec))
    {
        Ray scattered;
        vec3 attenuation;
        if(rec.matPtr->Scatter(r, rec, attenuation, scattered))
        {
            return attenuation * RayColor(scattered, world, depth - 1);
        }
        return vec3(0);
    }
    vec3 UnitDirection = glm::normalize(r.Direction());
    double t = 0.5 * (UnitDirection.y + 1.0);
    return (1.0 - t) * vec3(1.0) + t * vec3(0.5, 0.7, 1.0);
}

HittableList randomScene()
{
    HittableList world;
    auto materialGround = std::make_shared<Lambertian>(vec3(0.5,0.5,0.5));
    world.Add(make_shared<Sphere>(vec3(0, -1000, 0), 1000, materialGround));

    for(int i = 0; i < 11; ++i)
    {
        for(int j = 0; j < 11; ++j)
        {
            double chooseMatRand = randomDouble();
            vec3 center(i + 0.9 * randomDouble(), 0.2, j + 0.9 * randomDouble());

            if(glm::distance(vec3(4,0.2,0), center) > 0.9)
            {
                shared_ptr<Material> sphereMat;

                if(chooseMatRand < 0.8)
                {
                    // Diffuse
                    auto albedo = randomVec3() * randomVec3();
                    sphereMat = make_shared<Lambertian>(albedo);
                }
                else if(chooseMatRand < 0.95)
                {
                    // Metal
                    auto albedo = randomVec3(0.5,1);
                    auto fuzz = randomDouble(0, 0.5);
                    sphereMat = make_shared<Metal>(albedo, fuzz);
                }
                else
                {
                    // Glass
                    sphereMat = make_shared<Dielectric>(1.5);
                }
                world.Add(make_shared<Sphere>(center, 0.2, sphereMat));
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.Add(make_shared<Sphere>(vec3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(vec3(0.4, 0.2, 0.1));
    world.Add(make_shared<Sphere>(vec3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(vec3(0.7, 0.6, 0.5), 0.0);
    world.Add(make_shared<Sphere>(vec3(4, 1, 0), 1.0, material3));

    return world;
}

int main() {
    // Image
    const float aspectRatio = 3.0 / 2.0;
    const int imageWidth = 1200;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 500;
    const int maxDepth = 50;

    // World
    HittableList world = randomScene();


    // Camera
    const vec3 lookFrom(13,2,3);
    const vec3 lookAt(0,0,0);
    const vec3 up(0, 1,0);
    const auto distanceToFocus = 10.0;
    const auto aperture = 0.1;

    Camera cam(lookFrom, lookAt, up, aspectRatio, 20.0, aperture, distanceToFocus);

    // Render
    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    for (int j = imageHeight - 1; j >= 0; j--)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i < imageWidth; ++i) {

            vec3 color(0);
            for(int s = 0; s < samplesPerPixel; ++s) {
                auto u = (i + randomDouble()) / (imageWidth - 1);
                auto v = (j + randomDouble()) / (imageHeight - 1);

                Ray r = cam.getRay(u,v);
                color += RayColor(r, world, maxDepth);
            }
            writeColor(std::cout, color, samplesPerPixel);
        }
    }

    return 0;
}
