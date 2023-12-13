/* radare - Copyright 2023 - yourname */

#define R_LOG_ORIGIN "core.hello"

#include <r_core.h>

static int r_cmd_hello_client(void *user, const char *input) {
	RCore *core = (RCore *) user;
	if (r_str_startswith (input, "hello")) {
		r_cons_printf ("world\n");
		return true;
	}
	return false;
}

// PLUGIN Definition Info
RCorePlugin r_core_plugin_hello = {
	.meta = {
		.name = "core-hello",
		.desc = "hello world from an r2core plugin",
		.author = "pancake",
		.license = "MIT",
	},
	.call = r_cmd_hello_client,
};

#ifndef R2_PLUGIN_INCORE
R_API RLibStruct radare_plugin = {
	.type = R_LIB_TYPE_CORE,
	.data = &r_core_plugin_hello,
	.version = R2_VERSION
};
#endif
