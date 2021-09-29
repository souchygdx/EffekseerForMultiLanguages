package com.souchy.jeffekseer.enums;

public enum ColorMode {

	RGBA(0),
	HSVA(1),
	;
	
	public final int v;
	private ColorMode(int v) {
		this.v = v;
	}

	
	public static ColorMode parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
}
