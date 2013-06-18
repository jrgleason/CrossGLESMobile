#include "game-gl.h"
#include <jni.h>
#include "box2d.hpp"


JNIEXPORT void JNICALL Java_com_gleason_gl_nat_Native_init(JNIEnv* env, jclass class)
{
	InitializeOpenGL();
	init();
}
JNIEXPORT void JNICALL Java_com_gleason_gl_nat_Native_resize(JNIEnv* env, jclass class, jint width, jint height)
{
	resizeViewport(width, height);
}
JNIEXPORT void JNICALL Java_com_gleason_gl_nat_Native_render(JNIEnv* env, jclass class)
{
  renderFrameLine();
}
JNIEXPORT void JNICALL Java_com_gleason_gl_nat_Native_moveX(JNIEnv* env, jclass class, jfloat x)
{
  LOGD("In JNI");
  moveX(x);
}
