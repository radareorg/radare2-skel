#include <r_core.h>

int main(int argc, char **argv) {
	RCore *core = r_core_new ();
	char *res = r_core_cmd_str (core, "?E Hello");
	eprintf ("%s", res);
	free (res);
	r_core_free (core);
}
