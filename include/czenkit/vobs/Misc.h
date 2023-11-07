// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include "../Boxes.h"
#include "../Library.h"
#include "../Material.h"
#include "../Matrix.h"
#include "../Vector.h"

#ifdef __cplusplus
	#include <zenkit/vobs/Misc.hh>
using ZkAnimate = zenkit::vobs::Animate;
using ZkItem = zenkit::vobs::Item;
using ZkLensFlare = zenkit::vobs::LensFlare;
using ZkParticleEffectController = zenkit::vobs::ParticleEffectController;
using ZkMessageFilter = zenkit::vobs::MessageFilter;
using ZkCodeMaster = zenkit::vobs::CodeMaster;
using ZkMoverController = zenkit::vobs::MoverController;
using ZkTouchDamage = zenkit::vobs::TouchDamage;
using ZkEarthquake = zenkit::vobs::Earthquake;
#else
typedef struct ZkInternal_Animate ZkAnimate;
typedef struct ZkInternal_Item ZkItem;
typedef struct ZkInternal_LensFlare ZkLensFlare;
typedef struct ZkInternal_ParticleEffectController ZkParticleEffectController;
typedef struct ZkInternal_MessageFilter ZkMessageFilter;
typedef struct ZkInternal_CodeMaster ZkCodeMaster;
typedef struct ZkInternal_MoverController ZkMoverController;
typedef struct ZkInternal_TouchDamager ZkTouchDamage
typedef struct ZkInternal_Earthquake ZkEarthquake
#endif

typedef enum {
	ZkMessageFilterAction_NONE = 0,
	ZkMessageFilterAction_TRIGGER = 1,
	ZkMessageFilterAction_UNTRIGGER = 2,
	ZkMessageFilterAction_ENABLE = 3,
	ZkMessageFilterAction_DISABLE = 4,
	ZkMessageFilterAction_TOGGLE = 5,
} ZkMessageFilterAction;

typedef enum {
	ZkMoverMessageType_FIXED_DIRECT = 0,
	ZkMoverMessageType_FIXED_ORDER = 1,
	ZkMoverMessageType_NEXT = 2,
	ZkMoverMessageType_PREVIOUS = 3,
} ZkMoverMessageType;

typedef enum {
	ZkTouchCollisionType_NONE = 0,
	ZkTouchCollisionType_BOX = 1,
	ZkTouchCollisionType_POINT = 2,
} ZkTouchCollisionType;

CZK_API ZkAnimate* ZkAnimate_load(ZkRead* buf, ZkGameVersion version);
CZK_API ZkAnimate* ZkAnimate_loadPath(ZkString path, ZkGameVersion version);
CZK_API void ZkAnimate_del(ZkAnimate* slf);
CZK_API ZkBool ZkAnimate_getStartOn(ZkAnimate const* slf);

CZK_API ZkItem* ZkItem_load(ZkRead* buf, ZkGameVersion version);
CZK_API ZkItem* ZkItem_loadPath(ZkString path, ZkGameVersion version);
CZK_API void ZkItem_del(ZkItem* slf);
CZK_API ZkString ZkItem_getInstance(ZkItem const* slf);

CZK_API ZkLensFlare* ZkLensFlare_load(ZkRead* buf, ZkGameVersion version);
CZK_API ZkLensFlare* ZkLensFlare_loadPath(ZkString path, ZkGameVersion version);
CZK_API void ZkLensFlare_del(ZkLensFlare* slf);
CZK_API ZkString ZkLensFlare_getEffect(ZkLensFlare const* slf);

CZK_API ZkParticleEffectController* ZkParticleEffectController_load(ZkRead* buf, ZkGameVersion version);
CZK_API ZkParticleEffectController* ZkParticleEffectController_loadPath(ZkString path, ZkGameVersion version);
CZK_API void ZkParticleEffectController_del(ZkParticleEffectController* slf);
CZK_API ZkString ZkParticleEffectController_getEffectName(ZkParticleEffectController const* slf);
CZK_API ZkBool ZkParticleEffectController_getKillWhenDone(ZkParticleEffectController const* slf);
CZK_API ZkBool ZkParticleEffectController_getInitiallyRunning(ZkParticleEffectController const* slf);

CZK_API ZkMessageFilter* ZkMessageFilter_load(ZkRead* buf, ZkGameVersion version);
CZK_API ZkMessageFilter* ZkMessageFilter_loadPath(ZkString path, ZkGameVersion version);
CZK_API void ZkMessageFilter_del(ZkMessageFilter* slf);
CZK_API ZkString ZkMessageFilter_getTarget(ZkMessageFilter const* slf);
CZK_API ZkMessageFilterAction ZkMessageFilter_getOnTrigger(ZkMessageFilter const* slf);
CZK_API ZkMessageFilterAction ZkMessageFilter_getOnUntrigger(ZkMessageFilter const* slf);

CZK_API ZkCodeMaster* ZkCodeMaster_load(ZkRead* buf, ZkGameVersion version);
CZK_API ZkCodeMaster* ZkCodeMaster_loadPath(ZkString path, ZkGameVersion version);
CZK_API void ZkCodeMaster_del(ZkCodeMaster* slf);
CZK_API ZkString ZkCodeMaster_getTarget(ZkCodeMaster const* slf);
CZK_API ZkBool ZkCodeMaster_getOrdered(ZkCodeMaster const* slf);
CZK_API ZkBool ZkCodeMaster_getFirstFalseIsFailure(ZkCodeMaster const* slf);
CZK_API ZkString ZkCodeMaster_getFailureTarget(ZkCodeMaster const* slf);
CZK_API ZkBool ZkCodeMaster_getUntriggeredCancels(ZkCodeMaster const* slf);
CZK_API ZkSize ZkCodeMaster_getSlaveCount(ZkCodeMaster const* slf);
CZK_API ZkString ZkCodeMaster_getSlave(ZkCodeMaster const* slf, ZkSize i);
CZK_API void ZkCodeMaster_enumerateSlaves(ZkCodeMaster const* slf, ZkStringEnumerator cb, void* ctx);

CZK_API ZkMoverController* ZkMoverController_load(ZkRead* buf, ZkGameVersion version);
CZK_API ZkMoverController* ZkMoverController_loadPath(ZkString path, ZkGameVersion version);
CZK_API void ZkMoverController_del(ZkMoverController* slf);
CZK_API ZkString ZkMoverController_getTarget(ZkMoverController const* slf);
CZK_API ZkMoverMessageType ZkMoverController_getMessage(ZkMoverController const* slf);
CZK_API int32_t ZkMoverController_getKey(ZkMoverController const* slf);

CZK_API ZkTouchDamage* ZkTouchDamage_load(ZkRead* buf, ZkGameVersion version);
CZK_API ZkTouchDamage* ZkTouchDamage_loadPath(ZkString path, ZkGameVersion version);
CZK_API void ZkTouchDamage_del(ZkTouchDamage* slf);
CZK_API float ZkTouchDamage_getDamage(ZkTouchDamage const* slf);
CZK_API ZkBool ZkTouchDamage_getIsBarrier(ZkTouchDamage const* slf);
CZK_API ZkBool ZkTouchDamage_getIsBlunt(ZkTouchDamage const* slf);
CZK_API ZkBool ZkTouchDamage_getIsEdge(ZkTouchDamage const* slf);
CZK_API ZkBool ZkTouchDamage_getIsFire(ZkTouchDamage const* slf);
CZK_API ZkBool ZkTouchDamage_getIsFly(ZkTouchDamage const* slf);
CZK_API ZkBool ZkTouchDamage_getIsMagic(ZkTouchDamage const* slf);
CZK_API ZkBool ZkTouchDamage_getIsPoint(ZkTouchDamage const* slf);
CZK_API ZkBool ZkTouchDamage_getIsFall(ZkTouchDamage const* slf);
CZK_API float ZkTouchDamage_getRepeatDelaySeconds(ZkTouchDamage const* slf);
CZK_API float ZkTouchDamage_getVolumeScale(ZkTouchDamage const* slf);
CZK_API ZkTouchCollisionType ZkTouchDamage_getCollisionType(ZkTouchDamage const* slf);

CZK_API ZkEarthquake* ZkEarthquake_load(ZkRead* buf, ZkGameVersion version);
CZK_API ZkEarthquake* ZkEarthquake_loadPath(ZkString path, ZkGameVersion version);
CZK_API void ZkEarthquake_del(ZkEarthquake* slf);
CZK_API float ZkEarthquake_getRadius(ZkEarthquake const* slf);
CZK_API float ZkEarthquake_getDuration(ZkEarthquake const* slf);
CZK_API ZkVec3f ZkEarthquake_getAmplitude(ZkEarthquake const* slf);
