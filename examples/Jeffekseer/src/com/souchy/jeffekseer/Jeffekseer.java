package com.souchy.jeffekseer;

import effekseer.swig.EffekseerBackendCore;

public class Jeffekseer {

	// scales all effects
	public static float worldScaleX = 1f;
	public static float worldScaleY = 1f;
	public static float worldScaleZ = 1f;
	
	// offsets all effects if you have a world starting point
	public static float worldOffsetX = 0f;
	public static float worldOffsetY = 0f;
	public static float worldOffsetZ = 0f;
	
	/**
	 * If effects in the editor are made with y-up (true) or z-up (false)
	 * (My worlds are Z-up so I use this to convert the editor's coordinate system)
	 */
	public static boolean yUp = true;
	
	static {
		System.loadLibrary("EffekseerNativeForJava");
		EffekseerBackendCore.InitializeAsOpenGL();
	}
	
	public static EffectManager newManager() {
		var m = new EffectManager();
		m.Initialize(8000);
		return m;
	}
	
}
