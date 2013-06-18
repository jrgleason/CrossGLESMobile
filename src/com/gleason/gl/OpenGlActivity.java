package com.gleason.gl;


import com.gleason.gl.nat.Native;
import com.gleason.gl.renderer.NativeRenderer;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.app.Activity;
import android.graphics.Point;
import android.view.Display;
import android.view.DragEvent;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;

public class OpenGlActivity extends Activity implements View.OnTouchListener, View.OnDragListener{
	private GLSurfaceView view;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	    view = new GLSurfaceView(this);
	    view.setOnTouchListener(this);
//	    view.setOnDragListener(this);
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

	@Override
	public boolean onTouch(View arg0, MotionEvent arg1) {
		Native.moveX(arg1.getX());
		return true;
	}

	@Override
	public boolean onDrag(View v, DragEvent event) {
		// TODO Auto-generated method stub
		Native.moveX(event.getX());
		return false;
	}

}
