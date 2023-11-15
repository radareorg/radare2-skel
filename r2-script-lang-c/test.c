#include <r_core.h>

void entry(RCore *core) {
	R_LOG_INFO ("Hello From %p", core);
	char *res = r_core_cmd_str (core, "?E Hello");
	eprintf ("%s", res);
	free (res);
}
