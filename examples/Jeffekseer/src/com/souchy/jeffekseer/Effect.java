package com.souchy.jeffekseer;

import effekseer.swig.EffekseerEffectCore;

/**
 * Time units are in seconds
 * 
 * An effect is playing if it has a pointer reference (int ref)
 * 
 * Effects run at 60 fps so duration time is [frames / 60]
 * 
 */
public class Effect extends EffekseerEffectCore {
	
	@FunctionalInterface
	public static interface OnCompletionLambda {
		public void run();
	}
	/**
	 * value to represent that an effect has no ref/handle, aka is not playing.
	 */
	private static final int noref = Integer.MIN_VALUE;
	
	/**
	 * manager reference for access to effect-modifying methods
	 */
	private final EffectManager manager;
	/**
	 * id ref/handle to the effect inside the effekseer runtime.
	 * Set on play and reset on stop/delete.
	 */
	private int ref = noref;
	/**
	 * Time the effect has been playing in seconds (or 0 if it is stopped)
	 */
	private float time = 0;
	/**
	 * Lambda to execute when the effect completes (when time >= duration)
	 */
	public OnCompletionLambda onComplete = () -> stop();
	
	/** 
	 * Just a default duration of 100 frames to make sure effects play and complete. 
	 * You should set a real duration yourself.
	 */
	private float duration = 100f / 60f;
	
	public Effect(EffectManager manager) {
		this.manager = manager;
	}
	
	/**
	 * updates :
	 * 		time played and checks for onComplete
	 */
	public void act(float delta) {
		// compare time to duration
		if(isPlaying() && getDuration() > 0) {
			time += delta;
			if(time > getDuration() && onComplete != null)
				onComplete.run();
		}
	}
	
	public void play() {
		if(getRef() == noref) {
			time = 0;
			ref = manager.Play(this);
		}
	}
	public void pause(boolean pause) {
		if(getRef() != noref) {
			manager.SetPaused(getRef(), pause);
		}
	}
	
	public void stop() {
		if(getRef() != noref) {
			manager.Stop(getRef());
			ref = noref;
			time = 0;
		}
	}
	
	public void delete() {
		stop();
		manager.remove(this);
		super.delete();
	}
	
	public float getTime() {
		return time;
	}

	public void setDuration(float duration) {
		this.duration = duration;
	}
	public float getDuration() {
		return duration; 
	}
	
	public boolean isPlaying() {
		return getRef() != noref;
	}
	
	/**
	 * Sets the position of the whole effect.
	 */
	public void setPosition(float x, float y, float z) {
		if(getRef() != noref) {
			if(Jeffekseer.yUp) { 
				// if y up, swap the z and y then flip the y to combine with the 90° X rotation and bring back everything to normal
		        manager.SetEffectPosition(getRef(),
		                x * Jeffekseer.worldScaleX + Jeffekseer.worldOffsetX,
		                z * Jeffekseer.worldScaleZ + Jeffekseer.worldOffsetZ,
		                -y * Jeffekseer.worldScaleY - Jeffekseer.worldOffsetY
		        );
			} else {
		        manager.SetEffectPosition(getRef(),
		                x * Jeffekseer.worldScaleX + Jeffekseer.worldOffsetX,
		                y * Jeffekseer.worldScaleY + Jeffekseer.worldOffsetY,
		                z * Jeffekseer.worldScaleZ + Jeffekseer.worldOffsetZ
		        );
			}
		}
	}
	
	public void setPosition(double x, double y, double z) {
		setPosition((float) x, (float) y, (float) z);
	}
	
	/*
	 * can set an additional base matrix that works kind of like the worldScale/Offset I use 
	 * this is separate from the position etc
	 */
	public void setBaseMatrix(float[] v) {
		manager.SetEffectTransformBaseMatrix(getRef(), v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9], v[10], v[11]);
	}

	public int getRef() {
		return ref;
	}
	
}
