package com.souchy.jeffekseer.enums;

public enum ParameterRotationType {

	Fixed(0),
	PVA(1),
	Easing(2), 
	AxisPVA(3),
	AxisEasing(4),
	FCurve(5),

	None(0x7fffffff - 1),
	DWORD(0x7fffffff)
	
	;
	
	public final int v;
	private ParameterRotationType(int v) {
		this.v = v;
	}

	
	public static ParameterRotationType parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
	
	
}
