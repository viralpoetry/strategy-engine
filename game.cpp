
#include "game.h"
// len pre printf vypisy
#include <stdio.h>

Game::Game(int w, int h)
{
    width = w;
    height = h;
    halfWidth = w/2.0;
    halfHeight = h/2.0;
    timeSinceFPS = 0;
    camera.x = 0;
    //camera.y = -20.0f;
    camera.y = -40.0f;
    camera.z = -100.0f;
    angle = 30.0f;
}

Game::~Game()
{
    delete Map;
    // delete tank;
}

int Game::Init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(width,height);
    glutCreateWindow("Strategia");

    //glEnable(GL_TEXTURE_2D);
    //glShadeModel(GL_SMOOTH);

    glShadeModel(GL_FLAT);
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
      
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
 
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); 

    /* fps */
    milliseconds = glutGet(GLUT_ELAPSED_TIME);

    /* Terrain init */
    Map = new Terrain();
    
    /* init first tanks */
    Tank.push_back(new Object(vec3(0.0f, 5.0f, 0.0f)));

    return 0;
}

static Game* currentInstance;
/*
helper functions
http://stackoverflow.com/questions/3589422/using-opengl-glutdisplayfunc-within-class
*/
//extern "C"
void drawCallback() {
    currentInstance->Draw();
}
void resizeCallback(int x, int y) {
    currentInstance->Resize(x, y);
}
void activeMouseCallback(int button, int state, int x, int y) {
    currentInstance->activeMouse(button,state,x,y);
}
void passiveMouseCallback(int x, int y) {
    currentInstance->passiveMouse(x, y);
}
void standardKeyCallback(unsigned char key, int x, int y) {
    currentInstance->standardKey(key, x, y);
}
void specialKeyCallback(int key, int x, int y) {
    currentInstance->specialKey(key, x, y);
}

void Game::Run()
{
    glutSpecialFunc(specialKeyCallback);
    glutKeyboardFunc(standardKeyCallback);
    glutMouseFunc(activeMouseCallback);
    glutPassiveMotionFunc(passiveMouseCallback);
    //glutMouseFunc

    currentInstance = this;
    glutDisplayFunc(drawCallback);

    glutReshapeFunc(resizeCallback);

    //glutSetCursor(GLUT_CURSOR_NONE);
    //glutWarpPointer(width/2, height/2);
    glutMainLoop();
}

void Game::Draw()
{
    /* fps */
    milliseconds = glutGet(GLUT_ELAPSED_TIME);
    timeElapsed = milliseconds - previousTime;
    previousTime = milliseconds;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    glLoadIdentity();
    glRotatef(angle, 1.0, 0.0, 0.0);

    
    Update();
    /* draw */
    Map->Draw();
    
    //Sleep(10);
    glutSwapBuffers();
    glutPostRedisplay();
}

void Game::Update()
{
    /*for(size_t i = 0; i < Map->treeCoord.size(); i++)
    {
	   vec3 temp;
	   temp.x = Map->treeCoord.at(i)->x - Tank.at(0)->radius;
	   temp.y = Map->treeCoord.at(i)->y;
	   temp.z = Map->treeCoord.at(i)->z - Tank.at(0)->radius;

	   if( checkCollision(Tank.at(0)->position, temp, Tank.at(0)->radius, Map->radius) )
	   {
		  printf("kolizia\n");
		  Map->treeCoord.erase(Map->treeCoord.begin()+i);
	   }
    }

    for(size_t i = 0; i < Tank.size(); i++)
    {
	   Tank.at(i)->Update(timeElapsed);
    }
    */

    moveCamera();
}

void Game::Resize(int x, int y)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
    if(height == 0) {
	   height = 1;
    }

	float ratio = 1.0f * width / height;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);

	// Set the clipping volume
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void Game::moveCamera()
{
    camera.x = camera.x + delta.x*MOVEMENT_SPEED*(timeElapsed/50.0f);
    camera.z = camera.z + delta.z*MOVEMENT_SPEED*(timeElapsed/50.0f);

    glTranslatef(camera.x, camera.y, camera.z);
}

void Game::activeMouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN && button == GLUT_LEFT)
    {
	   mouseCoord.x = (GLfloat)(x-halfWidth)/(halfWidth);
	   mouseCoord.y =  -1*(GLfloat)(y-halfHeight)/(halfHeight);
    }

    glutPostRedisplay();
}

void Game::passiveMouse(int x, int y)
{
    mouseCoord.x = (GLfloat)(x-halfWidth)/(halfWidth);
    mouseCoord.y =  -1*(GLfloat)(y-halfHeight)/(halfHeight);

    /* pohyb a la strategia */
    if(x < 30)
    {
	   delta.x = 1.0;
    }
    else if(x > (width - 20) && camera.x > -80.0)
    {
	   delta.x = -1.0;
    }
    else
    {
	   delta.x = 0.0;
    }

    if(y < 30)
    {
	   delta.z = 1.0;
    }
    else if(y > height - 20)
    {
	   delta.z = -1.0;
    }
    else
    {
	   delta.z = 0.0;
    }

    //printf("%d %d\n",x, y);
    //Move();
}

void Game::specialKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
		    Tank.at(0)->Rotate(2.0);
			break;
		case GLUT_KEY_RIGHT : 
		    Tank.at(0)->Rotate(-2.0);
			break;
		case GLUT_KEY_UP :
		     Tank.at(0)->velocity += 0.2;
			break;
		case GLUT_KEY_DOWN :
		     Tank.at(0)->velocity -= 0.2;
			break;
	}
}

void Game::standardKey(unsigned char key, int x, int y)
{
    switch (key)
    {
	   case 'w':
		  Tank.at(0)->velocity += 0.2;
		  break;
	   case 's':
		  Tank.at(0)->velocity -= 0.2;
		  break;
	   case 'a':
		  Tank.at(0)->Rotate(3.0);
		  break;
	   case 'd':
		  Tank.at(0)->Rotate(-3.0);
		  break;
	   case 32:
		  Tank.at(0)->velocity = 0;
		  break;
	   case 27:
		  exit(0);
		  break;
	   default:
		  break;
    }
    //glutPostRedisplay();
}

bool Game::checkCollision(vec3 A, vec3 B, GLfloat radA, GLfloat radB)
{
    //vec3 temp = A - B;
    //GLfloat distSqr = dot(temp, temp);
    GLfloat dist = glm::distance(A, B);
    if(dist < 10) {
	   printf("%f\n", dist);
    }
    if(dist < radA + radB + 1) {
	   return true;
    } else {
	   return false;
    }
}





