#include "game-gl.h"
#include <jni.h>

JNIEXPORT void JNICALL Java_com_gleason_gl_nat_Native_init(JNIEnv* env, jclass class, jint resize, jint perspective)
{
	InitializeOpenGL(resize, perspective, 0);
}
JNIEXPORT void JNICALL Java_com_gleason_gl_nat_Native_resize(JNIEnv* env, jclass class, jint width, jint height)
{
	resizeViewport(width, height);
}
JNIEXPORT void JNICALL Java_com_gleason_gl_nat_Native_render(JNIEnv* env, jclass class)
{
  renderFrameLine();
}
