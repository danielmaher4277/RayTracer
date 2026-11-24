#ifndef MATRIX_42
#define MATRIX_42

#include <vector>


#include "Triangle.hpp"
#include "file_util.h"
#include<iostream>
using namespace std;

class Matrix{
  public:

    //vector<Triangle> Triangles;

    float x,y,z;
    float factor = 1;
    Vector3 newVector = {1, 1, 1};
    vector<Triangle> newTriangles;


    //Need to multiply each triangle by this matrix for every triangle in object, then return list of triangles
    vector<float> TranslationMatrix = {factor, 0, 0,
                                       0, factor, 0,
                                       0, 0, factor };


    vector<float> RotationMatrix = {1, 0, 0, 0,
                                    0, 1, 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1 };

    vector<float> ScalingMatrix = {1, 0, 0, 0,
                                   0, 1, 0, 0,
                                   0, 0, 1, 0,
                                   0, 0, 0, 1};

    
    vector<Triangle> ScaleTriangles(vector<Triangle> triangles){
        for(Triangle triangle: triangles){
            
            //cout << triangle.one << endl;
            //cout << triangle.one << triangle.two << triangle.three << endl;
            
            Triangle newSingleTriangle;

            triangle.one *= factor;
            newSingleTriangle.one = triangle.one;
            //newSingleTriangle.one = triangle.one * factor;
            
            triangle.two *= factor;
            newSingleTriangle.two = triangle.two;

            triangle.three *= factor;
            newSingleTriangle.three = triangle.three;

            newTriangles.push_back(newSingleTriangle);

            //cout << triangle.one << triangle.two << triangle.three << endl;
            // cout << newVector << triangle.two << triangle.three << endl;

        }
        return newTriangles;

    }


    vector<Triangle> TranslateTriangles(vector<Triangle> triangles){
        for(Triangle triangle: triangles){
            
            //cout << triangle.one << endl;
            //cout << triangle.one << triangle.two << triangle.three << endl;
            
            Triangle newSingleTriangle;


            cout << newSingleTriangle.one << newSingleTriangle.two << newSingleTriangle.three << endl;

            triangle.one.x *= factor;
            newSingleTriangle.one.x = triangle.one.x;

            triangle.one.y *= factor;
            newSingleTriangle.one.y = triangle.one.y;

            //newSingleTriangle.one = triangle.one * factor;

            
            triangle.two.x *= factor;
            newSingleTriangle.two.x = triangle.two.x;

            triangle.two.y *= factor;
            newSingleTriangle.two.y = triangle.two.y;


            triangle.three.x *= factor;
            newSingleTriangle.three.x = triangle.three.x;

            triangle.three.y *= factor;
            newSingleTriangle.three.y = triangle.three.y;


            cout << newSingleTriangle.one << newSingleTriangle.two << newSingleTriangle.three << endl;
            
            newTriangles.push_back(newSingleTriangle);

            //cout << triangle.one << triangle.two << triangle.three << endl;
            // cout << newVector << triangle.two << triangle.three << endl;

        }
        return newTriangles;

    }

    

  

};


#endif