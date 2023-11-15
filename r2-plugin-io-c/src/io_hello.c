/* radare - MIT - Copyright 2023 */

#include <r_io.h>

#define SOCKETURI "hello://"

RIOPlugin r_io_plugin_hello;

typedef struct {
	int magic;
	int size;
} HelloUserData;

static int __write(RIO *io, RIODesc *desc, const ut8 *buf, int count) {
	HelloUserData *userdata = desc->data;
	if (userdata) {
		R_LOG_WARN ("writing %d on ", userdata->magic);
	}
	return count;
}

static ut64 __lseek(RIO *io, RIODesc *desc, ut64 offset, int whence) {
	HelloUserData *userdata = desc->data;
	switch (whence) {
	case SEEK_SET: return r_io_desc_seek (desc, 0LL, R_IO_SEEK_CUR);
	case SEEK_CUR: return io->off + offset;
	case SEEK_END: return userdata->size;
	}
	return offset;
}

static int __read(RIO *io, RIODesc *desc, ut8 *buf, int count) {
	ut64 addr = r_io_desc_seek (desc, 0LL, R_IO_SEEK_CUR);
	R_LOG_WARN ("reading %d bytes from 0x%08"PFMT64x, count, addr);
	HelloUserData *userdata = desc->data;
	int i;
	for (i = 0; i < count; i++) {
		buf[0] = userdata->magic;
	}
	return count;
}

static bool __close(RIODesc *desc) {
	// HelloUserData *userdata = desc->data;
	R_FREE (desc->data);
	return true;
}

static bool __check(RIO *io, const char *pathname, bool many) {
	return r_str_startswith (pathname, SOCKETURI);
}

static RIODesc *__open(RIO *io, const char *pathname, int rw, int mode) {
	if (!__check (io, pathname, 0)) {
		return NULL;
	}
	pathname += strlen (SOCKETURI);
	HelloUserData *userdata = R_NEW0 (HelloUserData);
	if (userdata) {
		userdata->size = 64;
		userdata->magic = atoi (pathname);
		R_LOG_WARN ("Opening Hello '%s'", pathname);
		return r_io_desc_new (io,
				&r_io_plugin_hello,
				pathname,
				R_PERM_RW | (rw & R_PERM_X),
			       	mode,
				userdata);
	}
	return NULL;
}

static char *__system(RIO *io, RIODesc *desc, const char *cmd) {
	R_LOG_WARN ("system command executed '%s'", cmd);
	return NULL;
}

RIOPlugin r_io_plugin_hello = {
	.meta = {
		.name = "hello",
		.desc = "Hello World from radare2's IO",
		.license = "MIT",
	},
	.uris = SOCKETURI,
	.open = __open,
	.close = __close,
	.seek = __lseek,
	.read = __read,
	.check = __check,
	.write = __write,
	.system = __system,
};

#ifndef R2_PLUGIN_INCORE
R_API RLibStruct radare_plugin = {
	.type = R_LIB_TYPE_IO,
	.data = &r_io_plugin_hello,
	.version = R2_VERSION
};
#endif
