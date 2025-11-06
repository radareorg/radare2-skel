#include <r_core.h>
#include <stdbool.h>

extern bool swift_hello_call(RCorePluginSession *cps, const char *input);
extern bool swift_hello_init(RCorePluginSession *cps);
extern bool swift_hello_fini(RCorePluginSession *cps);

static bool hello_call(RCorePluginSession *cps, const char *input) {
    return swift_hello_call(cps, input);
}

static bool hello_init(RCorePluginSession *cps) {
    return swift_hello_init(cps);
}

static bool hello_fini(RCorePluginSession *cps) {
    return swift_hello_fini(cps);
}

RCore *get_core(RCorePluginSession *cps) {
    return cps->core;
}

RCons *get_cons(RCore *core) {
    return core->cons;
}

void *get_session_data(RCorePluginSession *cps) {
    return cps->data;
}

void set_session_data(RCorePluginSession *cps, void *data) {
    cps->data = data;
}

RCorePlugin r_core_plugin_hello = {
    .meta = {
        .name = "core-hello",
        .desc = "hello world from an r2core plugin in Swift",
        .author = "pancake",
        .license = "MIT",
    },
    .call = hello_call,
    .init = hello_init,
    .fini = hello_fini,
};

#ifndef R2_PLUGIN_INCORE
RLibStruct radare_plugin = {
    .type = R_LIB_TYPE_CORE,
    .data = &r_core_plugin_hello,
    .version = R2_VERSION,
    .abiversion = R2_ABIVERSION
};
#endif