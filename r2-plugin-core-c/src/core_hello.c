/* radare - Copyright 2025 - yourname */

#define R_LOG_ORIGIN "core.hello"

#include <r_core.h>

typedef struct hello_data_t {
	char *name;
} HelloData;

static bool hello_call(RCorePluginSession *cps, const char *input) {
	RCore *core = cps->core;
	if (r_str_startswith (input, "hello")) {
		HelloData *hd = cps->data;
		if (hd) {
			r_cons_printf (core->cons, "Hello %s\n", hd->name);
		} else {
			R_LOG_ERROR ("HelloData is null");
		}
		return true;
	}
	return false;
}

static bool hello_init(RCorePluginSession *cps) {
	HelloData *hd = R_NEW0 (HelloData);
	hd->name = strdup ("World");
	cps->data = hd;
	return true;
}

static bool hello_fini(RCorePluginSession *cps) {
	HelloData *hd = cps->data;
	free (hd->name);
	free (hd);
	cps->data = NULL;
	return true;
}

// PLUGIN Definition Info
RCorePlugin r_core_plugin_hello = {
	.meta = {
		.name = "core-hello",
		.desc = "hello world from an r2core plugin",
		.author = "pancake",
		.license = "MIT",
	},
	.call = hello_call,
	.init = hello_init, // optional
	.fini = hello_fini, // optional
};

#ifndef R2_PLUGIN_INCORE
R_API RLibStruct radare_plugin = {
	.type = R_LIB_TYPE_CORE,
	.data = &r_core_plugin_hello,
	.version = R2_VERSION,
	.abiversion = R2_ABIVERSION
};
#endif
