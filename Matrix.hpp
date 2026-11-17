#ifndef MATRIX_42
#define MATRIX_42

#include <vector>


#include "Triangle.hpp"
#include "file_util.h"
#include<iostream>
using namespace std;

class Matrix{
  public:


    float x,y,z;

    vector<float> TranslationMatrix = {1, 0, 0, x,
                                       0, 1, 0, y,
                                       0, 0, 1, z,
                                       0, 0, 0, 1};


    vector<float> RotationMatrix = {1, 0, 0, 0,
                                    0, 1, 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1};

    vector<float> ScalingMatrix = {1, 0, 0, 0,
                                   0, 1, 0, 0,
                                   0, 0, 1, 0,
                                   0, 0, 0, 1};

    
    vector<Triangle> TranslateTriangles(vector<Triangle> triangles){
        for(Triangle triangle: triangles){
            
            triangle.one * 5;
            triangle.two * 5;
            triangle.three * 5;
            cout << triangle.one << triangle.two << triangle.three << endl;

        }
        return triangles;

    }

    

  

};


#endif