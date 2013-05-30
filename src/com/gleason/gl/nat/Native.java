package com.gleason.gl.nat;

public class Native {
	static 
	{
		System.loadLibrary("testand");
	}

	public static native void init(int resize, int perspective);
	public static native void resize(int width, int height);
	public static native void render();
}
