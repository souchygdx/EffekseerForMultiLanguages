package com.souchy.jeffekseer.enums;

public enum GenerationType {
	
	Point(0),
	Sphere(1),
	Model(2),
	Circle(3),
	Line(4),
	;
	
	
	public final int v;
	private GenerationType(int v) {
		this.v = v;
	}

	
	public static GenerationType parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
}
