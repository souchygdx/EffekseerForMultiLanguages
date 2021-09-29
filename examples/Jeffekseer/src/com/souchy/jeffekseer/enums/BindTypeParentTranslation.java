package com.souchy.jeffekseer.enums;

public enum BindTypeParentTranslation {

	NotBind(0),
	NotBind_Root(3),
	WhenCreating(1),
	Always(2),
	NotBind_FollowParent(4),
	WhenCreating_FollowParent(5),
	
	;
	
	
	public final int v;
	private BindTypeParentTranslation(int v) {
		this.v = v;
	}

	
	public static BindTypeParentTranslation parse(int v) {
		for(var t : values()) 
			if(t.v == v) 
				return t;
		return null;
	}
	
	
}
