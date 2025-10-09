package main

/*
#cgo CFLAGS: -I/usr/local/include/libr
#cgo LDFLAGS: -L/usr/local/lib -lr_core -lr_config -lr_debug -lr_bin -lr_lang -lr_anal -lr_bp -lr_egg -lr_asm -lr_arch -lr_esil -lr_flag -lr_reg -lr_search -lr_syscall -lr_fs -lr_io -lr_socket -lr_cons -lr_magic -lr_muta -lr_util -ldl

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <r_core.h>
#include <r_cons.h>

extern int goHelloCall(RCorePluginSession *cps, char *input);
extern int goHelloInit(RCorePluginSession *cps);
extern int goHelloFini(RCorePluginSession *cps);

static inline bool hello_call(RCorePluginSession *cps, const char *input) {
	return goHelloCall(cps, (char *)input) != 0;
}

static inline bool hello_init(RCorePluginSession *cps) {
	return goHelloInit(cps) != 0;
}

static inline bool hello_fini(RCorePluginSession *cps) {
	return goHelloFini(cps) != 0;
}

static inline void cps_set_handle(RCorePluginSession *cps, uintptr_t handle) {
	cps->data = (void *)handle;
}

static inline uintptr_t cps_get_handle(RCorePluginSession *cps) {
	return (uintptr_t)cps->data;
}

static inline RCons *cps_cons(RCorePluginSession *cps) {
	return cps && cps->core ? cps->core->cons : NULL;
}

RCorePlugin r_core_plugin_hello __attribute__((weak, used)) = {
	.meta = {
		.name = "core-hello",
		.desc = "hello world from an r2core plugin",
		.author = "pancake",
		.license = "MIT",
	},
	.call = hello_call,
	.init = hello_init,
	.fini = hello_fini,
};

#ifndef R2_PLUGIN_INCORE
RLibStruct radare_plugin __attribute__((weak, used)) = {
	.type = R_LIB_TYPE_CORE,
	.data = &r_core_plugin_hello,
	.version = R2_VERSION,
	.abiversion = R2_ABIVERSION
};
#endif
*/
import "C"
import (
	"runtime/cgo"
	"unsafe"
)

func setSessionHandle(cps *C.RCorePluginSession, h cgo.Handle) {
	C.cps_set_handle(cps, C.uintptr_t(h))
}

func clearSessionHandle(cps *C.RCorePluginSession) {
	C.cps_set_handle(cps, 0)
}

func sessionHandle(cps *C.RCorePluginSession) (cgo.Handle, bool) {
	handleID := uintptr(C.cps_get_handle(cps))
	if handleID == 0 {
		return 0, false
	}
	return cgo.Handle(handleID), true
}

func sessionData(cps *C.RCorePluginSession) (*helloSession, bool) {
	handle, ok := sessionHandle(cps)
	if !ok {
		return nil, false
	}
	value := handle.Value()
	if value == nil {
		return nil, false
	}
	data, ok := value.(*helloSession)
	return data, ok
}

//export goHelloCall
func goHelloCall(cps *C.RCorePluginSession, input *C.char) C.int {
	if cps == nil || input == nil {
		return 0
	}

	session, ok := sessionData(cps)
	if !ok {
		return 0
	}

	message, handled := handleHelloCommand(session, C.GoString(input))
	if !handled {
		return 0
	}

	cons := C.cps_cons(cps)
	if cons == nil {
		return 0
	}

	cMessage := C.CString(message)
	defer C.free(unsafe.Pointer(cMessage))

	C.r_cons_print(cons, cMessage)
	return 1
}

//export goHelloInit
func goHelloInit(cps *C.RCorePluginSession) C.int {
	if cps == nil {
		return 0
	}

	session := newHelloSession()
	handle := cgo.NewHandle(session)
	setSessionHandle(cps, handle)
	return 1
}

//export goHelloFini
func goHelloFini(cps *C.RCorePluginSession) C.int {
	if cps == nil {
		return 0
	}

	if session, ok := sessionData(cps); ok {
		releaseHelloSession(session)
	}

	if handle, ok := sessionHandle(cps); ok {
		handle.Delete()
	}

	clearSessionHandle(cps)
	return 1
}
