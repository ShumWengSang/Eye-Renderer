#define STB_IMAGE_IMPLEMENTATION
#include "stdafx.h"
#include "Ray.h"
#include "Hittable/IHittable.h"
#include "Hittable/HittableList.h"
#include "Hittable/Sphere.h"
#include "Camera.h"
#include "Material/Material.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"
#include "Hittable/MovingSphere.h"
#include "Textures/Texture.h"
#include "Textures/NoiseTexture.h"
#include "Textures/ImageTexture.h"
#include "Hittable/AARect.h"
#include "Material/DiffuseLight.h"
#include "Hittable/Box.h"
#include "Hittable/Translate.h"
#include "Hittable/BVHNode.h"

using Array2D = std::vector<std::vector<glm::ivec3>>;

void writeColor(std::ostream& out, Color const & element)
{
       out  << element.x << ' '
            << element.y << ' '
            << element.z << '\n';
}

void writeColor(glm::ivec3& out, vec3 pixelColor, int samplesPerPixel)
{
    auto r = pixelColor.r;
    auto g = pixelColor.g;
    auto b = pixelColor.b;

    // Divde the color by the number of samples
    auto scale = 1.0 / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out.x = static_cast<int>( 256 * std::clamp(r, 0.0, 0.999));
    out.y = static_cast<int>( 256 * std::clamp(g, 0.0, 0.999));
    out.z = static_cast<int>( 256 * std::clamp(b, 0.0, 0.999));

/*    out << static_cast<int>( 256 * std::clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>( 256 * std::clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>( 256 * std::clamp(b, 0.0, 0.999)) << '\n';*/
}

Color RayColor(Ray const & r, Color const & background, const IHittable& world, int depth)
{
    // Exceed depth, no more light gathered
    if(depth <= 0)
        return Color(0);

    // If the ray hits nothing, return background color
    HitRecord rec;
    if(!world.Hit(r, 0.001, infinity, rec))
        return background;

    Ray scattered;
    Color attenuation;
    Color emitted = rec.matPtr->Emitted(rec.u, rec.v, rec.p);

    if(!rec.matPtr->Scatter(r, rec, attenuation, scattered))
    {
        return emitted;
    }
    return emitted + attenuation * RayColor(scattered, background, world, depth - 1);
}

HittableList Earth()
{
    auto earthTexture = make_shared<ImageTexture>("assets/earthmap.jpg");
    auto earthSurface = make_shared<Lambertian>(earthTexture);
    auto globe = make_shared<Sphere>(vec3(0,0,0), 2, earthSurface);
    return HittableList(globe);
}

HittableList randomScene()
{
    HittableList world;
    auto checker = make_shared<CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
    world.Add(make_shared<Sphere>(vec3(0,-1000,0), 1000, make_shared<Lambertian>(checker)));

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
                    auto center2 = center + vec3(0, randomDouble(0,.5), 0);
                    world.Add(make_shared<MovingSphere>(
                            center, center2, 0.0, 1.0, 0.2, sphereMat));
                }
                else if(chooseMatRand < 0.95)
                {
                    // Metal
                    auto albedo = randomVec3(0.5,1);
                    auto fuzz = randomDouble(0, 0.5);
                    sphereMat = make_shared<Metal>(albedo, fuzz);
                    world.Add(make_shared<Sphere>(center, 0.2, sphereMat));
                }
                else
                {
                    // Glass
                    sphereMat = make_shared<Dielectric>(1.5);
                    world.Add(make_shared<Sphere>(center, 0.2, sphereMat));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.Add(make_shared<Sphere>(vec3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(vec3(0.4, 0.2, 0.1));
    world.Add(make_shared<Sphere>(vec3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(vec3(0.7, 0.6, 0.5), 0.0);
    world.Add(make_shared<Sphere>(vec3(4, 1, 0), 1.0, material3));

    return HittableList(make_shared<BVHNode>(world, 0.0, 1.0));
}

HittableList TwoPerlinSpheres()
{
    HittableList objects;

    auto checker = make_shared<NoiseTexture>(4);
    objects.Add(make_shared<Sphere>(vec3(0, -1000, 0), 1000, make_shared<Lambertian>(checker)));
    objects.Add(make_shared<Sphere>(vec3(0, 2, 0), 2, make_shared<Lambertian>(checker)));

    return objects;
}

HittableList TwoSpheres()
{
    HittableList objects;

    auto checker = make_shared<CheckerTexture>();
    objects.Add(make_shared<Sphere>(vec3(0, -10, 0), 10, make_shared<Lambertian>(checker)));
    objects.Add(make_shared<Sphere>(vec3(0, 10, 0), 10, make_shared<Lambertian>(checker)));

    return objects;
}

HittableList SimpleLight()
{
    HittableList objects;

    auto pertext = make_shared<NoiseTexture>(4);
    objects.Add(make_shared<Sphere>(vec3(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));
    objects.Add(make_shared<Sphere>(vec3(0, 2, 0), 2, make_shared<Lambertian>(pertext)));

    auto diffLight = make_shared<DiffuseLight>(Color(4,4,4));
    objects.Add(make_shared<XY_Rect>(3,5,1,3,-2, diffLight));

    return objects;
}

HittableList Cornell_Box()
{
    HittableList objects;

    auto red = make_shared<Lambertian>(Color(0.65, 0.05, 0.05));
    auto white = make_shared<Lambertian>(Color(0.73,0.73,0.73));
    auto green = make_shared<Lambertian>(Color(.12, .45,0.15));
    auto light = make_shared<DiffuseLight>(Color(15, 15, 15));

    objects.Add(make_shared<YZ_Rect>(0, 555, 0, 555, 555, green));
    objects.Add(make_shared<YZ_Rect>(0, 555, 0, 555, 0, red));
    objects.Add(make_shared<XZ_Rect>(213, 343, 227, 332, 554, light));
    objects.Add(make_shared<XZ_Rect>(0, 555, 0, 555, 0, white));
    objects.Add(make_shared<XZ_Rect>(0, 555, 0, 555, 555, white));
    objects.Add(make_shared<XY_Rect>(0, 555, 0, 555, 555, white));

    shared_ptr<IHittable> box1 = make_shared<Box>(vec3(0,0,0), vec3(165, 330, 165), white);
    box1 = make_shared<Rotate_Y>(box1, 15);
    box1 = make_shared<Translate>(box1, vec3(265, 0, 295));
    objects.Add(box1);

    shared_ptr<IHittable> box2 = make_shared<Box>(vec3(0,0,0), vec3(165, 165, 165), white);
    box2 = make_shared<Rotate_Y>(box2, -18);
    box2 = make_shared<Translate>(box2, vec3(130, 0, 65));
    objects.Add(box2);

    // objects.Add(make_shared<Box>(vec3(130, 0, 65), vec3(295, 165, 230), white));
    // objects.Add(make_shared<Box>(vec3(265, 0, 295),vec3(430, 330, 460), white));

    return objects;
}

int main(void) {
    // Image
    float aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
    int samplesPerPixel = 100;
    int maxDepth = 50;
    Color background (0,0,0);

    // World
    HittableList world;

    // Camera
    vec3 lookFrom(13,2,3);
    vec3 lookAt(0,0,0);
    vec3 up(0, 1,0);
    auto distanceToFocus = 10.0;
    auto aperture = 0.1;
    auto fov = 20.0;

    switch (6) {
        case 1:
            world = randomScene();
            lookFrom = vec3(13,2,3);
            lookAt = vec3(0,0,0);
            fov = 20.0;
            aperture = 0.1;
            background = Color(0.70, 0.80, 1.00);
            break;

        case 2:
            world = TwoSpheres();
            lookFrom = vec3(13,2,3);
            lookAt = vec3(0,0,0);
            fov = 20.0;
            background = Color(0.70, 0.80, 1.00);
            break;
        case 3:
            world = TwoPerlinSpheres();
            lookFrom = vec3(13,2,3);
            lookAt = vec3(0,0,0);
            background = Color(0.70, 0.80, 1.00);
            fov = 20.0;
            break;
        case 4:
            world = Earth();
            lookFrom = vec3(13,2,3);
            lookAt = vec3(0,0,0);
            fov = 20.0;
            background = Color(0.70, 0.80, 1.00);
            break;
        case 5:
            world = SimpleLight();
            samplesPerPixel = 400;
            lookFrom = vec3(26,3,6);
            lookAt = vec3(0,2,0);
            fov = 20.0;
            background = Color(0,0,0);
            break;
        case 6:
            world = Cornell_Box();
            aspectRatio = 1.0;
            imageWidth = 600;
            samplesPerPixel = 200;
            lookFrom = vec3(278, 278, -800);
            lookAt = vec3(278, 278, 0);
            fov = 40.0;
            background = Color(0,0,0);
            break;
        default:
            break;
    }
    int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    Camera cam(lookFrom, lookAt, up, aspectRatio, fov, aperture, distanceToFocus, 0.0, 1.0);

    Array2D bufferArray (imageWidth, std::vector<glm::ivec3>(imageHeight, {0,0,0}));

    // Render
    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
 #pragma omp parallel for
    for (int j = imageHeight - 1; j >= 0; j--)
    {
        // std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i < imageWidth; ++i) {

            Color color(0);
            for(int s = 0; s < samplesPerPixel; ++s) {
                auto u = (i + randomDouble()) / (imageWidth - 1);
                auto v = (j + randomDouble()) / (imageHeight - 1);

                Ray r = cam.getRay(u,v);
                color += RayColor(r, background, world, maxDepth);
            }
            writeColor(bufferArray[i][j], color, samplesPerPixel);
        }
    }

    for (int j = imageHeight - 1; j >= 0; j--)
    {
        for(int i = 0; i < imageWidth; ++i)
        {
            writeColor(std::cout, bufferArray[i][j]);
        }
    }

    return 0;
}
