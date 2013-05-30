package com.gleason.gl;


import com.gleason.gl.renderer.NativeRenderer;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.app.Activity;
import android.graphics.Point;
import android.view.Display;
import android.view.Menu;

public class OpenGlActivity extends Activity {
	private GLSurfaceView view;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	    view = new GLSurfaceView(this);
	    Display display = getWindowManager().getDefaultDisplay();
	    Point size = new Point();
	    display.getSize(size);
	    // Tell EGL to use a ES 2.0 Context
	    view.setEGLContextClientVersion(2);
	    view.setEGLConfigChooser(8 , 8, 8, 8, 16, 0);
	    // Set the renderer
	    GLSurfaceView.Renderer render = new NativeRenderer();
	    view.setRenderer(render);
	    setContentView(view);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_open_gl, menu);
		return true;
	}

}
