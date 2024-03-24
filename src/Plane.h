#include <vector>

class Plane
{
    private:
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

    public:
        void loadHeightMap(const char* path);
        void GeneratePlane(int width, int height, int widthSegments, int heightSegments);
        std::vector<float> getVertices();
        std::vector<unsigned int> getIndices();

};