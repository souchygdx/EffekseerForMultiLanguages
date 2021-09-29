package com.souchy.jeffekseer.enums;

public enum ParameterTranslationType {

	Fixed(0),
	PVA(1),
	/** Applying Easing to a node that isn't already Easing will crash the runtime */
	Easing(2), 
	/** Applying FCure to a node that isn't already FCurve will crash the runtime */
	FCurve(3),
	NurbsCurve(4),
	ViewOffset(5),

	None(0x7fffffff - 1),

	DWORD(0x7fffffff)
	
	;
	
	public final int v;
	private ParameterTranslationType(int v) {
		this.v = v;
	}

	
	public static ParameterTranslationType parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
	

	public static final float[] zero = new float[] {
			// start min, max
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, -1.0f, 
			// middle min, max
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, -1.0f, 
			// end min, max
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, -1.0f, 
			// isIndividualEnabled, isMiddleEnabled, type
			0.0f, 0.0f, 0.0f, 
			// unused
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};
	
}
