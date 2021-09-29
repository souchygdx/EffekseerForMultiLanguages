package com.souchy.jeffekseer;

import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;

import effekseer.swig.EffekseerManagerCore;

public class EffectManager extends EffekseerManagerCore {
	
	private Queue<Effect> effects = new ConcurrentLinkedQueue<>();
	
	public void remove(Effect e) {
		effects.remove(e);
	}

	/**
	 * updates all effects
	 * 		effects update their time played and check onComplete
	 */
	public void act(float delta) {
		for(var fx : effects) 
			fx.act(delta);
	}
	
	
	public Effect loadEffect(String path, float magnifier) {
        Effect e = new Effect(this);
        var success = FXLoader.loadEffect(e, path, magnifier);
		if(success == null) return null;
		effects.add(e);
		return e;
	}
	
	public void dispose() {
		var it = effects.iterator();
		while(it.hasNext())
			it.next().delete();
			
		this.delete();
	}

}
