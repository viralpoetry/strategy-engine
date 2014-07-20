
#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "glm/glm.hpp"
#include "GL/glut.h"
#include "constants.h"
#include <vector>

using namespace glm;
using namespace std;

class Terrain
{
private:
    int ranseed;
    GLint treeDL[numOfTrees];
    GLuint initTree();
    void Borovica(int);
    void Haluze(float,int);

protected:
    void Init();
    int rand();

public:
    Terrain();
    ~Terrain();
    vector<vec3*> treeCoord;
    GLfloat radius;
    void Draw();
    void Ground();
    void Skybox();
};

#endif
