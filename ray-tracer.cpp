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



class Parser{
  public:

  

  vector<string> filecontentsholder = {};

  vector<string> temp5;
  vector<string> temp6;
  vector<string> temp7;
  int tempCounter = 0;
  int vectorYoureOn = 0;

  vector<string> posVectors_String;
  vector<float> posVectors_Float;
  vector<Vector3> posVectorsFinal;

  vector<string> texVectors_String;
  vector<float> texVectors_Float;
  vector<Vector3> texVectorsFinal;

  vector<string> normVectors_String;
  vector<float> normVectors_Float;
  vector<Vector3> normVectorsFinal;

  vector<string> corners_String;
  vector<float> corners_Float;
  vector<Vector3> cornersFinal;

  vector<Triangle> posTriangles;

  vector<Triangle> Parse(string NameOfFileToParse){


  ///Get Contents of object file

  filecontentsholder = readLines(NameOfFileToParse);


  ///Put lines into corresponding variables
  for(string line : filecontentsholder){
  
      const char delim = ' ';
  
      temp5 = split(line, delim);

      for(string string : temp5){

        if(string == "v"){
          posVectors_String.push_back(line);
          break;
        }
        if(string == "vt"){
          texVectors_String.push_back(line);
          break;
        }
        if(string == "vn"){
          normVectors_String.push_back(line);
          break;
        }
        if(string == "f"){
          corners_String.push_back(line);
          break;
        }
      }
  }




  ///Deliminating lines to extract float values from strings
  for(string line : posVectors_String){
    const char delim = ' ';
  
    temp6 = split(line, delim);

    for(string string : temp6){
      if(string != "v"){
        float tempFloat = std::stof(string);
        posVectors_Float.push_back(tempFloat);
      }
    }
  }

  for(string line : normVectors_String){
    const char delim = ' ';
  
    temp6 = split(line, delim);

    for(string string : temp6){
      if(string != "vn"){
        float tempFloat = std::stof(string);
        normVectors_Float.push_back(tempFloat);
      }
    }
  }

  for(string line : texVectors_String){
    const char delim = ' ';
  
    temp6 = split(line, delim);

    for(string string : temp6){
      if(string != "vt"){
        float tempFloat = std::stof(string);
        texVectors_Float.push_back(tempFloat);
      }
    }
  }

  ///Corners
  for(string line : corners_String){
    const char delim = ' ';
    const char delim2 = '/';
  
    temp6 = split(line, delim);

    for(string str : temp6){
      
        if(str != "f"){
          
          temp7 = split(str, delim2);
          
          
          for(string str2 : temp7){
            
            float tempFloat = std::stof(str2);
            corners_Float.push_back(tempFloat);  
          }

        }
    }
  }



  ///Creating Vec3's out of float list and pushing them to Vec3 Final Pos List

  int posVectorTempCounter1 = 0;
  int posVectorTempCounter2 = 1;
  int posVectorTempCounter3 = 2;

  for(int x = 0; x < posVectors_Float.size() / 3; x++){
    //cout << 42 << endl;
    posVectorsFinal.push_back(Vector3{posVectors_Float[posVectorTempCounter1], posVectors_Float[posVectorTempCounter2], posVectors_Float[posVectorTempCounter3]});
    posVectorTempCounter1 += 3;
    posVectorTempCounter2 += 3;
    posVectorTempCounter3 += 3;
  }



  int normVectorTempCounter1 = 0;
  int normVectorTempCounter2 = 1;
  int normVectorTempCounter3 = 2;

  for(int x = 0; x < normVectors_Float.size() / 3; x++){
    //cout << 42 << endl;
    normVectorsFinal.push_back(Vector3{normVectors_Float[normVectorTempCounter1], normVectors_Float[normVectorTempCounter2], normVectors_Float[normVectorTempCounter3]});
    normVectorTempCounter1 += 3;
    normVectorTempCounter2 += 3;
    normVectorTempCounter3 += 3;
  }




  int texVectorTempCounter1 = 0;
  int texVectorTempCounter2 = 1;
  
  for(int x = 0; x < texVectors_Float.size() / 2; x++){

    texVectorsFinal.push_back(Vector3{texVectors_Float[texVectorTempCounter1], texVectors_Float[texVectorTempCounter2], 0});
    texVectorTempCounter1 += 2;
    texVectorTempCounter2 += 2;


  }



  int cornersTempCounter1 = 0;
  int cornersTempCounter2 = 1;
  int cornersTempCounter3 = 2;

  for(int x = 0; x < corners_Float.size() / 3; x++){
    //cout << 42 << endl;
    cornersFinal.push_back(Vector3{corners_Float[cornersTempCounter1], corners_Float[cornersTempCounter2], corners_Float[cornersTempCounter3]});
    cornersTempCounter1 += 3;
    cornersTempCounter2 += 3;
    cornersTempCounter3 += 3;
  }

  // Vector3 newTempVec = cornersFinal[0];
  // cout << newTempVec.x << endl;

  ///Create Triangles from populated "Final" variables

  int TriangleCounter1 = 0;
  int TriangleCounter2 = 1;
  int TriangleCounter3 = 2;
  
  for(int x = 0; x < cornersFinal.size() / 3; x++){
    //Each loop needs to get three vectors threes from the faces 
    Triangle tempT = Triangle{Vector3{cornersFinal[TriangleCounter1].x, cornersFinal[TriangleCounter1].y, cornersFinal[TriangleCounter1].z}, Vector3{cornersFinal[TriangleCounter2].x, cornersFinal[TriangleCounter2].y, cornersFinal[TriangleCounter2].z}, Vector3{cornersFinal[TriangleCounter3].x, cornersFinal[TriangleCounter3].y, cornersFinal[TriangleCounter3].z}};

    tempT.one = posVectorsFinal[tempT.one.x - 1];
    tempT.two = posVectorsFinal[tempT.two.x - 1];
    tempT.three = posVectorsFinal[tempT.three.x - 1];

    posTriangles.push_back(tempT);

    TriangleCounter1 += 3;
    TriangleCounter2 += 3;
    TriangleCounter3 += 3;

  }


    // for(Triangle tri : posTriangles){
    //     cout << tri.one << tri.two << tri.three << endl;
    // }


  ///Return set of triangles from parser.

  return posTriangles;


  }

};






Parser parserObj;

vector<Triangle> triangles = parserObj.Parse("Untitled.obj");







/// Width of the final image
const int w = 640;

/// Height of the final image
const int h = 640;

/// Array for storing the pixel we have generated
unsigned char pixels[w * h * 3];

/// Background Color
Vector3 background_color = Vector3{255, 128, 200};







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
          Vector3 light_direction = Vector3{.5, 1, .5}.normalize();

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
