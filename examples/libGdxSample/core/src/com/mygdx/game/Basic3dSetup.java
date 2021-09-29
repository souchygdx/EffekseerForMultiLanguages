package com.mygdx.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.Camera;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g3d.Environment;
import com.badlogic.gdx.graphics.g3d.Model;
import com.badlogic.gdx.graphics.g3d.ModelBatch;
import com.badlogic.gdx.graphics.g3d.ModelCache;
import com.badlogic.gdx.graphics.g3d.ModelInstance;
import com.badlogic.gdx.graphics.g3d.attributes.BlendingAttribute;
import com.badlogic.gdx.graphics.g3d.attributes.ColorAttribute;
import com.badlogic.gdx.graphics.g3d.utils.CameraInputController;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.utils.viewport.ExtendViewport;
import com.badlogic.gdx.utils.viewport.Viewport;

/**
 * Sets a absic 3d world with a platform of 15x15 cubes
 */
public class Basic3dSetup {

	public Camera camera;
	public Viewport viewport;
	public Environment env;
	public CameraInputController controller;
	
	public ModelBatch batch;
	public ModelCache cache;

	public Basic3dSetup() {
		// init stuff
		camera = new OrthographicCamera();
		controller = new CameraInputController(camera);
		viewport = createViewport(camera);
		env = createEnvironment();
		batch = new ModelBatch(); 
		Gdx.input.setInputProcessor(controller);
		
		
		// load cube model
		String path = "cube.g3dj";
		var assets = new AssetManager();
		assets.load(path, Model.class);
		assets.finishLoading();
		Model cubeModel = assets.get(path); 
		
		// create small platform
		float size = 15;
		int scl = 1;
		cache = new ModelCache();
		cache.begin();
		for(int i = 0; i < size; i++) {
			for(int j = 0; j < size; j++) {
				var inst = new ModelInstance(cubeModel);
				inst.transform.translate(i, j, 0).scale(scl, scl, scl);
				if((i + j) % 2 == 0)
					inst.materials.get(0).set(ColorAttribute.createDiffuse(Color.DARK_GRAY));
				else 
					inst.materials.get(0).set(ColorAttribute.createDiffuse(Color.GRAY));
        		inst.materials.get(0).set(new BlendingAttribute(1f)); 
				cache.add(inst);
			}
		}
		cache.end();
		
		// set camera pos
		resetCamera();
	}

	private Environment createEnvironment() {
		var env = new Environment();
		var ambiant = 0.8f;
		env.set(new ColorAttribute(ColorAttribute.AmbientLight, ambiant, ambiant, ambiant, 1f));
		return env;
	}
	

	private Viewport createViewport(Camera cam) {
		float viewportSize = 16; 
		Viewport viewport = new ExtendViewport(viewportSize * 16/9, viewportSize, cam);
		viewport.update(Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
		return viewport;
	}
	
	public void topView() {
		var center = new Vector3(7.5f, 7.5f, 0f);
		camera.direction.set(0, 0, -1f);
		camera.up.set(1, 1, -1f);
		camera.position.set(center.x, center.y, center.z); 
		camera.near = -30f;
		camera.far = 120f;
		camera.update();
	}
	
	public void resetCamera() {
		topView();
		camera.rotate(45, camera.up.y, -camera.up.x, 0);
	}

	
}
