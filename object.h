
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "glm/glm.hpp"
#include "constants.h"
#include "GL/glut.h"
#include <string>
#include <math.h>

using namespace glm;
using namespace std;

class Object
{
private:
    GLfloat angle;
    GLuint texName;
    /* texture w, h */
    vec2 texRes;
    unsigned char *texture;
    unsigned char *texture_swaped;
    void Draw();
    void drawSphere();
    void Move(int);
    void mapSize();
    unsigned char* readFile(string);
    void textureConstruct(void);
    void transformColors(int,int,int);

public:
    vec3 position;
    GLfloat velocity;
    /* bounded sphere */
    GLfloat radius;
    Object(vec3);
    ~Object();
    bool mark;
    void Rotate(GLfloat);
    void Update(int);
};

#endif
