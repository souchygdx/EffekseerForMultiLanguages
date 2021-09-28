#pragma once

#include "EffekseerBackendCore.h"
#include "data/data.h"
#include "data/enums.h"

#include "Effekseer/Effekseer.EffectImplemented.h"
#include "Effekseer/Effekseer.EffectNode.h"
#include "Effekseer/Effekseer.Vector2D.h"
#include <Effekseer.h>
#include <assert.h>

//----------------------------------------------------------------------------------
// enums
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Util structs for conversion / jni passing
//----------------------------------------------------------------------------------
struct FloatArray
{
	float values[32];
};
/*
struct Fixed
{
	float v3;
};
struct PVA
{
	random_v3 location;
	random_v3 velocity;
	random_v3 acceleration;
};
struct Easing
{
	random_v3 start;
	random_v3 middle;
	random_v3 end;
	bool isMiddleActive;
};
struct Curve
{
	// ???
	// general : start/end, sampling, offset, timelineMode
	// chaque point : frame, val, left/right x2, type
};
struct v3
{
	float x,y,z;
};
struct random_v3
{
	v3 min;
	v3 max;
};
*/

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class EffekseerNodeCore
{
	friend class EffekseerEffectCore;

private:
	Effekseer::EffectNodeImplemented* node_ = nullptr;
	EffekseerNodeCore(Effekseer::EffectNode* node_);
	EffekseerNodeCore(Effekseer::EffectNodeImplemented* node_);
	~EffekseerNodeCore();

protected:
public:
	EffekseerNodeCore* getChild(int index);
	int getChildCount();

	// EffectBasicRenderParameter getBasicRenderParameter();
	// void setBasicRenderParameter(EffectBasicRenderParameter param);

	int getTranslationType();
	void setTranslationType(int type);
	// Effekseer::ParameterTranslationFixed getTranslationFixed();
	// void setTranslationFixed(Effekseer::ParameterTranslationFixed fixed);

	FloatArray getTranslationFixed();
	void setTranslationFixed(float values[]);
	FloatArray getTranslationPVA();
	void setTranslationPVA(float values[]);
	FloatArray getTranslationEasing();
	void setTranslationEasing(float values[]);
};