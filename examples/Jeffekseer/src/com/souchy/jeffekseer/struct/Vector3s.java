package com.souchy.jeffekseer.struct;

public record Vector3s(float x, float y, float z) {
//	public float x, y, z;
	
	public static final Vector3s zero = new Vector3s(0, 0, 0);
	

	public Vector3s add(Vector3s v) {
		return new Vector3s(x + v.x, y + v.y, z + v.z);
	}
	public Vector3s sub(Vector3s v) {
		return new Vector3s(x - v.x, y - v.y, z - v.z);
	}
	public Vector3s mult(Vector3s v) {
		return new Vector3s(x * v.x, y * v.y, z * v.z);
	}
	public Vector3s scl(float scl) {
		return new Vector3s(x * scl, y * scl, z * scl);
	}
	
	
	public int write(float[] array, int index) {
		array[index++] = x;
		array[index++] = y;
		array[index++] = z;
		return index;
	}

	public int size() {
		return 3;
	}
	
	
	
	public static record Vector3s_rand(float x, float y, float z, float x1, float y1, float z1) {
		public static final Vector3s_rand zero = new Vector3s_rand(0, 0, 0);
		
		public Vector3s_rand(Vector3s min, Vector3s max) {
			this(min.x, min.y, min.z, max.x, max.y, max.z);
		}
		public Vector3s_rand(float x, float y, float z) {
			this(x, y, z, x, y, z);
		}
		public int size() {
			return 3 * 2;
		}
		public int write(float[] array, int index) {
			array[index++] = x;
			array[index++] = y;
			array[index++] = z;

			array[index++] = x1;
			array[index++] = y1;
			array[index++] = z1;
			return index;
		}
	}

	
}
