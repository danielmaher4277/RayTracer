/// Include the image write library and enable it
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/// Uncomment these lines if you want to debug using couts
#include <iostream>

#include<vector>
#include<algorithm>

///Create local reference with "", to file
#include "Vector3.hpp"
#include "Triangle.hpp"
#include "file_util.h"
using namespace std;


  /// Width of the final image
  const int w = 640;

  /// Height of the final image
  const int h = 640;

  /// The 1d array for storing the pixel we have generated
  unsigned char pixels[w * h * 3];

  Triangle triangle01 = Triangle{Vector3{-1, 1, -2}, Vector3{-1, 1, -1}, Vector3{-1, -1, -2}};
  Triangle triangle02 = Triangle{Vector3{-1, 1, -1}, Vector3{-1, -1, -1}, Vector3{-1, -1, -2}};

  // Right Wall
  Triangle triangle03 = Triangle{Vector3{1, 1, -1}, Vector3{1, 1, -2}, Vector3{1, -1, -2}};
  Triangle triangle04 = Triangle{Vector3{1, -1, -1}, Vector3{1, 1, -1}, Vector3{1, -1, -2}};

  // Top Wall
  Triangle triangle05 = Triangle{Vector3{-1, 1, -1}, Vector3{-1, 1, -2}, Vector3{1, 1, -2}};
  Triangle triangle06 = Triangle{Vector3{1, 1, -1}, Vector3{-1, 1, -1}, Vector3{1, 1, -2}};

  // Bottom Wall
  Triangle triangle07 = Triangle{Vector3{-1, -1, -2}, Vector3{-1, -1, -1}, Vector3{1, -1, -2}};
  Triangle triangle08 = Triangle{Vector3{-1, -1, -1}, Vector3{1, -1, -1}, Vector3{1, -1, -2}};

  // Back Wall
  Triangle triangle09 = Triangle{Vector3{-1, 1, -2}, Vector3{-1, -1, -2}, Vector3{1, -1, -2}};
  Triangle triangle10 = Triangle{Vector3{1, 1, -2}, Vector3{-1, 1, -2}, Vector3{1, -1, -2}};

  vector<Triangle> triangles = {
      triangle01, triangle02,
      triangle03, triangle04,
      triangle05, triangle06,
      triangle07, triangle08,
      triangle09, triangle10};

  Vector3 background_color = Vector3{0,0,0};

Vector3 infinity = {10000000

Vector3 traceRayDistance(Vector3 origin, Vector3 direction){
    Vector3 color = {}


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

      ///FarPlane
      float closest_t = 10000000;


      for(const Triangle &triangle : triangles){

      
      
      Vector3 edge_one = triangle.one - triangle.two;
      Vector3 edge_two = triangle.three - triangle.two;
      Vector3 p = edge_two.cross(edge_one);
      Vector3 abc = p.normalize();
      float d = -abc.dot(triangle.one);

      float t = -(abc.dot(camera_origin)+d)/abc.dot(ray);

      if(t > closest_t || t<= 0)
        continue;
      

      
      Vector3 collision_point = ray * t + camera_origin;

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

        closest_t = t;

        Vector3 baseColor = Vector3{255, 255, 255};

        Vector3 lightDirection = Vector3{.5, 1, .1}.normalize();


        Vector3 ambient = baseColor * .1;
        Vector3 normal = p.normalize();

        float strength = max(0.f, lightDirection.dot(normal));

        Vector3 diffuse = baseColor * strength;
        Vector3 reflective = Vector3{0,0,0};

        Vector3 _color = ambient + diffuse + reflective;

        color = _color;

        r = color.x;
        g = color.y;
        b = color.z;
      }
    }
    return closest_t;
  };


  Vector3 traceRay(Vector3 origin, Vector3 direction, int Bounces = 2){
    Vector3 color = {}

    if(Bounces == 0){}


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

      ///FarPlane
      float closest_t = 10000000;


      for(const Triangle &triangle : triangles){

      
      
      Vector3 edge_one = triangle.one - triangle.two;
      Vector3 edge_two = triangle.three - triangle.two;
      Vector3 p = edge_two.cross(edge_one);
      Vector3 abc = p.normalize();
      float d = -abc.dot(triangle.one);

      float t = -(abc.dot(camera_origin)+d)/abc.dot(ray);

      if(t > closest_t || t<= 0)
        continue;
      

      
      Vector3 collision_point = ray * t + camera_origin;

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

        closest_t = t;

        Vector3 baseColor = Vector3{255, 255, 255};

        Vector3 lightDirection = Vector3{.5, 1, .1}.normalize();


        Vector3 ambient = baseColor * .1;
        Vector3 normal = p.normalize();

        float strength = max(0.f, lightDirection.dot(normal));

        Vector3 diffuse = baseColor * strength;
        Vector3 reflective = Vector3{0,0,0};

        Vector3 _color = ambient + diffuse + reflective;

        color = _color;

        r = color.x;
        g = color.y;
        b = color.z;
      }
    }
    return color;
  };


int main()
{
  /// Example of how to debug with couts. 
  /// You must uncomment the include and namespace lines above
  //cout << "Hello, world" << endl;


  Vector3 temp = Vector3{0,0,0};

  temp += Vector3{1,1,1};

  //cout << temp << endl;

    Vector3 origin = Vector3{0, 0, 1};
    Vector3 camera_look_at = Vector3{0, 0, 0};
    Vector3 camera_up = Vector3{0, 1, 0};





      pixels[index] = r;
      pixels[index + 1] = g;
      pixels[index + 2] = b;

      
    
  }
  }

  ///Write the final image as a png
  stbi_write_png("image.png", w, h, 3, pixels, w * 3);
  return 0;
}


class Parser{
  public:

  string NameOfFileToParse;

  string fileContents;

  //fileContents = (NameOfFileToParse).Read();
  
  //fileContents.strip()

  //Place lines from file into corresponding lists below, seperating them using spaces and newlines.
  
  //actual vectors
  //Vertices
  vector<Vector3> v = {};

  //actual vectors
  //Normals
  vector<Vector3> vn = {};

  //z always = 0, otherwise actual vector
  //Texture info
  vector<Vector3> vt = {};

  //Vector3's whos values represent indexes of the above lists. IE f = {{5, 1, 1},c{3, 2, 2}}
  //f = {{5, 1, 1}} = the face represented by this vec3 is made up of vertice index 5, normal index 1, and texture index 1. 
  vector<Vector3> f = {};
};