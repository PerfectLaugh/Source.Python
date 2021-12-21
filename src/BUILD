load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")
load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_library")

load(":files.bzl", "sp_files")

cmake(
    name = "asmjit",
    cache_entries = {
        "ASMJIT_STATIC": "TRUE",
        "ASMJIT_TEST": "FALSE",
    },
    lib_source = "@asmjit//:all_srcs",
    out_include_dir = "src",
)

cmake(
    name = "dyncall_s",
    lib_source = "@dyncall//:all_srcs",
    out_include_dir = "dyncall",

    out_static_libs = select({
        "@bazel_tools//src/conditions:windows": ["dyncall_s.lib"],
        "//conditions:default": ["dyncall_s.a"],
    }),
)

cmake(
    name = "DynamicHooks",
    lib_source = "@DynamicHooks//:all_srcs",
    out_include_dir = "src",
    working_directory = "src",

    out_static_libs = select({
        "@bazel_tools//src/conditions:windows": ["DynamicHooks.lib"],
        "//conditions:default": ["DynamicHooks.a"],
    }),
)

filegroup(
    name = "sp-loader",
    srcs = [
        "core/utilities/shared_utils.h",
        "loader/loader_main.h",
        "loader/updater.h",
        "loader/definitions.h",
        "loader/loader_main.cpp",
        "loader/updater.cpp",
    ],
)

COPTS_GENERIC = select({
    "@bazel_tools//src/conditions:windows": [
        "/D_NDEBUG", "/wd4005", "/MP", "/MT",
    ],
    "//conditions:default": [
        "-Wall", "-Wno-uninitialized", "-Wno-switch", "-Wno-unused",
        "-Wno-non-virtual-dtor", "-Wno-overloaded-virtual",
        "-Wno-conversion-null", "-Wno-write-strings",
        "-Wno-invalid-offsetof", "-Wno-reorder",

        "-mfpmath=sse", "-msse", "-m32", "-fno-strict-aliasing",
        "-std=c++17", "-fno-threadsafe-statics", "-v", "-fvisibility=hidden",

        "-D_NDEBUG",
    ],
})

COPTS_NOT_BMS = select({
    "@bazel_tools//src/conditions:windows": [],
    "//conditions:default": [
        "-Dstricmp=strcasecmp", "-D_stricmp=strcasecmp", "-D_strnicmp=strncasecmp",
        "-Dstrnicmp=strncasecmp", "-D_snprintf=snprintf",
        "-D_vsnprintf=vsnprintf", "-D_alloca=alloca", "-Dstrcmpi=strcasecmp",
    ],
})

cc_binary(
    name = "csgo-source-python",
    srcs = [
        ":sp-loader",
    ],

    deps = [
        "@boost//:filesystem",
        "@hl2sdk_csgo//:hl2sdk",
    ],

    defines = [
        "GAME_DLL=1",
    ],

    copts = COPTS_GENERIC + COPTS_NOT_BMS,
    linkopts = select({
        "@bazel_tools//src/conditions:windows": ["legacy_stdio_definitions.lib"],
        "//conditions:default": [],
    }),

    linkshared = True,
    linkstatic = True,
)

cc_binary(
    name = "csgo-core",
    srcs = sp_files("csgo"),

    deps = [
        "@hl2sdk_csgo//:hl2sdk",
        "@pybind11//:pybind11_embed",
        ":asmjit",
        ":dyncall_s",
        ":DynamicHooks",
    ],

    defines = [
        "BOOST_PYTHON_STATIC_LIB",
        "BOOST_PYTHON_SOURCE",
        "BOOST_PYTHON_NO_LIB",
        "BOOST_PYTHON_MAX_ARITY=32",
    ] + [
        "GAME_DLL=1",
    ],
    includes = [
        "core",
    ],

    copts = COPTS_GENERIC + COPTS_NOT_BMS,
    linkopts = select({
        "@bazel_tools//src/conditions:windows": ["legacy_stdio_definitions.lib"],
        "//conditions:default": [],
    }),

    linkshared = True,
    linkstatic = True,
)
