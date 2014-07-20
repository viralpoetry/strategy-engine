
#ifndef _GAME_H_
#define _GAME_H_

/* lebo Sleep */
//#include <windows.h>
#include "glm/glm.hpp"
#include "constants.h"

#include "terrain.h"
#include "object.h"

#include "GL/glut.h"
#include <vector>

#define speed 0.5

using namespace glm;
using namespace std;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f }; 
 
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

class Game
{

private:
    vec3 delta;
    vec3 camera;
    vec3 mouseCoord;
    float angle;
    int width;
    int height;
    int halfWidth;
    int halfHeight;
    /* fps */
    int timeSinceFPS;
    int milliseconds;
    int previousTime;
    int timeElapsed;
    /* *** */
    Terrain *Map;
    vector <Object*> Tank;
    void Controls();
    void moveCamera();
    bool checkCollision(vec3, vec3, GLfloat, GLfloat); 

public:
    Game(int,int);
    ~Game();
    void Run();
    void Draw();
    void Update();
    int Init(int, char **);
    void Resize(int, int);
    void activeMouse(int,int,int,int);
    void passiveMouse(int, int);
    void specialKey(int, int, int);
    void standardKey(unsigned char, int, int);
    
};

#endif
