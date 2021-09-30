package com.mygdx.game;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input.Keys;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.math.Vector3;
import com.souchy.jeffekseer.Effect;
import com.souchy.jeffekseer.Jeffekseer;
import com.souchy.jeffekseer.EffectManager;
import com.souchy.jeffekseer.Translation;
import com.souchy.jeffekseer.enums.AlphaBlendType;
import com.souchy.jeffekseer.enums.BindType;
import com.souchy.jeffekseer.enums.BindTypeParentTranslation;
import com.souchy.jeffekseer.enums.ParameterRotationType;
import com.souchy.jeffekseer.enums.ParameterScalingType;
import com.souchy.jeffekseer.enums.TextureFilterType;
import com.souchy.jeffekseer.enums.TextureWrapType;
import com.souchy.jeffekseer.enums.UVType;
import com.souchy.jeffekseer.struct.Float_rand;
import com.souchy.jeffekseer.struct.Int_rand;
import com.souchy.jeffekseer.struct.Vector3s;
import com.souchy.jeffekseer.struct.Vector3s.Vector3s_rand;
import com.souchy.jeffekseer.struct.Vector4s;
import com.souchy.jeffekseer.struct.Vector4s.Vector4s_rand;

import effekseer.swig.EffekseerBackendCore;
import effekseer.swig.EffekseerNodeCore;

public class Main extends ApplicationAdapter {

	public Basic3dSetup setup;
	public EffectManager manager;
	
	
	@Override
	public void create () {
		// create basic 3d world, camera, controller
		setup = new Basic3dSetup();
		
		// create effekseer manager and run effect
		manager = Jeffekseer.newManager();
		Jeffekseer.yUp = false; // the basic setup world is z-up so flip this
		runEffect(true);
	}
	
	/**
	 * load and play an effect
	 */
	public void runEffect(boolean mods) {
		String effectPath = "bin/main/Laser03.efkefc";
		Effect effect = manager.loadEffect(effectPath, 1);
		if (effect == null) {
			System.out.print("Failed to load.");
			return;
		}
		effect.setDuration(100f / 60f); // make it last 100 frames at 60fps
		effect.onComplete = effect::delete; // delete effect on complete
		if(mods) setEffectModifications(effect);
		effect.play();
		effect.setPosition(1, 1, 2); // this only works after the effect is playing. dont wait too long though. can update pos in real time in render() to make it follow a path for example
	}
	
	@Override
	public void render () {
		float delta = Gdx.graphics.getDeltaTime();
		
		// run effect with modifications 
		if(Gdx.input.isKeyJustPressed(Keys.NUM_1)) {
			runEffect(true);
		}
		// run effect without modifications
		if(Gdx.input.isKeyJustPressed(Keys.NUM_2)) {
			runEffect(false);
		}
		// reset camera position
		if(Gdx.input.isKeyJustPressed(Keys.SPACE)) {
			setup.resetCamera();
		}
		
		// update camera and controller
		setup.camera.update();
		setup.controller.update();
		// apply camera projection to effekseer (only needed if the camera moved)
		float[] p = setup.camera.projection.val;
		float[] v = setup.camera.view.val; 
		if(Jeffekseer.yUp) v = setup.camera.view.rotate(Vector3.X, 90).val;
		manager.setViewProjectionMatrix(p, v);
		
		// clear screen
		Gdx.gl.glClearColor(0, 0, 0, 0);
		Gdx.gl.glClear(
				GL20.GL_COLOR_BUFFER_BIT | GL20.GL_DEPTH_BUFFER_BIT| (Gdx.graphics.getBufferFormat().coverageSampling ? GL20.GL_COVERAGE_BUFFER_BIT_NV : 0));
		
		// render cubes platform
		setup.batch.begin(setup.camera);
		setup.batch.render(setup.cache, setup.env);
		setup.batch.end();

		// manager act (this updates effects which count their time playing)
		manager.act(delta);
		// manager render effects
		manager.Update(delta / (1.0f / 60.0f)); // 60 fps
		manager.DrawBack();
		manager.DrawFront();
	}
	
	@Override
	public void dispose () {
		manager.delete();
		EffekseerBackendCore.Terminate();
	}

	/**
	 * Usage examples of modifications. Can do in real time (render()) while the effect is playing.
	 */
	private void setEffectModifications(Effect effect) {
		EffekseerNodeCore root = effect.GetRoot();
		EffekseerNodeCore core0 = root.getChild(0);
		EffekseerNodeCore core1 = root.getChild(1);
		EffekseerNodeCore core2 = root.getChild(2);

		// translation works
//		float[] f = Translation.fixed(0f, 3f, 0f);
//		float[] pva = Translation.PVA(
//				new Vector3s(0, 0, 0), new Vector3s(0, 0, 0), 
//				new Vector3s(-0.1f, -0.1f, -0.1f), new Vector3s(0.0f, 0.1f, 0.1f), 
//				new Vector3s(0, 0, 0), new Vector3s(0, 0, 0)
//				);
//		pva = Translation.PVA_mean(
//				new Vector3s(0, 0, 0), new Vector3s(0, 0, 0), 
//				new Vector3s(0, 0, 0), new Vector3s(0.2f, 0.1f, 0.1f), 
//				new Vector3s(0, 0, 0), new Vector3s(0, 0, 0)
//				);
		float[] eas = Translation.easing(
				new Vector3s(0, 0, 0), new Vector3s(0, 0, 0), 
				new Vector3s(5, 5, 0), new Vector3s(5, 5, 0), 
				new Vector3s(10, 0, 0), new Vector3s(10, 0, 0)
				);
		
//		core0.setTranslationType(ParameterTranslationType.Fixed.v);
//		core0.setTranslationFixed(f);

//		core0.setTranslationType(ParameterTranslationType.PVA.v);
//		core0.setTranslationPVA(pva);

		// easing works as long as it's pre-set in the editor
//		core0.setTranslationType(ParameterTranslationType.Easing.v);
		core0.setTranslationEasing(eas);

	
		// child nodes
		EffekseerNodeCore core0track = core0.getChild(0);
		EffekseerNodeCore core0particle = core0track.getChild(0);

		EffekseerNodeCore core1track = core1.getChild(0);
		EffekseerNodeCore core1particle = core1track.getChild(0);

		EffekseerNodeCore core2track = core2.getChild(0);
		EffekseerNodeCore core2particle = core2track.getChild(0);
		
//		core0particle.setTranslationType(ParameterTranslationType.Fixed.v);
//		core1particle.setTranslationType(ParameterTranslationType.Fixed.v);
//		core2particle.setTranslationType(ParameterTranslationType.Fixed.v);

//		core0particle.setTranslationPVA(pva);
//		core1particle.setTranslationPVA(pva);
//		core2particle.setTranslationPVA(pva);
		
		// visibility works
		core0track.setVisibility(true);
		core0particle.setVisibility(true);
		core1track.setVisibility(true);
		core1particle.setVisibility(true);
		core2track.setVisibility(true);
		core2particle.setVisibility(true);
		
		// basic settings works 
		float[] basicSettings = Translation.basicSettings(25, BindTypeParentTranslation.WhenCreating, BindType.WhenCreating, BindType.WhenCreating, 
				true, false, false, new Int_rand(100, 100), new Float_rand(1, 1), new Float_rand(0, 0));
		core0particle.setParameterCommonValues(basicSettings);
		
		// basic render settings works except : blend, colorbind...
		float[] mat = Translation.basicRenderSettingsMaterialDefault(1, null, TextureFilterType.Linear, TextureWrapType.Repeat);
		float[] brenderSettings = Translation.basicRenderSettings(mat, AlphaBlendType.Sub, false, true, 
				false, 0f, new Vector3s(0,0,0),
				false, 0f, new Vector3s(0,0,0),
				UVType.Default, BindType.NotBind);
		core0particle.setBasicRenderSettings(brenderSettings);
		
		// color doesn't work properly. Needs the editor value to be white and the 100% alpha is like 127, i don't know how to fix
		float[] color = null;
		color = Translation.colorRandom(new Vector4s_rand(new Vector4s(0, 0, 255, 127), new Vector4s(255, 255, 255, 127)));
		color = Translation.colorEasing(new Vector4s_rand(0, 0, 255, 127), new Vector4s_rand(0, 0, 255, 127));
		color = Translation.colorFixed(new Vector4s(255, 0, 0, 127));
		core0particle.setRenderSettings_ColorAll(color);
		
		// generation works
		float[] gen = null;
		gen = Translation.generationLine(false, 2, 0, new Vector3s_rand(-5, 0, 0), new Vector3s_rand(7, 0, 0), Float_rand.zero);
//		gen = Translation.generationPoint(false, 0, 0, 0);
		core0particle.setGeneration(gen);
		
		// scaling works
		float[] scale = null;
		scale = Translation.fixed(0.1f, 0.3f, 0.1f);
		core0particle.setScalingType(ParameterScalingType.Fixed.v);
		core0particle.setScalingFixed(scale);
		
		// rotation works
		float[] rot = null;
//		rot = Translation.fixed(45, 0, 0);
//		core0.setRotationType(ParameterRotationType.Fixed.v);
//		core0.setRotationFixed(rot);
		rot = Translation.PVA(Vector3s.zero, new Vector3s(1f, 0, 0), Vector3s.zero);
		core0.setRotationType(ParameterRotationType.PVA.v);
		core0.setRotationPVA(rot);
		
	}
	
}
