/// Include the image write library and enable it
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// #include<vector>
//Create local reference with "", to file
// #include "Vector3.hpp"
// #include "Triangle.hpp"
// #include "file_util.h"

#include "Parser.hpp"
#include<iostream>
#include<algorithm>

using namespace std;




Parser parseObj;

vector<Triangle> triangles = parseObj.Parse("Untitled.obj");



/// Width of the final image
const int w = 640;

/// Height of the final image
const int h = 640;

/// Array for storing the pixel we have generated
unsigned char pixels[w * h * 3];

/// Background Color
Vector3 background_color = Vector3{100, 100, 255};







float trace_ray_distance(Vector3 origin, Vector3 direction){


    float closestT = INFINITY;

    for (const Triangle &triangle : triangles){

        Vector3 edge_one = triangle.one - triangle.two;
        Vector3 edge_two = triangle.three - triangle.two;
        Vector3 p = edge_two.cross(edge_one);
        Vector3 abc = p.normalize();
        float d = -abc.dot(triangle.one);

        float t = -(abc.dot(origin)+d)/abc.dot(direction);

        if(t > closestT || t <= 0)
          continue;
        
        Vector3 collision_point = direction * t + origin;

        Vector3 minus_one = collision_point - triangle.one;
        Vector3 minus_two = collision_point - triangle.two;
        Vector3 minus_three = collision_point - triangle.three;

        float triangle_area = p.length()/2;

        float area_one = minus_two.cross(minus_three).length()/2;
        float area_two = minus_three.cross(minus_one).length()/2;
        float area_three = minus_one.cross(minus_two).length()/2;


        float u = area_one/triangle_area;
        float v = area_two/triangle_area;
        float a = area_three/triangle_area;

        float sum = u + v + a;

        float diff = abs(1-sum);

        if(diff > .00001 || isnan(sum)){
          //not in triangle
        }
        else{
          //In triangle

          closestT = t;

        }
      }
    return closestT;


}




Vector3 trace_ray(Vector3 origin, Vector3 direction, int bounces = 2){
  

  Vector3 color = Vector3{background_color.x, background_color.y, background_color.z};
  
  if(bounces <= 0){
    return background_color;
  }

  float closestT = 1000000;

  for (const Triangle &triangle : triangles){
        Vector3 edge_one = triangle.one - triangle.two;
        Vector3 edge_two = triangle.three - triangle.two;
        Vector3 p = edge_two.cross(edge_one);
        Vector3 abc = p.normalize();
        float d = -abc.dot(triangle.one);

        float t = -(abc.dot(origin)+d)/abc.dot(direction);

        if(t > closestT || t <= 0)
          continue;
        
        Vector3 collision_point = direction * t + origin;

        Vector3 minus_one = collision_point - triangle.one;
        Vector3 minus_two = collision_point - triangle.two;
        Vector3 minus_three = collision_point - triangle.three;

        float triangle_area = p.length()/2;

        float area_one = minus_two.cross(minus_three).length()/2;
        float area_two = minus_three.cross(minus_one).length()/2;
        float area_three = minus_one.cross(minus_two).length()/2;


        float u = area_one/triangle_area;
        float v = area_two/triangle_area;
        float a = area_three/triangle_area;

        float sum = u + v + a;

        float diff = abs(1-sum);

        if(diff > .00001 || isnan(sum)){
          //not in triangle
        }
        else{
          //In triangle
          closestT = t;

          Vector3 base_color = Vector3{255, 255, 255};
          Vector3 light_direction = Vector3{-.5, 1, .5}.normalize();

          Vector3 ambient = base_color * .1;

          Vector3 normal = p.normalize();

          float strength = max(0.f, light_direction.dot(normal));

          Vector3 diffuse = base_color * strength;

          if(trace_ray_distance(collision_point, light_direction) != INFINITY){
            diffuse = Vector3{0,0,0};
          }

          Vector3 reflective = Vector3{0,0,0};

          if(true){
            Vector3 reflective_direction = direction - normal * 2 * normal.dot(direction);
            reflective = trace_ray(collision_point, reflective_direction, bounces -1) * .5;
            diffuse *= .5;
            ambient *= .5;
          }

          Vector3 _color = ambient + diffuse + reflective;

          color = _color;
        }
    }
    return color;
}






int main()
{

  Vector3 camera_origin = Vector3{0, 0, 1};
  Vector3 camera_look_at = Vector3{0, 0, 0};
  Vector3 camera_up = Vector3{0, 1, 0};


  /// Loop over each line doing down
  for (int y = 0; y < h; y++)
  {
    /// While going down, loop over every pixel going right
    for (int x = 0; x < w; x++)
    {

      int index = y * w * 3 + x * 3;

      unsigned char r = background_color.x;
      unsigned char g = background_color.y;
      unsigned char b = background_color.z;


      Vector3 target{x/(float)w * 2 -1, -(y/(float)h *2 -1), 0};

      Vector3 temp = (target - camera_origin);

      Vector3 ray = temp.normalize();

      Vector3 color = trace_ray(camera_origin, ray);

      r = color.x;
      g = color.y;
      b = color.z;



      pixels[index] = r;
      pixels[index + 1] = g;
      pixels[index + 2] = b;


    }
  }

  ///Write the final image as a png
  stbi_write_png("image.png", w, h, 3, pixels, w * 3);
  return 0;
}
