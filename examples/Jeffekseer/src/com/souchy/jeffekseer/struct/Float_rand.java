package com.souchy.jeffekseer.struct;

public record Float_rand(float min, float max) {
	public static final Float_rand zero = new Float_rand(0, 0);
	public Float_rand(float v) {
		this(v, v);
	}
	public int size() {
		return 2;
	}
	public int write(float[] array, int index) {
		array[index++] = min;
		array[index++] = max;
		return index;
	}
}