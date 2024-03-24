#include <iostream>
#include <vector>
#include "Plane.h"
int main()
{
    int width = 1024;
    int height = 1024;
    // int heightSegments = 1;
    // int widthSegments = 1;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    unsigned rez = 20;
    for(unsigned i = 0; i <= rez-1; i++)
    {
        for(unsigned j = 0; j <= rez-1; j++)
        {

            // current shape that is makes is a quad in the follow order: BL BR TL TR, idk why

            vertices.push_back(-width/2.0f + width*i/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*j/(float)rez); // v.z
            vertices.push_back(i / (float)rez); // u
            vertices.push_back(j / (float)rez); // v

            vertices.push_back(-width/2.0f + width*(i+1)/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*j/(float)rez); // v.z
            vertices.push_back((i+1) / (float)rez); // u
            vertices.push_back(j / (float)rez); // v

            vertices.push_back(-width/2.0f + width*i/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*(j+1)/(float)rez); // v.z
            vertices.push_back(i / (float)rez); // u
            vertices.push_back((j+1) / (float)rez); // v

            vertices.push_back(-width/2.0f + width*(i+1)/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*(j+1)/(float)rez); // v.z
            vertices.push_back((i+1) / (float)rez); // u
            vertices.push_back((j+1) / (float)rez); // v
        }
    }
    // std::vector<float> vertices = plane.getVertices();

    for (int i = 0 ; i < vertices.size(); i += 5)
    {
        std::cout << vertices[i] << " "<< vertices[i + 1] << " " << vertices[i + 2] << " "  << vertices[i + 3] << " "  << vertices[i + 4] << " "  << std::endl;
    }

    std::cout << std::endl;

    // for (int i = 0; i < indices.size(); i += 4)
    // {
    //     std:: cout << indices[i] << " "<< indices[i + 1] << " "<< indices[i + 2] << " "<< indices[i + 3] << " " << std::endl;
    // }
}