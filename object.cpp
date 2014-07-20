
#include "object.h"

Object::Object(vec3 pos)
{
    position = pos;
    radius = 3.0f;
    velocity = 0.0f;
    mark = false;

    texture = NULL;
    texture_swaped = NULL;
    texture = readFile("iron.bmp");
    transformColors(2,1,0);
    textureConstruct();
}

Object::~Object() {
}

void Object::Update(int delta)
{
    Move(delta);
    Draw();
}

void Object::Move(int delta)
{
    position.z += (float) (velocity * (delta/100.0f) * cos(angle / 180.0f * PI));
    position.x += (float) (velocity * (delta/100.0f) * sin(angle / 180.0f * PI));
    //translate(dx, 0, - dz);

    if(velocity > 0)
    {
	   //velocity -= 0.02;
    }
}

void Object::drawSphere()
{
    glPushMatrix();
	   glColor3f(1.0f, 0.0f, 0.0f);
	   glTranslatef(position.x, position.y, position.z);
	   glutWireSphere(radius, 16, 16);
    glPopMatrix();
}

void Object::Draw()
{
    glPushMatrix();
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glTranslatef(-position.x, radius, -position.z);
    mapSize();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName);

    if(mark == false)
    {
	   glColor3f(1.0f, 1.0f, 1.0f);
	   //glColor3f(  0.8,  0.0,  0.8 );
	   glBegin(GL_QUADS);
	   // Front Face
	   glTexCoord2f(0.0f, 0.0f); glVertex3f(-radius, -radius,  radius);  // Bottom Left Of The Texture and Quad
	   glTexCoord2f(1.0f, 0.0f); glVertex3f( radius, -radius,  radius);  // Bottom Right Of The Texture and Quad
	   glTexCoord2f(1.0f, 1.0f); glVertex3f( radius,  radius,  radius);  // Top Right Of The Texture and Quad
	   glTexCoord2f(0.0f, 1.0f); glVertex3f(-radius,  radius,  radius);  // Top Left Of The Texture and Quad
	   // Back Face
	   glTexCoord2f(1.0f, 0.0f); glVertex3f(-radius, -radius, -radius);  // Bottom Right Of The Texture and Quad
	   glTexCoord2f(1.0f, 1.0f); glVertex3f(-radius,  radius, -radius);  // Top Right Of The Texture and Quad
	   glTexCoord2f(0.0f, 1.0f); glVertex3f( radius,  radius, -radius);  // Top Left Of The Texture and Quad
	   glTexCoord2f(0.0f, 0.0f); glVertex3f( radius, -radius, -radius);  // Bottom Left Of The Texture and Quad
	   // Top Face
	   glTexCoord2f(0.0f, 1.0f); glVertex3f(-radius,  radius, -radius);  // Top Left Of The Texture and Quad
	   glTexCoord2f(0.0f, 0.0f); glVertex3f(-radius,  radius,  radius);  // Bottom Left Of The Texture and Quad
	   glTexCoord2f(1.0f, 0.0f); glVertex3f( radius,  radius,  radius);  // Bottom Right Of The Texture and Quad
	   glTexCoord2f(1.0f, 1.0f); glVertex3f( radius,  radius, -radius);  // Top Right Of The Texture and Quad
	   // Bottom Face
	   glTexCoord2f(1.0f, 1.0f); glVertex3f(-radius, -radius, -radius);  // Top Right Of The Texture and Quad
	   glTexCoord2f(0.0f, 1.0f); glVertex3f( radius, -radius, -radius);  // Top Left Of The Texture and Quad
	   glTexCoord2f(0.0f, 0.0f); glVertex3f( radius, -radius,  radius);  // Bottom Left Of The Texture and Quad
	   glTexCoord2f(1.0f, 0.0f); glVertex3f(-radius, -radius,  radius);  // Bottom Right Of The Texture and Quad
	   // Right face
	   glTexCoord2f(1.0f, 0.0f); glVertex3f( radius, -radius, -radius);  // Bottom Right Of The Texture and Quad
	   glTexCoord2f(1.0f, 1.0f); glVertex3f( radius,  radius, -radius);  // Top Right Of The Texture and Quad
	   glTexCoord2f(0.0f, 1.0f); glVertex3f( radius,  radius,  radius);  // Top Left Of The Texture and Quad
	   glTexCoord2f(0.0f, 0.0f); glVertex3f( radius, -radius,  radius);  // Bottom Left Of The Texture and Quad
	   // Left Face
	   glTexCoord2f(0.0f, 0.0f); glVertex3f(-radius, -radius, -radius);  // Bottom Left Of The Texture and Quad
	   glTexCoord2f(1.0f, 0.0f); glVertex3f(-radius, -radius,  radius);  // Bottom Right Of The Texture and Quad
	   glTexCoord2f(1.0f, 1.0f); glVertex3f(-radius,  radius,  radius);  // Top Right Of The Texture and Quad
	   glTexCoord2f(0.0f, 1.0f); glVertex3f(-radius,  radius, -radius);  // Top Left Of The Texture and Quad
	   glEnd();

    } else {
	   
	   glColor3f(1.0f, 0.0f, 0.0f);
	   //glColor3f(  0.8,  0.0,  0.8 );
	   glBegin(GL_QUADS);
	   // Front Face
	   glTexCoord2f(0.0f, 0.0f); glVertex3f(-radius, -radius,  radius);  // Bottom Left Of The Texture and Quad
	   glTexCoord2f(1.0f, 0.0f); glVertex3f( radius, -radius,  radius);  // Bottom Right Of The Texture and Quad
	   glTexCoord2f(1.0f, 1.0f); glVertex3f( radius,  radius,  radius);  // Top Right Of The Texture and Quad
	   glTexCoord2f(0.0f, 1.0f); glVertex3f(-radius,  radius,  radius);  // Top Left Of The Texture and Quad
	   // Back Face
	   glTexCoord2f(1.0f, 0.0f); glVertex3f(-radius, -radius, -radius);  // Bottom Right Of The Texture and Quad
	   glTexCoord2f(1.0f, 1.0f); glVertex3f(-radius,  radius, -radius);  // Top Right Of The Texture and Quad
	   glTexCoord2f(0.0f, 1.0f); glVertex3f( radius,  radius, -radius);  // Top Left Of The Texture and Quad
	   glTexCoord2f(0.0f, 0.0f); glVertex3f( radius, -radius, -radius);  // Bottom Left Of The Texture and Quad
	   // Top Face
	   glTexCoord2f(0.0f, 1.0f); glVertex3f(-radius,  radius, -radius);  // Top Left Of The Texture and Quad
	   glTexCoord2f(0.0f, 0.0f); glVertex3f(-radius,  radius,  radius);  // Bottom Left Of The Texture and Quad
	   glTexCoord2f(1.0f, 0.0f); glVertex3f( radius,  radius,  radius);  // Bottom Right Of The Texture and Quad
	   glTexCoord2f(1.0f, 1.0f); glVertex3f( radius,  radius, -radius);  // Top Right Of The Texture and Quad
	   // Bottom Face
	   glTexCoord2f(1.0f, 1.0f); glVertex3f(-radius, -radius, -radius);  // Top Right Of The Texture and Quad
	   glTexCoord2f(0.0f, 1.0f); glVertex3f( radius, -radius, -radius);  // Top Left Of The Texture and Quad
	   glTexCoord2f(0.0f, 0.0f); glVertex3f( radius, -radius,  radius);  // Bottom Left Of The Texture and Quad
	   glTexCoord2f(1.0f, 0.0f); glVertex3f(-radius, -radius,  radius);  // Bottom Right Of The Texture and Quad
	   // Right face
	   glTexCoord2f(1.0f, 0.0f); glVertex3f( radius, -radius, -radius);  // Bottom Right Of The Texture and Quad
	   glTexCoord2f(1.0f, 1.0f); glVertex3f( radius,  radius, -radius);  // Top Right Of The Texture and Quad
	   glTexCoord2f(0.0f, 1.0f); glVertex3f( radius,  radius,  radius);  // Top Left Of The Texture and Quad
	   glTexCoord2f(0.0f, 0.0f); glVertex3f( radius, -radius,  radius);  // Bottom Left Of The Texture and Quad
	   // Left Face
	   glTexCoord2f(0.0f, 0.0f); glVertex3f(-radius, -radius, -radius);  // Bottom Left Of The Texture and Quad
	   glTexCoord2f(1.0f, 0.0f); glVertex3f(-radius, -radius,  radius);  // Bottom Right Of The Texture and Quad
	   glTexCoord2f(1.0f, 1.0f); glVertex3f(-radius,  radius,  radius);  // Top Right Of The Texture and Quad
	   glTexCoord2f(0.0f, 1.0f); glVertex3f(-radius,  radius, -radius);  // Top Left Of The Texture and Quad
	   glEnd();
	   
    }

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void Object::Rotate(GLfloat alfa) {
    angle = ((int)(angle + alfa)) % 360;
}

void Object::mapSize() {
    if (position.x < -MAP_SIZE+radius)
    {
	   position.x = -MAP_SIZE+radius;
	   velocity = 0;
    }
    else if (position.x > MAP_SIZE-radius)
    {
	   position.x = MAP_SIZE-radius;
	   velocity = 0;
    }
    if (position.z < -MAP_SIZE+radius)
    {
	   position.z = -MAP_SIZE+radius;
	   velocity = 0;
    }
    else if (position.z > MAP_SIZE-radius)
    {
	   position.z = MAP_SIZE-radius;
	   velocity = 0;
    }
}

unsigned char* Object::readFile(string name)
{
    char header[54];
    FILE* file_bmp = fopen(name.c_str(),"r");
	if(file_bmp != 0)
	{

	    fread(header,1,54,file_bmp);

	    // rozmer
	    texRes.x = header[19]*256+header[18];
	    texRes.y = header[23]*256+header[22];

	    //int imageSize = header[4]*256+header[3];
		
	    unsigned char *data = (GLubyte*)malloc(texRes.x*texRes.y*3);

	    fread(data,1,texRes.x*texRes.y*3,file_bmp);

	    return data;
	}
	else
	{
	    return 0;
	}
}

void Object::textureConstruct(void)
{   
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texRes.x, texRes.y, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_swaped);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

void Object::transformColors(int R, int G, int B)
{
     int pixels = texRes.x*texRes.y;
	if(texture_swaped != NULL)
	{
		free((void*)texture_swaped);
	}
	texture_swaped = (GLubyte*)malloc(pixels*3);
	for(int i = 0; i < pixels; i++ )
	{
			texture_swaped[3*i+R] = texture[3*i];
			texture_swaped[3*i+G] = texture[3*i+1];
			texture_swaped[3*i+B] = texture[3*i+2];
	}
}
