package com.souchy.jeffekseer;

import com.souchy.jeffekseer.enums.AlphaBlendType;
import com.souchy.jeffekseer.enums.BindType;
import com.souchy.jeffekseer.enums.BindTypeParentTranslation;
import com.souchy.jeffekseer.enums.ColorMode;
import com.souchy.jeffekseer.enums.ColorType;
import com.souchy.jeffekseer.enums.GenerationType;
import com.souchy.jeffekseer.enums.RendererMaterialType;
import com.souchy.jeffekseer.enums.TextureFilterType;
import com.souchy.jeffekseer.enums.TextureWrapType;
import com.souchy.jeffekseer.enums.UVType;
import com.souchy.jeffekseer.struct.Float_rand;
import com.souchy.jeffekseer.struct.Int_rand;
import com.souchy.jeffekseer.struct.Vector3s;
import com.souchy.jeffekseer.struct.Vector3s.Vector3s_rand;
import com.souchy.jeffekseer.struct.Vector4s;
import com.souchy.jeffekseer.struct.Vector4s.Vector4s_rand;

/**
 * Util class to create all the arrays needed to send parameters to Effekseer <br>
 * This started as the translation (position) class and I didn't find a better name to englobe all
 */
public class Translation {

	//----------------------------------------------------------------------------------------- Translation / Rotation / Scaling

	public static float[] fixed(float x, float y, float z) {
		return new float[] { x, y, z, -1.0f };
	}
	
	public static float[] PVA(Vector3s pos, Vector3s speed, Vector3s accel) {
		return PVA(pos, pos, speed, speed, accel, accel);
	}
	public static float[] PVA_mean(Vector3s posMean, Vector3s posDev, Vector3s speedMean, Vector3s speedDev, Vector3s accelMean, Vector3s accelDev) {
		return PVA(
				posMean.sub(posDev), 		posMean.add(posDev), 
				speedMean.sub(speedDev), 	speedMean.add(speedDev), 
				accelMean.sub(accelDev), 	accelMean.add(accelDev)
				);
	}
	public static float[] PVA(Vector3s posMin, Vector3s posMax, Vector3s speedMin, Vector3s speedMax, Vector3s accelMin, Vector3s accelMax) {
		float[] t = new float[posMin.size() + posMax.size() + 2 + speedMin.size() + speedMax.size() + 2 + accelMin.size() + accelMax.size() + 2];
		int i = 0;
		i = posMin.write(t, i);
		i = posMax.write(t, i);
		t[i++] = -1;
		t[i++] = -1;
		i = speedMin.write(t, i);
		i = speedMax.write(t, i);
		t[i++] = -1;
		t[i++] = -1;
		i = accelMin.write(t, i);
		i = accelMax.write(t, i);
		t[i++] = -1;
		t[i++] = -1;
		return t;
	}
	
	public static float[] easing(Vector3s start, Vector3s end) {
		return easing(start, start, end, end);
	}
	public static float[] easing(Vector3s start, Vector3s mid, Vector3s end) {
		return easing(start, start, mid, mid, end, end);
	}
	public static float[] easing(Vector3s startMin, Vector3s startMax, Vector3s endMin, Vector3s endMax) {
		return easing(startMin, startMax, Vector3s.zero, Vector3s.zero, endMin, endMax, false, false);
	}
	public static float[] easing(Vector3s startMin, Vector3s startMax, Vector3s midMin, Vector3s midMax, Vector3s endMin, Vector3s endMax) {
		return easing(startMin, startMax, midMin, midMax, endMin, endMax, false, true);
	}
	/** isIndividualEnabled, isMiddleEnabled, type */
	public static float[] easing(Vector3s startMin, Vector3s startMax, Vector3s midMin, Vector3s midMax, Vector3s endMin, Vector3s endMax, boolean isIndividualEnabled, boolean isMidEnabled) {
		float[] t = new float[startMin.size() + startMax.size() + 2 + midMin.size() + midMax.size() + 2 + endMin.size() + endMax.size() + 2 + 3];
		int i = 0;
		i = startMin.write(t, i);
		i = startMax.write(t, i);
		t[i++] = -1;
		t[i++] = -1;
		i = midMin.write(t, i);
		i = midMax.write(t, i);
		t[i++] = -1;
		t[i++] = -1;
		i = endMin.write(t, i);
		i = endMax.write(t, i);
		t[i++] = -1;
		t[i++] = -1;

		t[i++] = isIndividualEnabled ? 1 : 0;
		t[i++] = isMidEnabled ? 1 : 0;
		t[i++] = 0; // type
		return t;
	}
	

	//----------------------------------------------------------------------------------------- Generation Settings / Spawning Method
	
	
	public static float[] generationPoint(boolean angleOnSpawn, float x, float y, float z) {
		return generationPoint(angleOnSpawn, x, y, z, x, y, z);
	}
	public static float[] generationPoint(boolean angleOnSpawn, float x, float y, float z, float x1, float y1, float z1) {
		float[] t = new float[2 + 3 * 2];
		int i = 0;
		t[i++] = GenerationType.Point.v; 
		t[i++] = angleOnSpawn ? 1 : 0;
		t[i++] = x;
		t[i++] = y;
		t[i++] = z;
		t[i++] = x;
		t[i++] = y;
		t[i++] = z;
		return t;
	}

	public static float[] generationLine(boolean angleOnSpawn, int vertices, int spawnMode, float x0, float y0, float z0, float x1, float y1, float z1) {
		return generationLine(angleOnSpawn, vertices, spawnMode, new Vector3s_rand(x0, y0, z0), new Vector3s_rand(x0, y0, z0), Float_rand.zero);
	}
	public static float[] generationLine(boolean angleOnSpawn, int vertices, int spawnMode, Vector3s_rand start, Vector3s_rand end, Float_rand noize) {
		float[] t = new float[2 + 2 + start.size() + end.size() + noize.size()];
		int i = 0;
		t[i++] = GenerationType.Line.v; 
		t[i++] = angleOnSpawn ? 1 : 0;
		t[i++] = vertices;
		t[i++] = spawnMode;
		i = start.write(t, i);
		i = end.write(t, i);
		i = noize.write(t, i);
		return t;
	}

	public static float[] generationCircle(boolean angleOnSpawn, int vertices, int spawnMode, int axis, Float_rand radius, Float_rand startAngle, Float_rand endAngle, Float_rand noize) {
		float[] t = new float[2 + 3 + radius.size() + startAngle.size() + endAngle.size() + noize.size()];
		int i = 0;
		t[i++] = GenerationType.Circle.v; 
		t[i++] = angleOnSpawn ? 1 : 0;
		t[i++] = vertices;
		t[i++] = spawnMode;
		t[i++] = axis;
		i = radius.write(t, i);
		i = startAngle.write(t, i);
		i = endAngle.write(t, i);
		i = noize.write(t, i);
		return t;
	}

	public static float[] generationSphere(boolean angleOnSpawn, Float_rand radius, Float_rand rotationX, Float_rand rotationY) {
		float[] t = new float[2 + radius.size() + rotationX.size() + rotationY.size()];
		int i = 0;
		t[i++] = GenerationType.Sphere.v; 
		t[i++] = angleOnSpawn ? 1 : 0;
		i = radius.write(t, i);
		i = rotationX.write(t, i);
		i = rotationY.write(t, i);
		return t;
	}
	
	public static float[] generationModel(boolean angleOnSpawn) {
		float[] t = new float[2];
		int i = 0;
		t[i++] = GenerationType.Model.v; 
		t[i++] = angleOnSpawn ? 1 : 0;
		// model path....
		return t;
	}
	
	//----------------------------------------------------------------------------------------- Basic Settings
	
	public static float[] basicSettings(
			int maxGeneration, 
			BindTypeParentTranslation inheritPosition,
			BindType inheritRotation,
			BindType inheritScale, 
			boolean RemoveWhenLifeIsExtinct,
			boolean RemoveWhenParentIsRemoved,
			boolean RemoveWhenChildrenIsExtinct,
			Int_rand life,
			Float_rand generationTime,
			Float_rand initialDelay
			) {

		float[] t = new float[1 + 3 + 3 + life.size() + generationTime.size() + initialDelay.size()];
		int i = 0;
		t[i++] = maxGeneration;
		t[i++] = inheritPosition.v;
		t[i++] = inheritRotation.v;
		t[i++] = inheritScale.v;
		t[i++] = RemoveWhenLifeIsExtinct ? 1 : 0;
		t[i++] = RemoveWhenParentIsRemoved ? 1 : 0;
		t[i++] = RemoveWhenChildrenIsExtinct ? 1 : 0;
		i = life.write(t, i);
		i = generationTime.write(t, i);
		i = initialDelay.write(t, i);
		
		return t;
	}

	//----------------------------------------------------------------------------------------- Basic Render Settings

	public static float[] basicRenderSettingsMaterialDefault(float emissiveScaling, Object texture, TextureFilterType filterType, TextureWrapType wrapType){
		float[] t = new float[1 + 3 + 0];
		int i = 0;
		t[i++] = RendererMaterialType.Default.v;
		t[i++] = emissiveScaling;
		t[i++] = filterType.v;
		t[i++] = wrapType.v;
		return t;
	}
	public static float[] basicRenderSettingsMaterialDistortion(Object texture, TextureFilterType filterType, TextureWrapType wrapType, int distortionIntensity){
		float[] t = new float[1 + 3 + 0];
		int i = 0;
		t[i++] = RendererMaterialType.BackDistortion.v;
		t[i++] = filterType.v;
		t[i++] = wrapType.v;
		t[i++] = distortionIntensity;
		return t;
	}

	public static float[] basicRenderSettingsMaterialLighting(float emissiveScaling, Object texture, Object normalMap, TextureFilterType[] filterType, TextureWrapType[] wrapType){
		float[] t = new float[1 + 5 + 0 + 0];
		int i = 0;
		t[i++] = RendererMaterialType.Lighting.v;
		t[i++] = emissiveScaling;
		t[i++] = filterType[0].v;
		t[i++] = wrapType[0].v;
		t[i++] = filterType[1].v;
		t[i++] = wrapType[1].v;
		return t;
	}

	public static float[] basicRenderSettingsMaterialFile(String path){
		float[] t = new float[1 + 0];
		int i = 0;
		t[i++] = RendererMaterialType.File.v;
		// file path..
		return t;
	}
	
	public static float[] basicRenderSettings(
			float[] material, 
			AlphaBlendType blend, boolean depthSet, boolean depthTest, 
			boolean fadeInType, float fadeInFrames, Vector3s fadeInEasing, 
			boolean fadeOutType, float fadeOutFrames, Vector3s fadeOutEasing,
			UVType UvType, BindType inheritColor) {
		float[] t = new float[material.length + 3 + 2 * 5 + 2];
		int i = 0;

		// includes the material type
		for(float f : material) {
			t[i++] = f;
		}
		
		t[i++] = blend.v;
		t[i++] = depthSet ? 1 : 0;
		t[i++] = depthTest ? 1 : 0;
		
		t[i++] = fadeInType ? 1 : 0;
		t[i++] = fadeInFrames;
		fadeInEasing.write(t, i);
		
		t[i++] = fadeOutType ? 1 : 0;
		t[i++] = fadeOutFrames;
		fadeOutEasing.write(t, i);

		t[i++] = UvType.v;
		t[i++] = inheritColor.v;
		
		// a file material can add customData1, customData2
		return t;
	}
	

	//----------------------------------------------------------------------------------------- Model Render Settings
	
	public static float[] modelRenderSettings() {
		float[] t = new float[1];
		int i = 0;
		t[i++] = 0;
		
		return t;
	}
	
	/**
	 * values are based on 255
	 */
	public static float[] colorFixed(Vector4s v) {
		float[] t = new float[1 + v.size()];
		int i = 0;
		t[i++] = ColorType.Fixed.v;
		i = v.write(t, i);
		return t;
	}
	/**
	 * values are based on 255
	 */
	public static float[] colorRandom(Vector4s_rand v) {
		float[] t = new float[1 + 1 + v.size()];
		int i = 0;
		t[i++] = ColorType.Random.v;
		t[i++] = ColorMode.RGBA.v;
		i = v.write(t, i);
		return t;
	}
	/**
	 * values are based on 255
	 */
	public static float[] colorEasing(Vector4s_rand start, Vector4s_rand end) {
		float[] t = new float[1 + 1 + start.size() + 1 + end.size()];
		int i = 0;
		t[i++] = ColorType.Easing.v;
		t[i++] = ColorMode.RGBA.v;
		i = start.write(t, i);
		t[i++] = ColorMode.RGBA.v;
		i = end.write(t, i);
		return t;
	}
	
}
