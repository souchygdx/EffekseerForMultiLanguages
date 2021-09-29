package com.souchy.jeffekseer.enums;

public enum CullingType {

	Front(0),
	Back(1),
	Double(2),
	
	;
	
	
	public final int v;
	private CullingType(int v) {
		this.v = v;
	}

	
	public static CullingType parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
	
}
