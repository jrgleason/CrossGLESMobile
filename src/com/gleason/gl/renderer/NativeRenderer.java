package com.gleason.gl.renderer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.gleason.gl.nat.Native;

import android.opengl.GLSurfaceView;

public class NativeRenderer implements GLSurfaceView.Renderer {
	@Override
	public void onDrawFrame(GL10 arg0) {
		// TODO Auto-generated method stub
		Native.render();
	}

	@Override
	public void onSurfaceChanged(GL10 arg0, int width, int height) {
		// TODO Auto-generated method stub
		Native.resize(width, height);
	}

	@Override
	public void onSurfaceCreated(GL10 arg0, EGLConfig arg1) {
		// TODO Auto-generated method stub
		Native.init(0,0);
	}
}
