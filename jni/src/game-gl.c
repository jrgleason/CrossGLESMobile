//
//  game-gl.c
//  Test
//
//  Created by Jackie Gleason on 5/29/13.
//  Copyright (c) 2013 Jackie Gleason. All rights reserved.
//
#include "game-gl.h"

GLfloat gObj[9] = {
	0.0f, -0.7f, 0.0f,
	0.2f, -1.0f, 0.0f,
	-0.2f, -1.0f, 0.0f
};

GLfloat gBullet[3] = {
	0.0f,0.0f,0.0f
};

GLfloat gEnemy[12] = {
	0.0f,1.2f,0.0f,
	0.2f,1.2f,0.0f,
	0.0f,1.0f,0.0f,
	0.2f,1.0f,0.0f
};

float colors[96] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f
};

struct Ship
{

};

struct UserData
{
   // Handle to a program object
   GLuint programObject;
   float widthScreen;
   float heightScreen;
};

struct UserData userData;

GLuint LoadShader ( GLenum type, const char *shaderSrc )
{
   GLuint shader;
   GLint compiled;

   // Create the shader object
   shader = glCreateShader ( type );

   if ( shader == 0 )
   	return 0;

   // Load the shader source
   glShaderSource ( shader, 1, &shaderSrc, NULL );

   // Compile the shader
   glCompileShader ( shader );

   // Check the compile status
   glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );

   if ( !compiled )
   {
      GLint infoLen = 0;

      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );

      if ( infoLen > 1 )
      {
         char* infoLog = malloc (sizeof(char) * infoLen );

         glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
//         esLogMessage ( "Error compiling shader:\n%s\n", infoLog );

         free ( infoLog );
      }

      glDeleteShader ( shader );
      return 0;
   }

   return shader;

}

///
// Initialize the shader and program object
//
int InitializeOpenGL ()
{
   GLbyte vShaderStr[] =
      "attribute vec4 vPosition;    \n"
      "uniform mat4 move;           \n"
      "uniform mat4 scale;           \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = vPosition;  \n"
	  "   gl_Position = move * gl_Position;  \n"
	  "   gl_Position = scale * gl_Position;  \n"
	  "   gl_PointSize = 5.0;  \n"
      "}                            \n";

   GLbyte fShaderStr[] =
      "precision mediump float;\n"\
      "void main()                                  \n"
      "{                                            \n"
      "  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
      "}                                            \n";

   GLuint vertexShader;
   GLuint fragmentShader;
   GLuint programObject;
   GLint linked;

   // Load the vertex/fragment shaders
   vertexShader = LoadShader ( GL_VERTEX_SHADER, vShaderStr );
   fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, fShaderStr );

   // Create the program object
   programObject = glCreateProgram ( );

   if ( programObject == 0 )
      return 0;

   glAttachShader ( programObject, vertexShader );
   glAttachShader ( programObject, fragmentShader );

   // Bind vPosition to attribute 0
   glBindAttribLocation ( programObject, 0, "vPosition" );

   // Link the program
   glLinkProgram ( programObject );

   // Check the link status
   glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );

   if ( !linked )
   {
      GLint infoLen = 0;

      glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );

      if ( infoLen > 1 )
      {
         char* infoLog = malloc (sizeof(char) * infoLen );

         glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
         //esLogMessage ( "Error linking program:\n%s\n", infoLog );

         free ( infoLog );
      }

      glDeleteProgram ( programObject );
      return GL_FALSE;
   }

   // Store the program object
   userData.programObject = programObject;

   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
   return GL_TRUE;
}

void glMove2D(float x, float y){
	float zoom[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, 1, 1
	};
	GLint projectionUniform = glGetUniformLocation(userData.programObject, "move");
	glUniformMatrix4fv(projectionUniform, 1, 0, &zoom[0]);
}

void glScale2D(float y, float x){
	float zoom[16] = {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
	};
	GLint projectionUniform = glGetUniformLocation(userData.programObject, "scale");
	glUniformMatrix4fv(projectionUniform, 1, 0, &zoom[0]);
}

GLuint getProgram(){
    return userData.programObject;
}


void resizeViewport(int newWidth, int newHeight) {
    userData.widthScreen = newWidth;
    userData.heightScreen = newHeight;
	glViewport(0, 0, userData.widthScreen, userData.heightScreen);
}

float location = -1.0f;
static float xLoc = 0.0f;
static float yLoc = 0.0f;
static float xLoc2 = 0.0f;
static float yLoc2 = -0.7f;
static float xLoc3 = 0.0f;
static float yLoc3 = 0.0f;

static int fire = 0;

void renderFrameLine() {

	   GLfloat vVertices[] = {  0.0f,  0.5f, 0.0f,
	                           -0.5f, -0.5f, 0.0f,
	                            0.5f, -0.5f, 0.0f };
	   if(location > 1.0f){
		   location = -1.0f;
	   }
	   else{
		   location+=0.1f;
	   }
	   // Set the viewport
//	   glViewport ( 0, 0, esContext->width, esContext->height );

	   // Clear the color buffer
	   glClear ( GL_COLOR_BUFFER_BIT );

	   // Use the program object
	   glUseProgram ( userData.programObject );
	   glMove2D(xLoc, yLoc);
	   // glScale2D(userData.widthScreen/userData.heightScreen, userData.heightScreen/userData.widthScreen);
	   glScale2D(1, userData.heightScreen/userData.widthScreen);
//	   glScale2D(1, 1);
	   // Load the vertex data
	   glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, gObj );
	   glEnableVertexAttribArray ( 0 );
	   glDrawArrays ( GL_TRIANGLES, 0, 3 );
	   if(fire == 1){
		   if(yLoc2 < 1){
			 yLoc2 += 0.1;
		     glMove2D(xLoc2, yLoc2);
		     glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, gBullet );
		     glDrawArrays ( GL_POINTS, 0, 1 );
		   }
		   else{
			   fire = 0;
			   yLoc2 = -0.7f;
		   }
	   }
	   else{
		   xLoc2 = xLoc;
	   }
	   if(yLoc3 > -2.4f){
		   yLoc3 -= .01f;
	   }
	   else{
		   yLoc3 = 0.0f;
	   }
	   glMove2D(xLoc3, yLoc3);
	   glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, gEnemy );
	   glDrawArrays ( GL_TRIANGLE_STRIP, 0, 4 );
}

void moveX(float x){
	if(fire == 0){
		fire = 1;
	}
	LOGD("Moving before convert %f", x);
	convertPointX(&x);
	LOGD("Moving to %f", x);
	xLoc = x;
    //normalize for aspect ratio
	xLoc = xLoc / (userData.heightScreen/userData.widthScreen);
}


void convertPointX(float *xIn){
	float midX = (userData.widthScreen)/2.0f;
	float oneBased = 0.0f;
	float x = *xIn;
	LOGD("Touch point is ", x);
	if(x>midX){
	  LOGD("We touched after the middle");
	  oneBased = (x-midX)/midX;
	}
	else if(x != midX){
	  LOGD("We touched before the middle");
	  oneBased = ((x-midX)/midX);
	}
	LOGD("OneBased is %f", oneBased);
	*xIn = oneBased;
}

//void convertPointY(int *y){
//	float midY = userData.heightScreen/2.0f;
//	float oneBased = 0.0f;
//	if(*y>midY){
//	  oneBased = (float)-1 * ((*y-midY)/midY);
//	}
//	else if(*y != midY){
//	  oneBased = (float)-1 * ((*y-midY)/midY);
//	}
//	*y = oneBased;
//}
//
//void convertPoints(int *x, int *y){
//  convertPointX(x);
//  convertPointY(x);
//}
