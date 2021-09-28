#pragma once

#include <assert.h>
#include <Effekseer.h>
#include "Effekseer/Effekseer.EffectNode.h"
#include "Effekseer/Effekseer.Vector2D.h"
#include "Effekseer/Effekseer.EffectImplemented.h"

enum class AlphaBlendType : int32_t
{
	/// <summary>
	/// 不透明
	/// </summary>
	Opacity = 0,
	/// <summary>
	/// 透明
	/// </summary>
	Blend = 1,
	/// <summary>
	/// 加算
	/// </summary>
	Add = 2,
	/// <summary>
	/// 減算
	/// </summary>
	Sub = 3,
	/// <summary>
	/// 乗算
	/// </summary>
	Mul = 4,
};

enum class TextureFilterType : int32_t
{
	Nearest = 0,
	Linear = 1,
};

enum class TextureWrapType : int32_t
{
	Repeat = 0,
	Clamp = 1,
};

enum class CullingType : int32_t
{
	Front = 0,
	Back = 1,
	Double = 2,
};
enum ParameterTranslationType
{
	ParameterTranslationType_Fixed = 0,
	ParameterTranslationType_PVA = 1,
	ParameterTranslationType_Easing = 2,
	ParameterTranslationType_FCurve = 3,
	ParameterTranslationType_NurbsCurve = 4,
	ParameterTranslationType_ViewOffset = 5,

	ParameterTranslationType_None = 0x7fffffff - 1,

	ParameterTranslationType_DWORD = 0x7fffffff,
};

enum class Easing3Type : int32_t
{
	StartEndSpeed = 0,
	Linear = 1,

	EaseInQuadratic = 10,
	EaseOutQuadratic = 11,
	EaseInOutQuadratic = 12,

	EaseInCubic = 20,
	EaseOutCubic = 21,
	EaseInOutCubic = 22,

	EaseInQuartic = 30,
	EaseOutQuartic = 31,
	EaseInOutQuartic = 32,

	EaseInQuintic = 40,
	EaseOutQuintic = 41,
	EaseInOutQuintic = 42,

	EaseInBack = 50,
	EaseOutBack = 51,
	EaseInOutBack = 52,

	EaseInBounce = 60,
	EaseOutBounce = 61,
	EaseInOutBounce = 62,
};
/**
	@brief	material type
*/
enum class RendererMaterialType : int32_t
{
	Default = 0,
	BackDistortion = 6,
	Lighting = 7,
	File = 128,
};
