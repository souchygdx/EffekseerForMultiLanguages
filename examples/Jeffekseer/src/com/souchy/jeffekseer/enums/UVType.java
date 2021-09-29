package com.souchy.jeffekseer.enums;

public enum UVType {

	Default(0),
	Fixed(1),
	Animation(2),
	Scroll(3),
	FCurve(4),
	;
	
	
	public final int v;
	private UVType(int v) {
		this.v = v;
	}

	
	public static UVType parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
}
