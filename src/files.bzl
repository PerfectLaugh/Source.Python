UTILITIES_FILES = [
    "core/utilities/sp_util.h",
    "core/utilities/shared_utils.h",
    "core/utilities/call_python.h",
    "core/utilities/wrap_macros.h",
    "core/utilities/conversions.h",
    "core/utilities/ipythongenerator.h",
    "core/utilities/conversions/baseentity_from.cpp",
    "core/utilities/conversions/basehandle_from.cpp",
    "core/utilities/conversions/edict_from.cpp",
    "core/utilities/conversions/index_from.cpp",
    "core/utilities/conversions/inthandle_from.cpp",
    "core/utilities/conversions/playerinfo_from.cpp",
    "core/utilities/conversions/pointer_from.cpp",
    "core/utilities/conversions/userid_from.cpp",
    "core/utilities/conversions/address_from.cpp",
    "core/utilities/conversions/uniqueid_from.cpp",
]

CORE_FILES = [
    "core/sp_python.h",
    "core/sp_main.h",
    "core/export_main.h",
    "core/sp_hooks.h",
    "core/sp_python.cpp",
    "core/sp_main.cpp",
    "core/export_main.cpp",
    "core/sp_hooks.cpp",
]

MODULE_BITBUFFERS_FILES = [
    "core/modules/bitbuffers/bitbuffers.h",
    "core/modules/bitbuffers/bitbuffers_wrap.cpp",
]

MODULE_COLORS_FILES = [
    "core/modules/colors/colors.h",
    "core/modules/colors/colors_wrap.cpp",
]

MODULE_COMMANDS_FILES = [
    "core/modules/commands/commands_client.h",
    "core/modules/commands/commands.h",
    "core/modules/commands/commands_say.h",
    "core/modules/commands/commands_server.h",
    "core/modules/commands/commands_client.cpp",
    "core/modules/commands/commands_client_wrap.cpp",
    "core/modules/commands/commands_wrap.cpp",
    "core/modules/commands/commands_say.cpp",
    "core/modules/commands/commands_say_wrap.cpp",
    "core/modules/commands/commands_server.cpp",
    "core/modules/commands/commands_server_wrap.cpp",
]

MODULE_CORE_FILES = [
    "core/modules/core/core.h",
    "core/modules/core/core.cpp",
    "core/modules/core/core_wrap.cpp",
]

MODULE_CORE_CACHE_FILES = [
    "core/modules/core/core_cache.h",
    "core/modules/core/core_cache.cpp",
    "core/modules/core/core_cache_wrap.cpp",
]

MODULE_EVENTS_FILES = [
    "core/modules/events/events.h",
    "core/modules/events/events_generator.h",
    "core/modules/events/events_generator.cpp",
    "core/modules/events/events_wrap.cpp",
]

MODULE_FILESYSTEM_FILES = [
    "core/modules/filesystem/filesystem.h",
    "core/modules/filesystem/filesystem.cpp",
    "core/modules/filesystem/filesystem_wrap.cpp",
]

MODULE_FILTERS_FILES = [
    "core/modules/filters/filters_recipients.h",
    "core/modules/filters/filters_recipients.cpp",
    "core/modules/filters/filters_recipients_wrap.cpp",
]

MODULE_KEYVALUES_FILES = [
    "core/modules/keyvalues/keyvalues.h",
    "core/modules/keyvalues/keyvalues_wrap.cpp",
]

MODULE_LISTENERS_FILES = [
    "core/modules/listeners/listeners_manager.h",
    "core/modules/listeners/listeners_manager.cpp",
    "core/modules/listeners/listeners_wrap.cpp",
]

MODULE_MATHLIB_FILES = [
    "core/modules/mathlib/mathlib.h",
    "core/modules/mathlib/mathlib_wrap.cpp",
]

MODULE_MEMORY_FILES = [
    "core/modules/memory/memory_alloc.h",
    "core/modules/memory/memory_calling_convention.h",
    "core/modules/memory/memory_function.h",
    "core/modules/memory/memory_function_info.h",
    "core/modules/memory/memory_hooks.h",
    "core/modules/memory/memory_pointer.h",
    "core/modules/memory/memory_scanner.h",
    "core/modules/memory/memory_signature.h",
    "core/modules/memory/memory_tools.h",
    "core/modules/memory/memory_utilities.h",
    "core/modules/memory/memory_wrap.h",
    "core/modules/memory/memory_rtti.h",
    "core/modules/memory/memory_exception.h",
    "core/modules/memory/memory_function.cpp",
    "core/modules/memory/memory_hooks.cpp",
    "core/modules/memory/memory_pointer.cpp",
    "core/modules/memory/memory_scanner.cpp",
    "core/modules/memory/memory_wrap.cpp",
    "core/modules/memory/memory_rtti.cpp",
    "core/modules/memory/memory_exception.cpp",
]

MODULE_MESSAGES_FILES = [
    "core/modules/messages/messages.h",
    "core/modules/messages/messages.cpp",
    "core/modules/messages/messages_wrap.cpp",
]

MODULE_NET_CHANNEL_FILES = [
    "core/modules/net_channel/net_channel_wrap.cpp",
]

MODULE_PHYSICS_FILES = [
    "core/modules/physics/physics.h",
    "core/modules/physics/physics.cpp",
    "core/modules/physics/physics_wrap.cpp",
]

MODULE_PLUGINS_FILES = [
    "core/modules/plugins/plugins.h",
    "core/modules/plugins/plugins.cpp",
    "core/modules/plugins/plugins_wrap.cpp",
]

MODULE_STRINGTABLES_FILES = [
    "core/modules/stringtables/stringtables.h",
    "core/modules/stringtables/stringtables.cpp",
    "core/modules/stringtables/stringtables_wrap.cpp",
]

MODULE_STUDIO_FILES = [
    # hl2sdk/${BRANCH}/public/studio.cpp
    "core/modules/studio/studio.h",
    "core/modules/studio/studio_wrap.cpp",
    "core/modules/studio/studio_constants_wrap.cpp",
    "core/modules/studio/studio_cache_wrap.cpp",
]

def patches_files(engine):
    files = ["core/patches/undefined_symbols.cpp"]

    engine_files = [
        "core/patches/{engine}/undefined_symbols.h".format(engine = engine),
        "core/patches/{engine}/patches.cpp".format(engine = engine),
    ]

    return files + engine_files

def module_cvars_files(engine):
    files = [
        "core/modules/cvars/cvars.h",
        "core/modules/cvars/cvars_wrap.cpp",
    ]

    engine_files = [
        "core/modules/cvars/{engine}/cvars.h".format(engine = engine),
    ]

    return files + engine_files

def module_effects_files(engine):
    files = [
        "core/modules/effects/effects_base.h",
        "core/modules/effects/effects_wrap.cpp",
        "core/modules/effects/effects_base_wrap.cpp",
    ]

    engine_files = [
        "core/modules/effects/{engine}/effects_base_wrap.h".format(engine = engine),
    ]

    return files + engine_files

def module_engines_files(engine):
    files = [
        "core/modules/engines/engines.h",
        "core/modules/engines/engines_server.h",
        "core/modules/engines/engines_gamerules.h",
        "core/modules/engines/engines_wrap.cpp",
        "core/modules/engines/engines_server.cpp",
        "core/modules/engines/engines_server_wrap.cpp",
        "core/modules/engines/engines_sound_wrap.cpp",
        "core/modules/engines/engines_trace_wrap.cpp",
        "core/modules/engines/engines_gamerules.cpp",
        "core/modules/engines/engines_gamerules_wrap.cpp",
    ]

    engine_files = [
        "core/modules/engines/{engine}/engines.h".format(engine = engine),
        "core/modules/engines/{engine}/engines_wrap.h".format(engine = engine),
    ]

    return files + engine_files

def module_entities_files(engine):
    files = [
        "core/modules/entities/entities.h",
        "core/modules/entities/entities_generator.h",
        "core/modules/entities/entities_factories.h",
        "core/modules/entities/entities_datamaps.h",
        "core/modules/entities/entities_props.h",
        "core/modules/entities/entities_entity.h",
        "core/modules/entities/entities.cpp",
        "core/modules/entities/entities_constants_wrap.cpp",
        "core/modules/entities/entities_helpers_wrap.cpp",
        "core/modules/entities/entities_wrap.cpp",
        "core/modules/entities/entities_factories.cpp",
        "core/modules/entities/entities_factories_wrap.cpp",
        "core/modules/entities/entities_generator.cpp",
        "core/modules/entities/entities_datamaps.cpp",
        "core/modules/entities/entities_datamaps_wrap.cpp",
        "core/modules/entities/entities_props.cpp",
        "core/modules/entities/entities_props_wrap.cpp",
        "core/modules/entities/entities_entity.cpp",
        "core/modules/entities/entities_entity_wrap.cpp",
    ]

    engine_files = [
        "core/modules/entities/{engine}/entities.h".format(engine = engine),
        "core/modules/entities/{engine}/entities_factories_wrap.h".format(engine = engine),
        "core/modules/entities/{engine}/entities_wrap.h".format(engine = engine),
        "core/modules/entities/{engine}/entities_datamaps_wrap.h".format(engine = engine),
        "core/modules/entities/{engine}/entities_props.h".format(engine = engine),
        "core/modules/entities/{engine}/entities_props_wrap.h".format(engine = engine),
        "core/modules/entities/{engine}/entities_constants_wrap.h".format(engine = engine),
    ]

    return files + engine_files

def module_globals_files(engine):
    files = ["core/modules/globals/globals_wrap.cpp"]
    engine_files = ["core/modules/globals/{engine}/globals_wrap.h".format(engine = engine)]

    return files + engine_files

def module_players_files(engine):
    files = [
        "core/modules/players/players_wrap.h",
        "core/modules/players/players_entity.h",
        "core/modules/players/players_generator.h",
        "core/modules/players/players_bots_wrap.cpp",
        "core/modules/players/players_constants_wrap.cpp",
        "core/modules/players/players_entity.cpp",
        "core/modules/players/players_helpers_wrap.cpp",
        "core/modules/players/players_wrap.cpp",
        "core/modules/players/players_generator.cpp",
        "core/modules/players/players_voice.cpp",
    ]

    engine_files = [
        "core/modules/players/{engine}/players_constants_wrap.h".format(engine = engine),
        "core/modules/players/{engine}/players_wrap.h".format(engine = engine),
    ]

    return files + engine_files

def module_steam_files(engine):
    files = [
        "core/modules/steam/steam_wrap.h",
        "core/modules/steam/steam_wrap.cpp",
    ]

    engine_files = [
        "core/modules/steam/{engine}/steam_wrap.h".format(engine = engine),
    ]

    return files + engine_files


def module_weapons_files(engine):
    files = [
        "core/modules/weapons/weapons_entity.h",
        "core/modules/weapons/weapons_constants_wrap.cpp",
        "core/modules/weapons/weapons_scripts_wrap.cpp",
        "core/modules/weapons/weapons_entity.cpp",
        "core/modules/weapons/weapons_entity_wrap.cpp",
    ]

    engine_files = [
        "core/modules/weapons/{engine}/weapons_constants_wrap.h".format(engine = engine),
        "core/modules/weapons/{engine}/weapons_scripts_wrap.h".format(engine = engine),
    ]

    return files + engine_files

def modules_files(engine):
    files = []

    files += MODULE_BITBUFFERS_FILES
    files += MODULE_COLORS_FILES
    files += MODULE_COMMANDS_FILES
    files += MODULE_CORE_FILES
    files += MODULE_CORE_CACHE_FILES
    files += MODULE_EVENTS_FILES
    files += MODULE_FILESYSTEM_FILES
    files += MODULE_FILTERS_FILES
    files += MODULE_KEYVALUES_FILES
    files += MODULE_LISTENERS_FILES
    files += MODULE_MATHLIB_FILES
    files += MODULE_MEMORY_FILES
    files += MODULE_MESSAGES_FILES
    files += MODULE_NET_CHANNEL_FILES
    files += MODULE_PHYSICS_FILES
    files += MODULE_PLUGINS_FILES
    files += MODULE_STRINGTABLES_FILES
    files += MODULE_STUDIO_FILES

    files += module_cvars_files(engine)
    files += module_effects_files(engine)
    files += module_engines_files(engine)
    files += module_entities_files(engine)
    files += module_globals_files(engine)
    files += module_players_files(engine)
    files += module_steam_files(engine)
    files += module_weapons_files(engine)

    return files

def sp_files(engine):
    return patches_files(engine) + modules_files(engine)
