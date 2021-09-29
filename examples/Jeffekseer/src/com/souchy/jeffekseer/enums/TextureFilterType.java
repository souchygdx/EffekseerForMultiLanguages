package com.souchy.jeffekseer.enums;

public enum TextureFilterType {
	
	Nearest(0),
	Linear(1),
	;
	
	
	public final int v;
	private TextureFilterType(int v) {
		this.v = v;
	}

	
	public static TextureFilterType parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
}
