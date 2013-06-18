package com.gleason.gl.nat;

public class Native {
	static 
	{
                System.loadLibrary("box2D");
		System.loadLibrary("testand");
	}

	public static native void init();
	public static native void resize(int width, int height);
	public static native void render();
	public static native void moveX(float x);
}
