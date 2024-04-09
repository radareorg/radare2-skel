/* radare - MIT - Copyright 2024 */

// XXX this is an experimental plugin that is subject to change in the future.

#include <r_parse.h>

RParsePlugin r_parse_plugin_hello;

static int parse(RParse *p, const char *data, char *str) {
	char *input = strdup (data);
	input = r_str_replace_all (input, "sp, -0x60", "LOCALVAR");
	strcpy (str, input);
	return true;
}

RParsePlugin r_parse_plugin_hello = {
	.name = "hello",
	.desc = "Hello World from radare2's RParse",
	.parse = parse,
};

#ifndef R2_PLUGIN_INCORE
R_API RLibStruct radare_plugin = {
	.type = R_LIB_TYPE_PARSE,
	.data = &r_parse_plugin_hello,
	.version = R2_VERSION
};
#endif
