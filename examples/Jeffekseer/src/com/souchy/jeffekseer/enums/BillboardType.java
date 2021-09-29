package com.souchy.jeffekseer.enums;

public enum BillboardType {

	Billboard(0),
	YAxisFixed(1),
	Fixed(2),
	RotatedBillboard(3),
	;
	
	
	public final int v;
	private BillboardType(int v) {
		this.v = v;
	}
	
	public static BillboardType parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
	
}
