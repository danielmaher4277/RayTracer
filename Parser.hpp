#ifndef PARSER_42
#define PARSER_42

#include<vector>
using namespace std;

#include "Vector3.hpp"
#include "Vector3.cpp"
#include "Triangle.hpp"
#include "file_util.h"


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


#endif