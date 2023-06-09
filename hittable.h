#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"
#include "aabb.h"

class material;

struct hit_record{
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    double t;
    double u;
    double v;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal){
        //the intuition for comparing the ray to the normal
        /*
        if (dot(ray_direction, outward_normal) > 0.0) {
            // ray is inside the sphere
            ...
        } else {
            // ray is outside the sphere
            ...
        }
        */
       // well how do we remember the normal?
       /*
       bool front_face;
        if (dot(ray_direction, outward_normal) > 0.0) {
            // ray is inside the sphere
            normal = -outward_normal;
            front_face = false;
        } else {
            // ray is outside the sphere
            normal = outward_normal;
            front_face = true;
        }*/
        
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable{
    public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const = 0;
};

#endif