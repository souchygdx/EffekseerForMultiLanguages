package com.souchy.jeffekseer.enums;

public enum TextureWrapType {
	
	Repeat(0),
	Clamp(1)
	;
	
	
	public final int v;
	private TextureWrapType(int v) {
		this.v = v;
	}

	
	public static TextureWrapType parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
}
