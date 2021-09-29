package com.souchy.jeffekseer.struct;

public record Vector4s(float r, float g, float b, float a) {

	public static final Vector4s zero = new Vector4s(0, 0, 0, 0);

	public int size() {
		return 4;
	}

	public int write(float[] array, int index) {
		array[index++] = r;
		array[index++] = g;
		array[index++] = b;
		array[index++] = a;
		return index;
	}
	
	
	public static record Vector4s_rand(float r, float g, float b, float a, float r1, float g1, float b1, float a1) {
		public static final Vector4s_rand zero = new Vector4s_rand(0, 0, 0, 0, 0, 0, 0, 0);

		public Vector4s_rand(float r, float g, float b, float a) {
			this(r, g, b, a, r, g, b, a);
		}
		public Vector4s_rand(Vector4s min, Vector4s max) {
			this(min.r, min.g, min.b, min.a, max.r, max.g, max.b, max.a);
		}

		public int size() {
			return 2 * 4;
		}

		public int write(float[] array, int index) {
			array[index++] = r;
			array[index++] = g;
			array[index++] = b;
			array[index++] = a;

			array[index++] = r1;
			array[index++] = g1;
			array[index++] = b1;
			array[index++] = a1;
			return index;
		}
	}
	
	
	
}
