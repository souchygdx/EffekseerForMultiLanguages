package com.souchy.jeffekseer.struct;

public record Int_rand(int min, int max) {
	public static final Int_rand zero = new Int_rand(0, 0);
	public Int_rand(int v) {
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
