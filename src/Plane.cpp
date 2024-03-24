#include "Plane.h"
#include "stb_image/stb_image.h"

void Plane::loadHeightMap(const char* path)
{
    int width, height, nChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);

    unsigned rez = 20;
    for(unsigned i = 0; i <= rez-1; i++)
    {
        for(unsigned j = 0; j <= rez-1; j++)
        {
            //Top right
            vertices.push_back(-width/2.0f + width*(i+1)/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*(j+1)/(float)rez); // v.z
            vertices.push_back((i+1) / (float)rez); // u
            vertices.push_back((j+1) / (float)rez); // v

            //Top left
            vertices.push_back(-width/2.0f + width*i/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*(j+1)/(float)rez); // v.z
            vertices.push_back(i / (float)rez); // u
            vertices.push_back((j+1) / (float)rez); // v

            //Bottom left
            vertices.push_back(-width/2.0f + width*i/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*j/(float)rez); // v.z
            vertices.push_back(i / (float)rez); // u
            vertices.push_back(j / (float)rez); // v

            //Bottom right
            vertices.push_back(-width/2.0f + width*(i+1)/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*j/(float)rez); // v.z
            vertices.push_back((i+1) / (float)rez); // u
            vertices.push_back(j / (float)rez); // v
        }
    }

    stbi_image_free(data);
}

void Plane::GeneratePlane(int width, int height, int widthSegments, int heightSegments)
{
    //for incrementing reason, we will generate the plane starting from the bottom left
    for (int z = 0; z <= heightSegments; z++)
    {
        for (int x = 0; x <= widthSegments; x++)
        {
            vertices.push_back(x * (width/widthSegments));
            vertices.push_back(0.0f); //y component of graph
            vertices.push_back(z * (height/heightSegments));
        }
    }

    for (int i = 0; i < heightSegments; i++)
    {
        for (int j = 0; j < widthSegments; j++)
        {
            indices.push_back((i * (widthSegments + 1)) + j);
            indices.push_back((i * (widthSegments + 1)) + j + 1);
            indices.push_back(((1 + i) * (widthSegments + 1)) + j + 1);
            indices.push_back(((1 + i) * (widthSegments + 1)) + j);
        }
    }
}

std::vector<float> Plane::getVertices()
{
    return vertices;
}

std::vector<unsigned int> Plane::getIndices()
{
    return indices;
}