// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#include "zenkit-capi/DaedalusVm.h"

#include <zenkit/DaedalusVm.hh>
#include <zenkit/addon/daedalus.hh>

#include "Internal.hh"

struct ZkInternal_DaedalusVm {
	zenkit::DaedalusVm handle;
	std::unordered_map<uint32_t, std::function<void(ZkDaedalusVm*)>> externals;
	std::function<void(ZkDaedalusVm*, ZkDaedalusSymbol*)> externalDefault;
};

ZkDaedalusVm* ZkDaedalusVm_load(ZkRead* buf) {
	ZKC_CHECK_NULL(buf);

	try {
		ZkDaedalusScript script;
		script.load(buf);
		zenkit::register_all_script_classes(script);

		auto* vm = new ZkDaedalusVm {zenkit::DaedalusVm {std::move(script)}, {}, nullptr};

		vm->handle.register_default_external_custom([vm](zenkit::DaedalusVm&, zenkit::DaedalusSymbol& sym) {
			auto callback = vm->externals.find(sym.index());
			if (callback != vm->externals.end()) {
				callback->second(vm);
				return;
			}

			if (vm->externalDefault) vm->externalDefault(vm, &sym);
		});

		return vm;
	} catch (std::exception const& exc) {
		ZKC_LOG_ERROR("ZkDaedalusVm_load() failed: %s", exc.what());
		return nullptr;
	}
}

ZkDaedalusVm* ZkDaedalusVm_loadPath(ZkString path) {
	ZKC_CHECK_NULL(path);

	try {
		auto buf = zenkit::Read::from(path);
		return ZkDaedalusVm_load(buf.get());
	} catch (std::exception const& exc) {
		ZKC_LOG_ERROR("ZkDaedalusVm_load() failed: %s", exc.what());
		return nullptr;
	}
}

ZkDaedalusVm* ZkDaedalusVm_loadVfs(ZkVfs* vfs, ZkString name) {
	ZKC_CHECK_NULL(vfs, name);

	auto node = vfs->find(name);
	if (node == nullptr) return nullptr;

	auto rd = node->open_read();
	return ZkDaedalusVm_load(rd.get());
}

ZKC_DELETER(ZkDaedalusVm)

void ZkDaedalusVm_pushInt(ZkDaedalusVm* slf, int32_t value) {
	ZKC_CHECK_NULLV(slf);
	ZKC_CATCH(slf->handle.push_int(value));
}

void ZkDaedalusVm_pushFloat(ZkDaedalusVm* slf, float value) {
	ZKC_CHECK_NULLV(slf);
	ZKC_CATCH(slf->handle.push_float(value));
}

void ZkDaedalusVm_pushString(ZkDaedalusVm* slf, ZkString value) {
	ZKC_CHECK_NULLV(slf);
	ZKC_CATCH(slf->handle.push_string(value));
}

void ZkDaedalusVm_pushInstance(ZkDaedalusVm* slf, ZkDaedalusInstance* value) {
	ZKC_CHECK_NULLV(slf);

	auto instance = slf->handle.find_symbol_by_index(value->symbol_index());
	if (instance == nullptr) {
		ZKC_LOG_ERROR("ZkDaedalusVm_pushInstance() failed: invalid instance");
		return;
	}

	ZKC_CATCH(slf->handle.push_instance(instance->get_instance()));
}

int32_t ZkDaedalusVm_popInt(ZkDaedalusVm* slf) {
	ZKC_CHECK_NULL(slf);
	ZKC_RETURN_CATCH(slf->handle.pop_int());
}

float ZkDaedalusVm_popFloat(ZkDaedalusVm* slf) {
	ZKC_CHECK_NULL(slf);
	ZKC_RETURN_CATCH(slf->handle.pop_float());
}

ZkString ZkDaedalusVm_popString(ZkDaedalusVm* slf) {
	ZKC_CHECK_NULL(slf);
	ZKC_RETURN_CATCH(slf->handle.pop_string().c_str());
}

ZkDaedalusInstance* ZkDaedalusVm_popInstance(ZkDaedalusVm* slf) {
	ZKC_CHECK_NULL(slf);
	ZKC_RETURN_CATCH(slf->handle.pop_instance().get());
}

ZkDaedalusInstance* ZkDaedalusVm_getGlobalSelf(ZkDaedalusVm* slf) {
	ZKC_CHECK_NULL(slf);
	ZKC_RETURN_CATCH(slf->handle.global_self()->get_instance().get());
}

ZkDaedalusInstance* ZkDaedalusVm_getGlobalOther(ZkDaedalusVm* slf) {
	ZKC_CHECK_NULL(slf);
	ZKC_RETURN_CATCH(slf->handle.global_other()->get_instance().get());
}

ZkDaedalusInstance* ZkDaedalusVm_getGlobalVictim(ZkDaedalusVm* slf) {
	ZKC_CHECK_NULL(slf);
	ZKC_RETURN_CATCH(slf->handle.global_victim()->get_instance().get());
}

ZkDaedalusInstance* ZkDaedalusVm_getGlobalHero(ZkDaedalusVm* slf) {
	ZKC_CHECK_NULL(slf);
	ZKC_RETURN_CATCH(slf->handle.global_hero()->get_instance().get());
}

ZkDaedalusInstance* ZkDaedalusVm_getGlobalItem(ZkDaedalusVm* slf) {
	ZKC_CHECK_NULL(slf);
	ZKC_RETURN_CATCH(slf->handle.global_item()->get_instance().get());
}

void ZkDaedalusVm_setGlobalSelf(ZkDaedalusVm* slf, ZkDaedalusInstance* value) {
	ZKC_CHECK_NULLV(slf);

	auto sym = slf->handle.find_symbol_by_index(value->symbol_index());
	if (sym == nullptr) {
		ZKC_LOG_ERROR("ZkDaedalusVm_setGlobalSelf() failed: invalid instance");
		return;
	}

	ZKC_CATCH(slf->handle.global_self()->set_instance(sym->get_instance()));
}
void ZkDaedalusVm_setGlobalOther(ZkDaedalusVm* slf, ZkDaedalusInstance* value) {
	ZKC_CHECK_NULLV(slf);

	auto sym = slf->handle.find_symbol_by_index(value->symbol_index());
	if (sym == nullptr) {
		ZKC_LOG_ERROR("ZkDaedalusVm_setGlobalOther() failed: invalid instance");
		return;
	}

	ZKC_CATCH(slf->handle.global_other()->set_instance(sym->get_instance()));
}
void ZkDaedalusVm_setGlobalVictim(ZkDaedalusVm* slf, ZkDaedalusInstance* value) {
	ZKC_CHECK_NULLV(slf);

	auto sym = slf->handle.find_symbol_by_index(value->symbol_index());
	if (sym == nullptr) {
		ZKC_LOG_ERROR("ZkDaedalusVm_setGlobalVictim() failed: invalid instance");
		return;
	}

	ZKC_CATCH(slf->handle.global_victim()->set_instance(sym->get_instance()));
}
void ZkDaedalusVm_setGlobalHero(ZkDaedalusVm* slf, ZkDaedalusInstance* value) {
	ZKC_CHECK_NULLV(slf);

	auto sym = slf->handle.find_symbol_by_index(value->symbol_index());
	if (sym == nullptr) {
		ZKC_LOG_ERROR("ZkDaedalusVm_setGlobalHero() failed: invalid instance");
		return;
	}

	ZKC_CATCH(slf->handle.global_hero()->set_instance(sym->get_instance()));
}
void ZkDaedalusVm_setGlobalItem(ZkDaedalusVm* slf, ZkDaedalusInstance* value) {
	ZKC_CHECK_NULLV(slf);

	auto sym = slf->handle.find_symbol_by_index(value->symbol_index());
	if (sym == nullptr) {
		ZKC_LOG_ERROR("ZkDaedalusVm_setGlobalItem() failed: invalid instance");
		return;
	}

	ZKC_CATCH(slf->handle.global_item()->set_instance(sym->get_instance()));
}

void ZkDaedalusVm_callFunction(ZkDaedalusVm* slf, ZkDaedalusSymbol* sym) {
	ZKC_CHECK_NULLV(slf);
	slf->handle.unsafe_call(sym);
}

ZkDaedalusInstance* ZkDaedalusVm_initInstance(ZkDaedalusVm* slf, ZkDaedalusSymbol* sym, ZkDaedalusInstanceType type) {
	ZKC_CHECK_NULL(slf, sym);

	switch (type) {
	case ZkDaedalusInstanceType_GuildValues:
		return slf->handle.init_instance<zenkit::IGuildValues>(sym).get();
	case ZkDaedalusInstanceType_Npc:
		return slf->handle.init_instance<zenkit::INpc>(sym).get();
	case ZkDaedalusInstanceType_Mission:
		return slf->handle.init_instance<zenkit::IMission>(sym).get();
	case ZkDaedalusInstanceType_Item:
		return slf->handle.init_instance<zenkit::IItem>(sym).get();
	case ZkDaedalusInstanceType_Focus:
		return slf->handle.init_instance<zenkit::IFocus>(sym).get();
	case ZkDaedalusInstanceType_Info:
		return slf->handle.init_instance<zenkit::IInfo>(sym).get();
	case ZkDaedalusInstanceType_ItemReact:
		return slf->handle.init_instance<zenkit::IItemReact>(sym).get();
	case ZkDaedalusInstanceType_Spell:
		return slf->handle.init_instance<zenkit::ISpell>(sym).get();
	case ZkDaedalusInstanceType_Svm:
		return slf->handle.init_instance<zenkit::ISvm>(sym).get();
	case ZkDaedalusInstanceType_Menu:
		return slf->handle.init_instance<zenkit::IMenu>(sym).get();
	case ZkDaedalusInstanceType_MenuItem:
		return slf->handle.init_instance<zenkit::IMenuItem>(sym).get();
	case ZkDaedalusInstanceType_Camera:
		return slf->handle.init_instance<zenkit::ICamera>(sym).get();
	case ZkDaedalusInstanceType_MusicSystem:
		return slf->handle.init_instance<zenkit::IMusicSystem>(sym).get();
	case ZkDaedalusInstanceType_MusicTheme:
		return slf->handle.init_instance<zenkit::IMusicTheme>(sym).get();
	case ZkDaedalusInstanceType_MusicJingle:
		return slf->handle.init_instance<zenkit::IMusicJingle>(sym).get();
	case ZkDaedalusInstanceType_ParticleEffect:
		return slf->handle.init_instance<zenkit::IParticleEffect>(sym).get();
	case ZkDaedalusInstanceType_EffectBase:
		return slf->handle.init_instance<zenkit::IEffectBase>(sym).get();
	case ZkDaedalusInstanceType_ParticleEffectEmitKey:
		return slf->handle.init_instance<zenkit::IParticleEffectEmitKey>(sym).get();
	case ZkDaedalusInstanceType_FightAi:
		return slf->handle.init_instance<zenkit::IFightAi>(sym).get();
	case ZkDaedalusInstanceType_SoundEffect:
		return slf->handle.init_instance<zenkit::ISoundEffect>(sym).get();
	case ZkDaedalusInstanceType_SoundSystem:
		return slf->handle.init_instance<zenkit::ISoundSystem>(sym).get();
	}

	ZKC_LOG_ERROR("ZkDaedalusVm_initInstance() failed: invalid instance type");
	return nullptr;
}

void ZkDaedalusVm_registerExternal(ZkDaedalusVm* slf,
                                   ZkDaedalusSymbol* sym,
                                   ZkDaedalusVmExternalCallback cb,
                                   void* ctx) {
	ZKC_CHECK_NULLV(slf, sym, cb);
	slf->externals.insert_or_assign(sym->index(), [cb, ctx](ZkDaedalusVm* vm) { cb(ctx, vm); });
}

void ZkDaedalusVm_registerExternalDefault(ZkDaedalusVm* slf, ZkDaedalusVmExternalDefaultCallback cb, void* ctx) {
	ZKC_CHECK_NULLV(slf);
	slf->externalDefault = [cb, ctx](ZkDaedalusVm* vm, ZkDaedalusSymbol* sym) { cb(ctx, vm, sym); };
}

void ZkDaedalusVm_printStackTrace(ZkDaedalusVm* slf) {
	ZKC_CHECK_NULLV(slf);
	slf->handle.print_stack_trace();
}
