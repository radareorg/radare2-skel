#ifndef SHIM_H
#define SHIM_H

#include <r_core.h>

extern bool swift_hello_call(RCorePluginSession *cps, const char *input);
extern bool swift_hello_init(RCorePluginSession *cps);
extern bool swift_hello_fini(RCorePluginSession *cps);

#endif