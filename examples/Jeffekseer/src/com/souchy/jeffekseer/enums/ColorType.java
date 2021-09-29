package com.souchy.jeffekseer.enums;

public enum ColorType {

	Fixed(0),
	Random(1),
	Easing(2),
	FCurve_RGBA(3),
	;
	
	public final int v;
	private ColorType(int v) {
		this.v = v;
	}

	
	public static ColorType parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
	
	
	
}
