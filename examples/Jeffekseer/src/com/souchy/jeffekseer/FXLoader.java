package com.souchy.jeffekseer;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.function.Function;

import effekseer.swig.EffekseerEffectCore;
import effekseer.swig.EffekseerManagerCore;
import effekseer.swig.EffekseerTextureType;

public class FXLoader {
	
	public static Function<String, byte[]> read = (String path) -> {
    	try {
    		Path p = Paths.get(path);
//    		System.out.println("Jeffekseer FXLoader path [" + path + "] " + new File(".").getAbsolutePath());
			return Files.readAllBytes(p);
		} catch (IOException e) {
			e.printStackTrace();
			return new byte[0];
		}
	};
	
	
    public static EffekseerEffectCore loadEffect(EffekseerEffectCore effectCore, String effectPath, float magnification) {
//      com.badlogic.gdx.files.FileHandle handle = Gdx.files.internal(effectPath);
    	//File handle = new File(effectPath);
    	
        // load an effect
        {
            byte[] bytes = read.apply(effectPath); // handle.readBytes();
            if (!effectCore.Load(bytes, bytes.length, magnification)) {
                System.out.print("Failed to load.");
                return null;
            }
        }

        // load textures
        EffekseerTextureType[] textureTypes = new EffekseerTextureType[] {
                EffekseerTextureType.Color,
                EffekseerTextureType.Normal,
                EffekseerTextureType.Distortion,
        };
        
        // textures
		for (int t = 0; t < 3; t++) {
			for (int i = 0; i < effectCore.GetTextureCount(textureTypes[t]); i++) {
				String path = new File(effectPath).getParent();
				path = fixPath(path, effectCore.GetTexturePath(i, textureTypes[t]));
				byte[] bytes = read.apply(path);
				effectCore.LoadTexture(bytes, bytes.length, i, textureTypes[t]);
			}
		}
		// models
		for (int i = 0; i < effectCore.GetModelCount(); i++) {
			String path = new File(effectPath).getParent();
			path = fixPath(path, effectCore.GetModelPath(i));
			byte[] bytes = read.apply(path);
			effectCore.LoadModel(bytes, bytes.length, i);
		}
		// materials
		for (int i = 0; i < effectCore.GetMaterialCount(); i++) {
			String path = new File(effectPath).getParent();
			path = fixPath(path, effectCore.GetMaterialPath(i));
            byte[] bytes = read.apply(path);
			effectCore.LoadMaterial(bytes, bytes.length, i);
		}
		// curves
		for (int i = 0; i < effectCore.GetCurveCount(); i++) {
			String path = new File(effectPath).getParent();
			path = fixPath(path, effectCore.GetCurvePath(i));
            byte[] bytes = read.apply(path);
			effectCore.LoadCurve(bytes, bytes.length, i);
		}

        // TODO sound

        return effectCore;
    }
    
    private static String fixPath(String path, String add) {
		if (path != null) {
			path += "/" + add;
		} else {
			path = add;
		}
		return path;
    }
    
}
