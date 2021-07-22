#pragma once

#include "systems/IParticleSystem.hxx"
#include "systems/BasicParticleSystem.hxx"
#include "systems/ManualParticleSystem.hxx"
#include "systems/AutomaticParticleSystem.hxx"
#include "systems/ThreadParticleSystem.hxx"

#include "particles/BasicParticle.hxx"


#include "policies/None.hxx"
#include "policies/emit/EmitPoint.hxx"
#include "policies/emit/EmitRect.hxx"
#include "policies/emit/EmitCircle.hxx"
#include "policies/emit/EmitPolar.hxx"
#include "policies/color/ColorConstant.hxx"
#include "policies/color/ColorLinear.hxx"
#include "policies/movement/MovementLinear.hxx"
#include "policies/movement/MovementDampening.hxx"
#include "policies/movement/MovementAcceleration.hxx"
#include "policies/movement/MovementFloating.hxx"
#include "policies/rotate/RotationConstant.hxx"
#include "policies/scale/ScaleConstant.hxx"
#include "policies/scale/ScaleLinear.hxx"
#include "policies/scale/ScaleParabola.hxx"
#include "policies/render/RenderColor.hxx"
#include "policies/render/RenderTexture.hxx"



