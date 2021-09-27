package com.mygdx.game;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.badlogic.gdx.Gdx;

import effekseer.swig.EffekseerEffectCore;
import effekseer.swig.EffekseerTextureType;

public class FXLoader {
	
	private static byte[] read(String path) {
    	try {
    		Path p = Paths.get(path);
    		System.out.println("FXLoader path [" + path + "] " + new File(".").getAbsolutePath());
			return Files.readAllBytes(p);
		} catch (IOException e) {
			e.printStackTrace();
			return new byte[0];
		}
	}
	
	private static byte[] read(File handle) {
		return read(handle.getPath());
	}
	
    public static EffekseerEffectCore loadEffect(String effectPath, float magnification) {
        //com.badlogic.gdx.files.FileHandle handle = Gdx.files.internal(effectPath);
//    	var path = Paths.get(effectPath);
    	File handle = new File(effectPath);
//    	Files.readAllBytes(path);
        EffekseerEffectCore effectCore = new EffekseerEffectCore();

        // load an effect
        {
            byte[] bytes = read(handle); // handle.readBytes();
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

	    for(int t = 0; t < 3; t++)
        {
            for (int i = 0; i < effectCore.GetTextureCount(textureTypes[t]); i++) {
                String path = (new File(effectPath)).getParent();
                if (path != null) {
                    path += "/" + effectCore.GetTexturePath(i, textureTypes[t]);
                } else {
                    path = effectCore.GetTexturePath(i, textureTypes[t]);
                }
                
//                handle = Gdx.files.internal(path);
//                byte[] bytes = handle.readBytes();
                byte[] bytes = read(path);
                effectCore.LoadTexture(bytes, bytes.length, i, textureTypes[t]);
            }
        }

        for (int i = 0; i < effectCore.GetModelCount(); i++) {
            String path = (new File(effectPath)).getParent();
            if (path != null) {
                path += "/" + effectCore.GetModelPath(i);
            } else {
                path = effectCore.GetModelPath(i);
            }

//            handle = Gdx.files.internal(path);
//            byte[] bytes = handle.readBytes();
            byte[] bytes = read(path);
            effectCore.LoadModel(bytes, bytes.length, i);
        }

		for (int i = 0; i < effectCore.GetMaterialCount(); i++) {
			String path = (new File(effectPath)).getParent();
			if (path != null) {
				path += "/" + effectCore.GetMaterialPath(i);
			} else {
				path = effectCore.GetMaterialPath(i);
			}

//			handle = Gdx.files.internal(path);
//			byte[] bytes = handle.readBytes();
            byte[] bytes = read(path);
			effectCore.LoadMaterial(bytes, bytes.length, i);
		}

		for (int i = 0; i < effectCore.GetCurveCount(); i++) {
			String path = (new File(effectPath)).getParent();
			if (path != null) {
				path += "/" + effectCore.GetCurvePath(i);
			} else {
				path = effectCore.GetCurvePath(i);
			}

//			handle = Gdx.files.internal(path);
//			byte[] bytes = handle.readBytes();
            byte[] bytes = read(path);
			effectCore.LoadCurve(bytes, bytes.length, i);
		}

        // TODO sound

        return effectCore;
    }
    
    
}
