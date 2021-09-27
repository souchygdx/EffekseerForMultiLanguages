package com.mygdx.game;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

import effekseer.swig.EffekseerBackendCore;
import effekseer.swig.EffekseerEffectCore;
import effekseer.swig.EffekseerManagerCore;

import java.io.Console;
import java.io.File;

public class libGdxSample extends ApplicationAdapter {
	public SpriteBatch batch;
	public Texture img;
	public EffekseerManagerCore effekseerManagerCore;
	public EffekseerEffectCore effekseerEffectCore;
	public float time = 0.0f;

	@Override
	public void create () {
		batch = new SpriteBatch();
		img = new Texture("badlogic.jpg");

		System.loadLibrary("EffekseerNativeForJava");

		EffekseerBackendCore.InitializeAsOpenGL();

		effekseerManagerCore = new EffekseerManagerCore();
		effekseerManagerCore.Initialize(8000);

		String effectPath = "bin/main/Laser03.efkefc";
		effekseerEffectCore = FXLoader.loadEffect(effectPath, 50.0f);
		if (effekseerEffectCore == null) {
			System.out.print("Failed to load.");
			return;
		}
//		SWIGTYPE_p_Effekseer__EffectNode r = effekseerEffectCore.GetRoot();
	}

	@Override
	public void render () {

		if (time == 0.0f) {
			int efkhandle = effekseerManagerCore.Play(effekseerEffectCore);
			effekseerManagerCore.SetEffectPosition(efkhandle, 
					Gdx.graphics.getWidth() / 6.0f,
					Gdx.graphics.getHeight() / 2.0f, 
					0.0f);
		}

		time += Gdx.graphics.getDeltaTime();
		if (time > 2.0f) {
			time = 0.0f;
		}

		Gdx.gl.glClearColor(0, 0, 0, 1);
		// It needs to clear depth
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT | GL20.GL_DEPTH_BUFFER_BIT);
		//batch.begin();
		//batch.draw(img, 0, 0);
		//batch.end();

		effekseerManagerCore.SetViewProjectionMatrixWithSimpleWindow(Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
		effekseerManagerCore.Update(Gdx.graphics.getDeltaTime() / (1.0f / 60.0f));
		effekseerManagerCore.DrawBack();
		effekseerManagerCore.DrawFront();
	}
	
	@Override
	public void dispose () {
		batch.dispose();
		img.dispose();
		effekseerManagerCore.delete();
		effekseerEffectCore.delete();
		EffekseerBackendCore.Terminate();
	}

	
}
