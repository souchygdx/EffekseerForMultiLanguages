package com.souchy.jeffekseer.enums;

public enum BindType {

	NotBind(0),
	NotBind_Root(3),
	WhenCreating(1),
	Always(2)
	;
	
	
	public final int v;
	private BindType(int v) {
		this.v = v;
	}

	
	public static BindType parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
	
	
}
