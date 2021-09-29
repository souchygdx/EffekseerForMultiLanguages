#include "EffekseerNodeCore.h"
#include "EffekseerBackendCore.h"
#include "EffekseerEffectCore.h"
#include "EffekseerManagerCore.h"
//#include <EffekseerRendererGL.h>
#include "data/data.h"
#include "data/enums.h"

#include "Effekseer/Effekseer.EffectImplemented.h"
#include "Effekseer/Effekseer.EffectNode.h"
#include "Effekseer/Effekseer.EffectNodeModel.h"
#include "Effekseer/Effekseer.Vector2D.h"
#include <Effekseer.h>
#include <assert.h>

// ctor
EffekseerNodeCore::EffekseerNodeCore(Effekseer::EffectNode* node_) { this->node_ = (Effekseer::EffectNodeImplemented*)node_; }
// ctor
EffekseerNodeCore::EffekseerNodeCore(Effekseer::EffectNodeImplemented* node_) { this->node_ = node_; }
// dtor
EffekseerNodeCore::~EffekseerNodeCore() {}

// children
EffekseerNodeCore* EffekseerNodeCore::getChild(int index) { return new EffekseerNodeCore(node_->GetChild(index)); }
int EffekseerNodeCore::getChildCount() { return node_->GetChildrenCount(); }

void EffekseerNodeCore::setVisibility(bool visible) { node_->IsRendered = visible; }

void EffekseerNodeCore::setParameterCommonValues(float t[])
{
	int i = 0;
	node_->CommonValues.MaxGeneration = t[i++];
	node_->CommonValues.TranslationBindType = (Effekseer::TranslationParentBindType) (int) t[i++];
	node_->CommonValues.RotationBindType = (Effekseer::BindType) (int) t[i++];
	node_->CommonValues.ScalingBindType = (Effekseer::BindType) (int) t[i++];
	node_->CommonValues.RemoveWhenLifeIsExtinct = t[i++];
	node_->CommonValues.RemoveWhenParentIsRemoved = t[i++];
	node_->CommonValues.RemoveWhenChildrenIsExtinct = t[i++];
	node_->CommonValues.life.min = t[i++];
	node_->CommonValues.life.max = t[i++];
	node_->CommonValues.GenerationTime.min = t[i++];
	node_->CommonValues.GenerationTime.max = t[i++];
	node_->CommonValues.GenerationTimeOffset.min = t[i++];
	node_->CommonValues.GenerationTimeOffset.max = t[i++];
}

#pragma region generation
void EffekseerNodeCore::setGeneration(float t[])
{
	int i = 0;
	int generationType = t[i++];
	int angleOnSpawn = (int) t[i++];
	node_->GenerationLocation.EffectsRotation = angleOnSpawn;
	switch (generationType)
	{
	case Effekseer::ParameterGenerationLocation::TYPE_POINT:
		setGenerationPoint(t);
		break;
	case Effekseer::ParameterGenerationLocation::TYPE_LINE:
		setGenerationLine(t);
		break;
	case Effekseer::ParameterGenerationLocation::TYPE_CIRCLE:
		setGenerationCircle(t);
		break;
	case Effekseer::ParameterGenerationLocation::TYPE_SPHERE:
		setGenerationSphere(t);
		break;
	case Effekseer::ParameterGenerationLocation::TYPE_MODEL:
		setGenerationModel(t);
		break;
	}
}

void EffekseerNodeCore::setGenerationPoint(float t[])
{
	int i = 2; // already read generationType and angleOnSpawn
	node_->GenerationLocation.type = Effekseer::ParameterGenerationLocation::TYPE_POINT;
	node_->GenerationLocation.point.location.min.x = t[i++];
	node_->GenerationLocation.point.location.min.y = t[i++];
	node_->GenerationLocation.point.location.min.z = t[i++];
	node_->GenerationLocation.point.location.max.x = t[i++];
	node_->GenerationLocation.point.location.max.y = t[i++];
	node_->GenerationLocation.point.location.max.z = t[i++];
}
void EffekseerNodeCore::setGenerationLine(float t[])
{
	int i = 2; // already read generationType and angleOnSpawn
	node_->GenerationLocation.type = Effekseer::ParameterGenerationLocation::TYPE_LINE;

	node_->GenerationLocation.line.division = t[i++];
	node_->GenerationLocation.line.type = (Effekseer::ParameterGenerationLocation::LineType) (int) t[i++];

	node_->GenerationLocation.line.position_start.min.x = t[i++];
	node_->GenerationLocation.line.position_start.min.y = t[i++];
	node_->GenerationLocation.line.position_start.min.z = t[i++];
	node_->GenerationLocation.line.position_start.max.x = t[i++];
	node_->GenerationLocation.line.position_start.max.y = t[i++];
	node_->GenerationLocation.line.position_start.max.z = t[i++];

	node_->GenerationLocation.line.position_end.min.x = t[i++];
	node_->GenerationLocation.line.position_end.min.y = t[i++];
	node_->GenerationLocation.line.position_end.min.z = t[i++];
	node_->GenerationLocation.line.position_end.max.x = t[i++];
	node_->GenerationLocation.line.position_end.max.y = t[i++];
	node_->GenerationLocation.line.position_end.max.z = t[i++];

	node_->GenerationLocation.line.position_noize.min = t[i++];
	node_->GenerationLocation.line.position_noize.max = t[i++];
}
void EffekseerNodeCore::setGenerationCircle(float t[])
{
	int i = 2; // already read generationType and angleOnSpawn
	node_->GenerationLocation.type = Effekseer::ParameterGenerationLocation::TYPE_CIRCLE;

	node_->GenerationLocation.circle.division = t[i++];
	node_->GenerationLocation.circle.type = (Effekseer::ParameterGenerationLocation::eCircleType)(int) t[i++];
	node_->GenerationLocation.circle.axisDirection = (Effekseer::ParameterGenerationLocation::AxisType)(int) t[i++];

	node_->GenerationLocation.circle.radius.min = t[i++];
	node_->GenerationLocation.circle.radius.max = t[i++];

	node_->GenerationLocation.circle.angle_start.min = t[i++];
	node_->GenerationLocation.circle.angle_start.max = t[i++];

	node_->GenerationLocation.circle.angle_end.min = t[i++];
	node_->GenerationLocation.circle.angle_end.max = t[i++];

	node_->GenerationLocation.circle.angle_noize.min = t[i++];
	node_->GenerationLocation.circle.angle_noize.max = t[i++];
}
void EffekseerNodeCore::setGenerationSphere(float t[])
{
	int i = 2; // already read generationType and angleOnSpawn
	node_->GenerationLocation.type = Effekseer::ParameterGenerationLocation::TYPE_SPHERE;
	node_->GenerationLocation.sphere.radius.min = t[i++];
	node_->GenerationLocation.sphere.radius.max = t[i++];
	node_->GenerationLocation.sphere.rotation_x.min = t[i++];
	node_->GenerationLocation.sphere.rotation_x.max = t[i++];
	node_->GenerationLocation.sphere.rotation_y.min = t[i++];
	node_->GenerationLocation.sphere.rotation_y.max = t[i++];
}

void EffekseerNodeCore::setGenerationModel(float t[])
{
	int i = 0;
	int generationType = t[i++];
	node_->GenerationLocation.type = Effekseer::ParameterGenerationLocation::TYPE_MODEL;
	int spawnMethod = t[i++];
	// rest of it would be the path to the model or something
}
#pragma endregion

#pragma region translation
int EffekseerNodeCore::getTranslationType() { return static_cast<int>(node_->TranslationType); }
void EffekseerNodeCore::setTranslationType(int type)
{
	if (node_ == nullptr)
		return;
	try
	{
		node_->TranslationType = static_cast<Effekseer::ParameterTranslationType>(type);
	}
	catch (...)
	{
	}
}

// void EffekseerNodeCore::setTranslationTypeEasing()
//{
//	if (node_ == nullptr) return;
//	node_->TranslationType = Effekseer::ParameterTranslationType_Easing;
//}
// void EffekseerNodeCore::setTranslationTypeFCurve()
//{
//	if (node_ == nullptr) return;
//	node_->TranslationType = Effekseer::ParameterTranslationType_FCurve;
//}

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
		 node_->TranslationPVA.RefEqA.Min,		   node_->TranslationPVA.RefEqA.Max}};
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
		node_->TranslationEasing.start.min.x,
		node_->TranslationEasing.start.min.y,
		node_->TranslationEasing.start.min.z,
		node_->TranslationEasing.start.max.x,
		node_->TranslationEasing.start.max.y,
		node_->TranslationEasing.start.max.z,
		node_->TranslationEasing.RefEqS.Min,
		node_->TranslationEasing.RefEqS.Max,

		node_->TranslationEasing.middle.min.x,
		node_->TranslationEasing.middle.min.y,
		node_->TranslationEasing.middle.min.z,
		node_->TranslationEasing.middle.max.x,
		node_->TranslationEasing.middle.max.y,
		node_->TranslationEasing.middle.max.z,
		node_->TranslationEasing.RefEqM.Min,
		node_->TranslationEasing.RefEqM.Max,

		node_->TranslationEasing.end.min.x,
		node_->TranslationEasing.end.min.y,
		node_->TranslationEasing.end.min.z,
		node_->TranslationEasing.end.max.x,
		node_->TranslationEasing.end.max.y,
		node_->TranslationEasing.end.max.z,
		node_->TranslationEasing.RefEqE.Min,
		node_->TranslationEasing.RefEqE.Max,

		node_->TranslationEasing.isIndividualEnabled ? 1 : 0,
		node_->TranslationEasing.isMiddleEnabled ? 1 : 0, //(float)node_->TranslationEasing.type_,

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
	// node_->TranslationEasing.type_ = (Effekseer::Easing3Type)(int32_t)values[i++];
}
#pragma endregion

#pragma region rotation

int EffekseerNodeCore::getRotationType() { return static_cast<int>(node_->RotationType); }
void EffekseerNodeCore::setRotationType(int type)
{
	if (node_ == nullptr)
		return;
	try
	{
		node_->RotationType = static_cast<Effekseer::ParameterRotationType>(type);
	}
	catch (...)
	{
	}
}
void EffekseerNodeCore::setRotationFixed(float values[])
{
	int i = 0;
	node_->RotationFixed.Position.X = values[i++];
	node_->RotationFixed.Position.Y = values[i++];
	node_->RotationFixed.Position.Z = values[i++];
	node_->RotationFixed.RefEq = values[i++];
}
void EffekseerNodeCore::setRotationPVA(float values[])
{
	int i = 0;
	node_->RotationPVA.rotation.min.x = values[i++];
	node_->RotationPVA.rotation.min.y = values[i++];
	node_->RotationPVA.rotation.min.z = values[i++];
	node_->RotationPVA.rotation.max.x = values[i++];
	node_->RotationPVA.rotation.max.y = values[i++];
	node_->RotationPVA.rotation.max.z = values[i++];
	node_->RotationPVA.RefEqP.Min = values[i++];
	node_->RotationPVA.RefEqP.Max = values[i++];

	node_->RotationPVA.velocity.min.x = values[i++];
	node_->RotationPVA.velocity.min.y = values[i++];
	node_->RotationPVA.velocity.min.z = values[i++];
	node_->RotationPVA.velocity.max.x = values[i++];
	node_->RotationPVA.velocity.max.y = values[i++];
	node_->RotationPVA.velocity.max.z = values[i++];
	node_->RotationPVA.RefEqV.Min = values[i++];
	node_->RotationPVA.RefEqV.Max = values[i++];

	node_->RotationPVA.acceleration.min.x = values[i++];
	node_->RotationPVA.acceleration.min.y = values[i++];
	node_->RotationPVA.acceleration.min.z = values[i++];
	node_->RotationPVA.acceleration.max.x = values[i++];
	node_->RotationPVA.acceleration.max.y = values[i++];
	node_->RotationPVA.acceleration.max.z = values[i++];
	node_->RotationPVA.RefEqA.Min = values[i++];
	node_->RotationPVA.RefEqA.Max = values[i++];
}
void EffekseerNodeCore::setRotationEasing(float values[])
{
	int i = 0;
	node_->RotationEasing.start.min.x = values[i++];
	node_->RotationEasing.start.min.y = values[i++];
	node_->RotationEasing.start.min.z = values[i++];
	node_->RotationEasing.start.max.x = values[i++];
	node_->RotationEasing.start.max.y = values[i++];
	node_->RotationEasing.start.max.z = values[i++];
	node_->RotationEasing.RefEqS.Min = values[i++];
	node_->RotationEasing.RefEqS.Max = values[i++];

	node_->RotationEasing.middle.min.x = values[i++];
	node_->RotationEasing.middle.min.y = values[i++];
	node_->RotationEasing.middle.min.z = values[i++];
	node_->RotationEasing.middle.max.x = values[i++];
	node_->RotationEasing.middle.max.y = values[i++];
	node_->RotationEasing.middle.max.z = values[i++];
	node_->RotationEasing.RefEqM.Min = values[i++];
	node_->RotationEasing.RefEqM.Max = values[i++];

	node_->RotationEasing.end.min.x = values[i++];
	node_->RotationEasing.end.min.y = values[i++];
	node_->RotationEasing.end.min.z = values[i++];
	node_->RotationEasing.end.max.x = values[i++];
	node_->RotationEasing.end.max.y = values[i++];
	node_->RotationEasing.end.max.z = values[i++];
	node_->RotationEasing.RefEqE.Min = values[i++];
	node_->RotationEasing.RefEqE.Max = values[i++];

	node_->RotationEasing.isIndividualEnabled = values[i++];
	node_->RotationEasing.isMiddleEnabled = values[i++];
	// node_->RotationEasing.type_ = (Effekseer::Easing3Type)(int32_t)values[i++];
}
#pragma endregion

#pragma region scaling

int EffekseerNodeCore::getScalingType() { return static_cast<int>(node_->ScalingType); }
void EffekseerNodeCore::setScalingType(int type)
{
	if (node_ == nullptr)
		return;
	node_->ScalingType = static_cast<Effekseer::ParameterScalingType>(type);
}
void EffekseerNodeCore::setScalingFixed(float values[])
{
	int i = 0;
	node_->ScalingFixed.Position.X = values[i++];
	node_->ScalingFixed.Position.Y = values[i++];
	node_->ScalingFixed.Position.Z = values[i++];
	node_->ScalingFixed.RefEq = values[i++];
}
void EffekseerNodeCore::setScalingPVA(float values[])
{
	int i = 0;
	node_->ScalingPVA.Position.min.x = values[i++];
	node_->ScalingPVA.Position.min.y = values[i++];
	node_->ScalingPVA.Position.min.z = values[i++];
	node_->ScalingPVA.Position.max.x = values[i++];
	node_->ScalingPVA.Position.max.y = values[i++];
	node_->ScalingPVA.Position.max.z = values[i++];
	node_->ScalingPVA.RefEqP.Min = values[i++];
	node_->ScalingPVA.RefEqP.Max = values[i++];

	node_->ScalingPVA.Velocity.min.x = values[i++];
	node_->ScalingPVA.Velocity.min.y = values[i++];
	node_->ScalingPVA.Velocity.min.z = values[i++];
	node_->ScalingPVA.Velocity.max.x = values[i++];
	node_->ScalingPVA.Velocity.max.y = values[i++];
	node_->ScalingPVA.Velocity.max.z = values[i++];
	node_->ScalingPVA.RefEqV.Min = values[i++];
	node_->ScalingPVA.RefEqV.Max = values[i++];

	node_->ScalingPVA.Acceleration.min.x = values[i++];
	node_->ScalingPVA.Acceleration.min.y = values[i++];
	node_->ScalingPVA.Acceleration.min.z = values[i++];
	node_->ScalingPVA.Acceleration.max.x = values[i++];
	node_->ScalingPVA.Acceleration.max.y = values[i++];
	node_->ScalingPVA.Acceleration.max.z = values[i++];
	node_->ScalingPVA.RefEqA.Min = values[i++];
	node_->ScalingPVA.RefEqA.Max = values[i++];
}
void EffekseerNodeCore::setScalingEasing(float values[])
{
	int i = 0;
	node_->ScalingEasing.start.min.x = values[i++];
	node_->ScalingEasing.start.min.y = values[i++];
	node_->ScalingEasing.start.min.z = values[i++];
	node_->ScalingEasing.start.max.x = values[i++];
	node_->ScalingEasing.start.max.y = values[i++];
	node_->ScalingEasing.start.max.z = values[i++];
	node_->ScalingEasing.RefEqS.Min = values[i++];
	node_->ScalingEasing.RefEqS.Max = values[i++];

	node_->ScalingEasing.middle.min.x = values[i++];
	node_->ScalingEasing.middle.min.y = values[i++];
	node_->ScalingEasing.middle.min.z = values[i++];
	node_->ScalingEasing.middle.max.x = values[i++];
	node_->ScalingEasing.middle.max.y = values[i++];
	node_->ScalingEasing.middle.max.z = values[i++];
	node_->ScalingEasing.RefEqM.Min = values[i++];
	node_->ScalingEasing.RefEqM.Max = values[i++];

	node_->ScalingEasing.end.min.x = values[i++];
	node_->ScalingEasing.end.min.y = values[i++];
	node_->ScalingEasing.end.min.z = values[i++];
	node_->ScalingEasing.end.max.x = values[i++];
	node_->ScalingEasing.end.max.y = values[i++];
	node_->ScalingEasing.end.max.z = values[i++];
	node_->ScalingEasing.RefEqE.Min = values[i++];
	node_->ScalingEasing.RefEqE.Max = values[i++];

	node_->ScalingEasing.isIndividualEnabled = values[i++];
	node_->ScalingEasing.isMiddleEnabled = values[i++];
	// node_->ScalingEasing.type_ = (Effekseer::Easing3Type)(int32_t)values[i++];
}
#pragma endregion

#pragma region basic render settings

void EffekseerNodeCore::setBasicRenderSettings(float t[]) {
	int i = 0;
	// material
	auto matType = (Effekseer::RendererMaterialType) (int) t[i++];
	node_->RendererCommon.MaterialType = matType;
	switch (matType)
	{
		case Effekseer::RendererMaterialType::Default: 
			setBasicRenderSettingsMaterialDefault(t);
			i += 3;
			break;
		case Effekseer::RendererMaterialType::BackDistortion: 
			setBasicRenderSettingsMaterialDistortion(t);
			i += 3;
			break;
		case Effekseer::RendererMaterialType::Lighting: 
			setBasicRenderSettingsMaterialLighting(t);
			i += 5;
			break;
		case Effekseer::RendererMaterialType::File: 
			setBasicRenderSettingsMaterialFile(t);
			i += 0;
			break;
	}
	// 
	node_->RendererCommon.AlphaBlend = (Effekseer::AlphaBlendType) (int) t[i++];
	node_->RendererCommon.ZWrite = t[i++] == 1;
	node_->RendererCommon.ZTest = t[i++] == 1;
	// fade in
	switch ((int)t[i++])
	{
	case 0:
		node_->RendererCommon.FadeInType = node_->RendererCommon.FADEIN_OFF;
		break;
	case 1:
		node_->RendererCommon.FadeInType = node_->RendererCommon.FADEIN_ON;
		break;
	}
	node_->RendererCommon.FadeIn.Frame = t[i++];
	node_->RendererCommon.FadeIn.Value.easingA = t[i++];
	node_->RendererCommon.FadeIn.Value.easingB = t[i++];
	node_->RendererCommon.FadeIn.Value.easingC = t[i++];
	// fade out
	switch ((int)t[i++])
	{
	case 0:
		node_->RendererCommon.FadeOutType = node_->RendererCommon.FADEOUT_OFF;
		break;
	case 1:
		node_->RendererCommon.FadeOutType = node_->RendererCommon.FADEOUT_ON;
		break;
	} 
	node_->RendererCommon.FadeOut.Frame = t[i++];
	node_->RendererCommon.FadeOut.Value.easingA = t[i++];
	node_->RendererCommon.FadeOut.Value.easingB = t[i++];
	node_->RendererCommon.FadeOut.Value.easingC = t[i++];
	// uv
	switch ((int) t[i++])
	{
	case 0:
		node_->RendererCommon.UVTypes[0] = node_->RendererCommon.UV_DEFAULT;
		break;
	case 1:
		node_->RendererCommon.UVTypes[0] = node_->RendererCommon.UV_FIXED;
		break;
	case 2:
		node_->RendererCommon.UVTypes[0] = node_->RendererCommon.UV_ANIMATION;
		break;
	case 3:
		node_->RendererCommon.UVTypes[0] = node_->RendererCommon.UV_SCROLL;
		break;
	case 4:
		node_->RendererCommon.UVTypes[0] = node_->RendererCommon.UV_FCURVE;
		break;
	}
	// color
	node_->RendererCommon.ColorBindType = (Effekseer::BindType) (int) t[i++];
}

void EffekseerNodeCore::setBasicRenderSettingsMaterialDefault(float t[]) { 
	int i = 0;
	int matType = t[i++];
	node_->RendererCommon.EmissiveScaling = t[i++];
	node_->RendererCommon.FilterTypes[0] = (Effekseer::TextureFilterType) (int) t[i++];
	node_->RendererCommon.WrapTypes[0] = (Effekseer::TextureWrapType) (int) t[i++];
}
void EffekseerNodeCore::setBasicRenderSettingsMaterialDistortion(float t[]) { 
	int i = 0; 
	int matType = t[i++];
	node_->RendererCommon.FilterTypes[0] = (Effekseer::TextureFilterType) (int) t[i++];
	node_->RendererCommon.WrapTypes[0] = (Effekseer::TextureWrapType) (int) t[i++];
	node_->RendererCommon.DistortionIntensity = t[i++];
}

void EffekseerNodeCore::setBasicRenderSettingsMaterialLighting(float t[]) {
	int i = 0;
	int matType = t[i++];
	node_->RendererCommon.EmissiveScaling = t[i++];
	node_->RendererCommon.FilterTypes[0] = (Effekseer::TextureFilterType) (int) t[i++];
	node_->RendererCommon.WrapTypes[0] = (Effekseer::TextureWrapType) (int) t[i++];
	node_->RendererCommon.FilterTypes[1] = (Effekseer::TextureFilterType) (int) t[i++];
	node_->RendererCommon.WrapTypes[1] = (Effekseer::TextureWrapType) (int) t[i++];
}
void EffekseerNodeCore::setBasicRenderSettingsMaterialFile(float t[]) {
	int i = 0;
	int matType = t[i++];
	// ???
}

#pragma endregion

#pragma region render settings

void EffekseerNodeCore::setRenderSettings(float t[]) {
	auto model = (Effekseer::EffectNodeModel*) node_;
	int i = 0;
}
void EffekseerNodeCore::setRenderSettingsNone(float t[]) {
	auto model = (Effekseer::EffectNodeModel*) node_;
	int i = 0;
}
void EffekseerNodeCore::setRenderSettingsSprite(float t[]) {
	auto model = (Effekseer::EffectNodeModel*) node_;
	int i = 0;
	node_->RenderingOrder; // enum order : [orderOfSpawn, reversed]
	model->Billboard; // enum billboardConfig : [billboard, rotatedBillboard, fixedYAxis, fixed]
	model->AllColor; // colorall : [fixed {v4}, random { v4 min, v4 max }, easing { v4 startMin, v4 startMax, v4 endMin, v4 endMax }, fcurve {}]
	// enum vertex color : [default / fixed { 4 x vector4 int }]
	// enum vertex coords : [default / fixed { 4 x vector2 float }]
}
void EffekseerNodeCore::setRenderSettingsRibbon(float t[]) {
	auto model = (Effekseer::EffectNodeModel*) node_;
	int i = 0;
	// enum uv type : [stretch / tile { int numberOfTileOnHead, int numberOfTileOnTail, vector2int loopingArea }]
	// boolean followViewpoint
	model->AllColor;
	// enum vertex color : [default / fixed { 4 x vector4 int }]
	// enum position : [default / fixed { float leftCoord, float rightCoord }]
	// int numberOfSplineDivision
}
void EffekseerNodeCore::setRenderSettingsTrack(float t[]) {
	auto model = (Effekseer::EffectNodeModel*) node_;
	int i = 0;
	// enum uv type : [stretch / tile { int numberOfTileOnHead, int numberOfTileOnTail, vector2int loopingArea }]
	// enum front size : [fixed] + float value
	// enum mid   size : [fixed] + float value
	// enum back  size : [fixed] + float value
	// int numberOfSplineDivision
	// enum colorLeft : [fixed {v4}, random { v4 min, v4 max }, easing { v4 startMin, v4 startMax, v4 endMin, v4 endMax }, fcurve {}]
	// enum colorLeftCenter : [fixed {v4}, random { v4 min, v4 max }, easing { v4 startMin, v4 startMax, v4 endMin, v4 endMax }, fcurve {}]
	// enum colorCenter : [fixed {v4}, random { v4 min, v4 max }, easing { v4 startMin, v4 startMax, v4 endMin, v4 endMax }, fcurve {}]
	// enum colorCenterMid : [fixed {v4}, random { v4 min, v4 max }, easing { v4 startMin, v4 startMax, v4 endMin, v4 endMax }, fcurve {}]
	// enum colorRight : [fixed {v4}, random { v4 min, v4 max }, easing { v4 startMin, v4 startMax, v4 endMin, v4 endMax }, fcurve {}]
	// enum colorRightCenter : [fixed {v4}, random { v4 min, v4 max }, easing { v4 startMin, v4 startMax, v4 endMin, v4 endMax }, fcurve {}]
}
void EffekseerNodeCore::setRenderSettingsRing(float t[]) {
	auto model = (Effekseer::EffectNodeModel*) node_;
	int i = 0;
	// enum shape : [donut, crescent]
	node_->RenderingOrder; // enum order : [orderOfSpawn, reversed]
	model->Billboard; // enum billboardConfig : [billboard, rotatedBillboard, fixedYAxis, fixed]
	// int vertexCount
	// enum positionOuter : [fixed{}, pva{}, easing{}]
	// enum positionInner :  [fixed{}, pva{}, easing{}]
	// enum ratioCenter : [fixed {float}, random { float2 }, easing { float startMin/Max, float endMinMax, enum type { enum easeIn, enum easeOut }, bool isMidEnabled, bool isRandGroupEnabled, bool isTypeIndividual }]
	// enum colorOuter : [fixed {v4}, random { v4 min, v4 max }, easing { v4 startMin, v4 startMax, v4 endMin, v4 endMax }, fcurve {}]
	// enum colorCenter : [fixed {v4}, random { v4 min, v4 max }, easing { v4 startMin, v4 startMax, v4 endMin, v4 endMax }, fcurve {}]
	// enum colorInner : [fixed {v4}, random { v4 min, v4 max }, easing { v4 startMin, v4 startMax, v4 endMin, v4 endMax }, fcurve {}]
}
void EffekseerNodeCore::setRenderSettingsModel(float t[]) {
	auto model = (Effekseer::EffectNodeModel*) node_;
	int i = 0;
	// enum type : [file, procedural]
	// model : <load>
	model->Billboard; // enum billboardConfig : [billboard, rotatedBillboard, fixedYAxis, fixed]
	model->Culling; // enum culling : [front, back, double]
	model->AllColor; // color : [fixed {v4}, random { v4 min, v4 max }, easing { v4 startMin, v4 startMax, v4 endMin, v4 endMax }, fcurve {}]
}

void EffekseerNodeCore::setRenderSettings_ColorAll(float t[]) {
	auto model = (Effekseer::EffectNodeModel*) node_;
	int i = 0;
	int type = t[i++];
	switch (type) {
		case 0:
			model->AllColor.type = model->AllColor.Fixed;
			model->AllColor.fixed.all.R = t[i++];
			model->AllColor.fixed.all.G = t[i++];
			model->AllColor.fixed.all.B = t[i++];
			model->AllColor.fixed.all.A = t[i++];
			break;// Fixed = 0,
		case 1:
			model->AllColor.type = model->AllColor.Random;
			model->AllColor.random.all.mode = (Effekseer::ColorMode) (int) t[i++];
			model->AllColor.random.all.min.R = t[i++];
			model->AllColor.random.all.min.G = t[i++];
			model->AllColor.random.all.min.B = t[i++];
			model->AllColor.random.all.min.A = t[i++];
			model->AllColor.random.all.max.R = t[i++];
			model->AllColor.random.all.max.G = t[i++];
			model->AllColor.random.all.max.B = t[i++];
			model->AllColor.random.all.max.A = t[i++];
			break; //Random = 1,
		case 2: 
			model->AllColor.type = model->AllColor.Easing;
			model->AllColor.easing.all.start.mode = (Effekseer::ColorMode) (int) t[i++];
			model->AllColor.easing.all.start.min.R = t[i++];
			model->AllColor.easing.all.start.min.G = t[i++];
			model->AllColor.easing.all.start.min.B = t[i++];
			model->AllColor.easing.all.start.min.A = t[i++];
			model->AllColor.easing.all.start.max.R = t[i++];
			model->AllColor.easing.all.start.max.G = t[i++];
			model->AllColor.easing.all.start.max.B = t[i++];
			model->AllColor.easing.all.start.max.A = t[i++];
			
			model->AllColor.easing.all.end.mode = (Effekseer::ColorMode) (int) t[i++];
			model->AllColor.easing.all.end.min.R = t[i++];
			model->AllColor.easing.all.end.min.G = t[i++];
			model->AllColor.easing.all.end.min.B = t[i++];
			model->AllColor.easing.all.end.min.A = t[i++];
			model->AllColor.easing.all.end.max.R = t[i++];
			model->AllColor.easing.all.end.max.G = t[i++];
			model->AllColor.easing.all.end.max.B = t[i++];
			model->AllColor.easing.all.end.max.A = t[i++];
			break; //Easing = 2,
		case 3:
			model->AllColor.type = model->AllColor.FCurve_RGBA;
			//model->AllColor.fcurve_rgba.FCurve->R;
			break; //FCurve_RGBA = 3,
	}
	// color : [fixed {v4}, random { v4 min, v4 max }, easing { v4 startMin, v4 startMax, v4 endMin, v4 endMax }, fcurve {}]
}

//void EffekseerNodeCore::setRenderSettings_ColorAllFixedTest()
//{
//	auto model = (Effekseer::EffectNodeModel*) node_;
//	model->AllColor.type = model->AllColor.Fixed;
//	model->AllColor.fixed.all.R = 255;
//	model->AllColor.fixed.all.G = 255;
//	model->AllColor.fixed.all.B = 255;
//	model->AllColor.fixed.all.A = 255;
//}


#pragma endregion

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