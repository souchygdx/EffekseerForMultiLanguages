#include "EffekseerManagerCore.h"
#include "EffekseerBackendCore.h"
#include "EffekseerEffectCore.h"
#include <EffekseerRendererGL.h>
#include "EffekseerRenderer/GraphicsDevice.h"

EffekseerNodeCore::EffekseerNodeCore(Effekseer::EffectNode* node_) {
	this->node_ = node_;
}

EffekseerNodeCore::~EffekseerNodeCore() {}

EffekseerNodeCore* EffekseerNodeCore::GetChild(int index) { 
	return new EffekseerNodeCore(node_->GetChild(index)); 
}
