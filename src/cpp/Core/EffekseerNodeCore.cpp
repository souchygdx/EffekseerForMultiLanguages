#include "EffekseerNodeCore.h"
#include "EffekseerBackendCore.h"
#include "EffekseerEffectCore.h"
#include "EffekseerManagerCore.h"
//#include <EffekseerRendererGL.h>
#include "data/enums.h"
#include "data/data.h"

#include "Effekseer/Effekseer.EffectImplemented.h"
#include "Effekseer/Effekseer.EffectNode.h"
#include "Effekseer/Effekseer.Vector2D.h"
#include <Effekseer.h>
#include <assert.h>


// ctor
EffekseerNodeCore::EffekseerNodeCore(Effekseer::EffectNode* node_) {
	this->node_ = (Effekseer::EffectNodeImplemented*) node_; 
}
// ctor
EffekseerNodeCore::EffekseerNodeCore(Effekseer::EffectNodeImplemented* node_) {
	this->node_ = node_;
}
// dtor
EffekseerNodeCore::~EffekseerNodeCore() {}

// children
EffekseerNodeCore* EffekseerNodeCore::getChild(int index) { 
	return new EffekseerNodeCore(node_->GetChild(index)); 
}
int EffekseerNodeCore::getChildCount() { return node_->GetChildrenCount(); }


// basic render parameters
//EffectBasicRenderParameter EffekseerNodeCore::getBasicRenderParameter() { 
//	return node_->GetBasicRenderParameter(); 
//}
//void EffekseerNodeCore::setBasicRenderParameter(EffectBasicRenderParameter param) { 
//	node_->SetBasicRenderParameter((Effekseer::EffectBasicRenderParameter) param); 
//}

// translation
#pragma region translation
int EffekseerNodeCore::getTranslationType() { 
	return static_cast<int>(node_->TranslationType);
}
void EffekseerNodeCore::setTranslationType(int type)
{
	if (node_ == nullptr) return;
	try {
		node_->TranslationType = static_cast<Effekseer::ParameterTranslationType>(type);
	} catch (...) {

	}
}
// translation fixed
// Effekseer::ParameterTranslationFixed EffekseerNodeCore::getTranslationFixed() { return node_->TranslationFixed; }
// void EffekseerNodeCore::setTranslationFixed(Effekseer::ParameterTranslationFixed fixed) { node_->TranslationFixed = fixed; }

FloatArray EffekseerNodeCore::getTranslationFixed()
{
	// 4 values
	FloatArray values{{node_->TranslationFixed.Position.X,
					   node_->TranslationFixed.Position.Y,
					   node_->TranslationFixed.Position.Z,
					   node_->TranslationFixed.RefEq}};
	return values;
	/*return std::array<float, 4> {
			node_->TranslationFixed.Position.X,
			node_->TranslationFixed.Position.Y,
			node_->TranslationFixed.Position.Z,
			node_->TranslationFixed.RefEq
	};*/
}
void EffekseerNodeCore::setTranslationFixed(float values[])
{
	int i = 0;
	node_->TranslationFixed.Position.X = values[i++];
	node_->TranslationFixed.Position.Y = values[i++];
	node_->TranslationFixed.Position.Z = values[i++];
	node_->TranslationFixed.RefEq = values[i++];
}

FloatArray EffekseerNodeCore::getTranslationPVA()
{
	// 24 values
	// float values[] {}
	FloatArray arr = {
		{node_->TranslationPVA.location.min.x,	 node_->TranslationPVA.location.min.y,	 node_->TranslationPVA.location.min.z,
		 node_->TranslationPVA.location.max.x,	 node_->TranslationPVA.location.max.y,	 node_->TranslationPVA.location.max.z,
		 node_->TranslationPVA.RefEqP.Min,		   node_->TranslationPVA.RefEqP.Max,

		 node_->TranslationPVA.velocity.min.x,	 node_->TranslationPVA.velocity.min.y,	 node_->TranslationPVA.velocity.min.z,
		 node_->TranslationPVA.velocity.max.x,	 node_->TranslationPVA.velocity.max.y,	 node_->TranslationPVA.velocity.max.z,
		 node_->TranslationPVA.RefEqV.Min,		   node_->TranslationPVA.RefEqV.Max,

		 node_->TranslationPVA.acceleration.min.x, node_->TranslationPVA.acceleration.min.y, node_->TranslationPVA.acceleration.min.z,
		 node_->TranslationPVA.acceleration.max.x, node_->TranslationPVA.acceleration.max.y, node_->TranslationPVA.acceleration.max.z,
		node_->TranslationPVA.RefEqA.Min,  node_->TranslationPVA.RefEqA.Max}};
	return arr;
}
void EffekseerNodeCore::setTranslationPVA(float values[])
{
	int i = 0;
	node_->TranslationPVA.location.min.x = values[i++];
	node_->TranslationPVA.location.min.y = values[i++];
	node_->TranslationPVA.location.min.z = values[i++];
	node_->TranslationPVA.location.max.x = values[i++];
	node_->TranslationPVA.location.max.y = values[i++];
	node_->TranslationPVA.location.max.z = values[i++];
	node_->TranslationPVA.RefEqP.Min = values[i++];
	node_->TranslationPVA.RefEqP.Max = values[i++];

	node_->TranslationPVA.velocity.min.x = values[i++];
	node_->TranslationPVA.velocity.min.y = values[i++];
	node_->TranslationPVA.velocity.min.z = values[i++];
	node_->TranslationPVA.velocity.max.x = values[i++];
	node_->TranslationPVA.velocity.max.y = values[i++];
	node_->TranslationPVA.velocity.max.z = values[i++];
	node_->TranslationPVA.RefEqV.Min = values[i++];
	node_->TranslationPVA.RefEqV.Max = values[i++];

	node_->TranslationPVA.acceleration.min.x = values[i++];
	node_->TranslationPVA.acceleration.min.y = values[i++];
	node_->TranslationPVA.acceleration.min.z = values[i++];
	node_->TranslationPVA.acceleration.max.x = values[i++];
	node_->TranslationPVA.acceleration.max.y = values[i++];
	node_->TranslationPVA.acceleration.max.z = values[i++];
	node_->TranslationPVA.RefEqA.Min = values[i++];
	node_->TranslationPVA.RefEqA.Max = values[i++];
}

FloatArray EffekseerNodeCore::getTranslationEasing()
{
	// 27 values
	// float values[] {}
	FloatArray arr = {{
		node_->TranslationEasing.start.min.x,		  node_->TranslationEasing.start.min.y,		node_->TranslationEasing.start.min.z,
		node_->TranslationEasing.start.max.x,		  node_->TranslationEasing.start.max.y,		node_->TranslationEasing.start.max.z,
		node_->TranslationEasing.RefEqS.Min,		  node_->TranslationEasing.RefEqS.Max,

		node_->TranslationEasing.middle.min.x,		  node_->TranslationEasing.middle.min.y,	node_->TranslationEasing.middle.min.z,
		node_->TranslationEasing.middle.max.x,		  node_->TranslationEasing.middle.max.y,	node_->TranslationEasing.middle.max.z,
		node_->TranslationEasing.RefEqM.Min,		  node_->TranslationEasing.RefEqM.Max,

		node_->TranslationEasing.end.min.x,			  node_->TranslationEasing.end.min.y,		node_->TranslationEasing.end.min.z,
		node_->TranslationEasing.end.max.x,			  node_->TranslationEasing.end.max.y,		node_->TranslationEasing.end.max.z,
		node_->TranslationEasing.RefEqE.Min,		  node_->TranslationEasing.RefEqE.Max,

		node_->TranslationEasing.isIndividualEnabled?1:0, node_->TranslationEasing.isMiddleEnabled?1:0, //(float)node_->TranslationEasing.type_,

		// type
		// ease in, out
		//
	}};
	return arr;
}
void EffekseerNodeCore::setTranslationEasing(float values[])
{
	int i = 0;
	node_->TranslationEasing.start.min.x = values[i++];
	node_->TranslationEasing.start.min.y = values[i++];
	node_->TranslationEasing.start.min.z = values[i++];
	node_->TranslationEasing.start.max.x = values[i++];
	node_->TranslationEasing.start.max.y = values[i++];
	node_->TranslationEasing.start.max.z = values[i++];
	node_->TranslationEasing.RefEqS.Min = values[i++];
	node_->TranslationEasing.RefEqS.Max = values[i++];

	node_->TranslationEasing.middle.min.x = values[i++];
	node_->TranslationEasing.middle.min.y = values[i++];
	node_->TranslationEasing.middle.min.z = values[i++];
	node_->TranslationEasing.middle.max.x = values[i++];
	node_->TranslationEasing.middle.max.y = values[i++];
	node_->TranslationEasing.middle.max.z = values[i++];
	node_->TranslationEasing.RefEqM.Min = values[i++];
	node_->TranslationEasing.RefEqM.Max = values[i++];

	node_->TranslationEasing.end.min.x = values[i++];
	node_->TranslationEasing.end.min.y = values[i++];
	node_->TranslationEasing.end.min.z = values[i++];
	node_->TranslationEasing.end.max.x = values[i++];
	node_->TranslationEasing.end.max.y = values[i++];
	node_->TranslationEasing.end.max.z = values[i++];
	node_->TranslationEasing.RefEqE.Min = values[i++];
	node_->TranslationEasing.RefEqE.Max = values[i++];

	node_->TranslationEasing.isIndividualEnabled = values[i++];
	node_->TranslationEasing.isMiddleEnabled = values[i++];
	//node_->TranslationEasing.type_ = (Effekseer::Easing3Type)(int32_t)values[i++];
}
#pragma endregion

// translation pva
// translation easing
// translation curve

// rotation
// rotation fixed
// rotation pva
// rotation easing
// rotation curve

// scale
// scale fixed
// scale pva
// scale easing
// scale curve

/*
basic settings :
	visibility
	name
	spawn count / infinite

	inherit position / rotation / scale
	destroy after time / parent / when no

	time to live
	spawn rate
	initial delay
*/

/*
spawning method :
	set angle on spawn
	point / line / circle / sphere / model
	spawn location mean/dev (x,y,z)
*/

/*
position / rotation / scale :
	x/y/z
	PVA
	easing
	f-curve
*/

/*
force fields
*/

/*
basic render settings :
	material default / lighting / distortion / file
	filter, wrap
	blend, depth set, depth test
	fade in, out
	UV
	inherit color
	custom data 1
	custom data 2
*/

/*
render settings :
	sprite / ribbnon / track / ring / model
	order of spawn / reversed
	configuration billboard / rotated / fixed y / fixed
	color all : fixed / random / easing / fcurve
	vertex color
	vertex coords
*/