#pragma once

#include "EffekseerBackendCore.h"


class EffekseerNodeCore
{
	
private:
	Effekseer::EffectNode* node_ = nullptr;


public:
	EffekseerNodeCore(Effekseer::EffectNode* node_);
	~EffekseerNodeCore();
	
	EffekseerNodeCore* GetChild(int index);


};