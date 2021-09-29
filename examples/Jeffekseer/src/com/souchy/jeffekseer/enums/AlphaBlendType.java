package com.souchy.jeffekseer.enums;

public enum AlphaBlendType {

	Opacity(0),
	Blend(1),
	Add(2),
	Sub(3),
	Mul(4),
	;
	
	
	public final int v;
	private AlphaBlendType(int v) {
		this.v = v;
	}
	
	public static AlphaBlendType parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
	
}
