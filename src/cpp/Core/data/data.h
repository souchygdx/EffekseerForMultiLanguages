#pragma once

#include <assert.h>
#include <Effekseer.h>
#include "Effekseer/Effekseer.EffectNode.h"
#include "Effekseer/Effekseer.Vector2D.h"
#include "Effekseer/Effekseer.EffectImplemented.h"

/*
struct EffectBasicRenderParameter
{
	int32_t MaterialIndex = -1;

	int32_t ColorTextureIndex;

	int32_t AlphaTextureIndex;
	TextureWrapType AlphaTexWrapType;

	int32_t UVDistortionIndex;
	TextureWrapType UVDistortionTexWrapType;

	int32_t BlendTextureIndex;
	TextureWrapType BlendTexWrapType;

	int32_t BlendAlphaTextureIndex;
	TextureWrapType BlendAlphaTexWrapType;

	int32_t BlendUVDistortionTextureIndex;
	TextureWrapType BlendUVDistortionTexWrapType;

	struct FlipbookParameters
	{
		bool Enable;
		int32_t LoopType;
		int32_t DivideX;
		int32_t DivideY;
	} FlipbookParams;

	RendererMaterialType MaterialType;

	float UVDistortionIntensity;

	int32_t TextureBlendType;

	float BlendUVDistortionIntensity;

	bool EnableFalloff;
	struct
	{
		int32_t ColorBlendType;
		std::array<float, 4> BeginColor;
		std::array<float, 4> EndColor;
		float Pow = 1.0f;
	} FalloffParam;

	float EmissiveScaling;

	struct
	{
		float Color[4];
		float Threshold;
		float ColorScaling;
	} EdgeParam;

	AlphaBlendType AlphaBlend;
	TextureFilterType FilterType;
	TextureWrapType WrapType;
	bool ZWrite;
	bool ZTest;
	bool Distortion;
	float DistortionIntensity;

	float SoftParticleDistanceFar = 0.0f;
	float SoftParticleDistanceNear = 0.0f;
	float SoftParticleDistanceNearOffset = 0.0f;
};


struct MaterialTextureParameter
{
	//! 0 - color, 1 - value
	int32_t Type = 0;
	int32_t Index = 0;
};

*/