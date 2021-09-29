package com.souchy.jeffekseer.enums;

public enum ParameterScalingType {

	Fixed(0),
	PVA(1),
	Easing(2), 
	SinglePVA(3),
	SingleEasing(4),
	FCurve(5),
	SingleFCurve(6),
	
	None(0x7fffffff - 1),
	DWORD(0x7fffffff)
	;
	
	public final int v;
	private ParameterScalingType(int v) {
		this.v = v;
	}

	
	public static ParameterScalingType parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
	
}
