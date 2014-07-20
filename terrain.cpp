
#include "terrain.h"

Terrain::Terrain()
{
    // init generator
    ranseed = 23;
    radius = 2.0;

    // init display list
    glEnable(GL_DEPTH_TEST);
    for(int i = 0; i < numOfTrees; i++) {
	   treeDL[i] = initTree();
    }

    // init coords
    for(int i = 0; i < numOfTrees/2; i++) {
	   treeCoord.push_back(new vec3(rand()%100, 0.0f, rand()%100));
    }
    for(int i = numOfTrees/2; i < numOfTrees; i++) {
	   treeCoord.push_back(new vec3((rand()%200) - 100, 0.0f, (rand()%200) - 100));
    }
}

Terrain::~Terrain()
{
}

void Terrain::Draw()
{
    Ground();
}

void Terrain::Ground()
{
    // Draw ground
    //glColor3f(0.33f, 0.42f, 0.18f);
    glColor3f(0.8f, 0.9f, 1.0f);
    glBegin(GL_QUADS);
	   glVertex3f(-MAP_SIZE, 0.0f, -MAP_SIZE);
	   glVertex3f(-MAP_SIZE, 0.0f,  MAP_SIZE);
	   glVertex3f( MAP_SIZE, 0.0f,  MAP_SIZE);
	   glVertex3f( MAP_SIZE, 0.0f, -MAP_SIZE);
    glEnd();

    // Draw trees
    for(size_t i = 0; i < treeCoord.size(); i++)
    {
	   glPushMatrix();
	    
	   glTranslatef( treeCoord.at(i)->x, 0, treeCoord.at(i)->z);
	   glCallList(treeDL[0]);
	    
	   glPopMatrix();
    }

}

void Terrain::Skybox()
{
}

int Terrain::rand()
{
    ranseed = (ranseed * 1103515245 + 12345) & RND_MAX;
    return ranseed;
}

GLuint Terrain::initTree()
{
    GLuint temp;
    // Create the id for the list
    temp = glGenLists(1);
    // start list
    glNewList(temp,GL_COMPILE);
	
    Borovica(rand()%7);

    glEndList();

    return(temp);
}

void Terrain::Borovica(int randomNum)
{
    // Kmen
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glRotatef( -90, 1, 0, 0);
    GLUquadricObj *p;
    p = gluNewQuadric();
    gluQuadricDrawStyle(p, GL_LINE);
    gluCylinder(p, 0.5, 0.2, randomNum+2, 10, 10);
    //glRotatef( 90, 1, 0, 0);

    glPopMatrix();

    //glRotatef(20, 0, 1, 0);
    glTranslatef(0, randomNum+1, 0);
    Haluze(1.6, randomNum%2+5);
    glPopMatrix();

}

void Terrain::Haluze(float size, int level)
{
    if( level <= 0 ) {
	   return;
    } else {
	   glBegin(GL_TRIANGLE_FAN);
	   
	   // set color to Dark Olive Green
	   glColor3f(0.33f, 0.42f, 0.18f);
	   glVertex3f( 0.0f,  size/2.0, 0.0f);
	   
	   //glColor3f(0.0f,1.0f,0.0f);                	// set color to green
	   glColor3f(0.13f,0.545f,0.13f);
	   glVertex3f(-size, -size, size);
      
	   //glColor3f(1.0f,1.0f,0.0f);                	// set color to yellow
	   glColor3f(0.0f,0.39f,0.0f);
	   glVertex3f( size, -size, size);
      
	   //glColor3f(0.0f,0.0f,1.0f);                	// set color to blue
	   glColor3f(0.33f, 0.42f, 0.18f);
	   glVertex3f( size, -size, -size);
      
	   // set color to Forest Green
	   glColor3f(0.13f,0.545f,0.13f);
	   glVertex3f( -size, -size, -size);
      
	   //glColor3f(0.0f,1.0f,0.0f);                	// set color to green
	   glColor3f(0.33f, 0.42f, 0.18f);
	   glVertex3f(-size, -size, size);
	   glEnd();

    }

    glPushMatrix();
    glTranslatef(0, 1-(2.05/level), 0);

    glRotatef( rand()%40, 0, 1, 0);
    Haluze(size - 0.28, level-1);
    glPopMatrix();

}
