package com.souchy.jeffekseer.enums;

public enum RendererMaterialType {

	Default(0),
	BackDistortion(6),
	Lighting(7),
	File(128),
	
	;
	
	
	public final int v;
	private RendererMaterialType(int v) {
		this.v = v;
	}

	
	public static RendererMaterialType parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
}
