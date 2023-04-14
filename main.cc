#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

double hit_sphere(const point3& center, double radius, const ray& r){
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;
    if(discriminant < 0){
        return -1.0;
    }
    else{
        return (-half_b - sqrt(discriminant))/ a;
    }
}

color ray_color(const ray& r){
    point3 sphereOrigin = point3(0,0,-1);
    double radius = 0.5;
    auto t = hit_sphere(sphereOrigin, radius , r);
    if(t > 0.0){
        vec3 N = unit_vector(r.at(t) - sphereOrigin);
        return 0.5*color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    //background --- did not hit the sphere
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    //linear interpolation
    // blendedValue = (1 - t)*startValue + t*endValue
    return (1.0-t)*color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
}

using namespace std;

int main(){
    // Image
    const auto aspect_ratio = 16.0/9.0;
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0,0,0);
    auto horizontal = vec3(viewport_width,0,0);
    auto vertical = vec3(0,viewport_height,0);
    auto lower_left_corner  = origin - horizontal/2 - vertical/2 - vec3(0,0,focal_length);

    // Render

    cout << "P3\n" << image_width << ' ' << image_height << "\n 256\n";

    for(int j = image_height-1; j >= 0; --j){
        cerr << "\rScanlines remaining: " << j << ' ' << flush;
        for(int i = 0 ; i < image_width; ++i){
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(cout, pixel_color);
        }
    }
    cerr << "\nDone.\n";
}