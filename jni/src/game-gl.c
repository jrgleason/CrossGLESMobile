//
//  game-gl.c
//  Test
//
//  Created by Jackie Gleason on 5/29/13.
//  Copyright (c) 2013 Jackie Gleason. All rights reserved.
//
#include "game-gl.h"

GLbyte vShaderStr[] =
"attribute vec4 vPosition;   \n"
"void main()                 \n"
"{                           \n"
"     gl_Position = vPosition; \n"
"}                           \n";

GLbyte fShaderStr[] = "precision mediump float;"
"void main()                                \n"
"{                                          \n"
"  gl_FragColor = vec4 (0.0, 1.0, 0.0, 1.0); \n"
"}                                          \n";

GLuint programObject;

float widthScreen;
float heightScreen;


GLuint getProgram(){
    return programObject;
}

GLuint LoadShader(GLenum type, const char *shaderSrc) {
#ifdef __APPLE__
    printf("Compiling Shader \n");
#endif
	GLuint shader;
	GLint compiled;
	// Create the shader object
	shader = glCreateShader(type);
		
	// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);
    
	// Compile the shader
	glCompileShader(shader);
    
	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
#ifdef __APPLE__
        printf("Shader Failed \n");
#endif
		GLint infoLen = 0;
        
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        
		glDeleteShader(shader);
		return 0;
	}
    else{
#ifdef __APPLE__
        printf("Shader Created \n");
#endif
    }
	return shader;
    
}

void InitializeOpenGL(int i, int p, GLuint pro) {
#ifdef __APPLE__
    printf("Testing the init \n");
#endif
	//LOGD("Initialization Started");
	GLuint vertexShader;
	GLuint fragmentShader;
#ifdef __APPLE__
    printf("Test %d\n", GL_VERTEX_SHADER);
#endif
	vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
	fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);
    if(pro == 0){
        programObject = glCreateProgram();
        if(programObject == 0){
#ifdef __APPLE__
            printf("Invalid program returned \n");
#else
            LOGD("Invalid program returned");
#endif
        }
    }
    else{
        programObject = pro;
    }
	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);
	glBindAttribLocation(programObject, 0, "vPosition");
    glLinkProgram(programObject);
	glUseProgram(programObject);
    GLint linked;
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    
    if (!linked) {
        // printf("Error linking program:\n");
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
#ifdef __APPLE__
            char* infoLog = (char*)malloc(sizeof(char)*infoLen);
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);

            printf("%s\n",infoLog);
            free(infoLog);
#endif
        }
        glDeleteProgram(programObject);
    }
    else{
        // printf("No linker error \n");
    }
    
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
#ifdef __APPLE__
    printf("Initialization Complete \n");
#else
    LOGD("Initialization Complete");
#endif
}
void resizeViewport(int newWidth, int newHeight) {
#ifdef __APPLE__
    printf("Width: %d Height: %d \n", newWidth, newHeight);
#endif
	glViewport(0, 0, newWidth, newHeight);
}

float f = 0.0f;
float s = 0.5f;

void renderFrameLine() {
    if(f>1.0f){
        f = 0.0f;
    }
    else{
        f = f+.01;
    }
    glClearColor(0.25f, 0.8f, f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat vVertices[] = { s, s, 0.0f, s, -s, 0.0f, -s, s,
        0.0f};
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

