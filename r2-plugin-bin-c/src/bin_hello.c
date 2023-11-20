/* radare - LGPL - Copyright 2023 - pancake */

#include <r_bin.h>

static bool load(RBinFile *hello, RBuffer *buf, ut64 loadaddr) {
	return true;
}

static void destroy(RBinFile *hello) {
	RBuffer *buf = R_UNWRAP3 (hello, bo, bin_obj);
	r_buf_free (buf);
}

static RList *strings(RBinFile *hello) {
	// no strings here
	return NULL;
}

static RBinInfo *info(RBinFile *bf) {
	RBinInfo *ret = R_NEW0 (RBinInfo);
	if (R_LIKELY (ret)) {
		ret->lang = NULL;
		ret->file = bf->file? strdup (bf->file): NULL;
		ret->type = strdup ("executable");
		ret->bclass = strdup ("1.0"); // version
		ret->rclass = strdup ("program");
		ret->os = strdup ("any");
		ret->subsystem = strdup ("unknown");
		ret->machine = strdup ("world");
		ret->arch = strdup ("hello");
		ret->has_va = 1;
		ret->bits = 32; // 16?
		ret->big_endian = 0;
		ret->dbg_info = 0;
	}
	return ret;
}

static bool check(RBinFile *hello, RBuffer *buf) {
	r_return_val_if_fail (buf, false);

	ut8 tmp[64] = {0};
	int read_length = r_buf_read_at (buf, 0, tmp, sizeof (tmp));
	if (read_length < 64) {
		return false;
	}
	if (!memcmp (tmp, "HELL", 4)) {
		return true;
	}
	return false;
}

static RList *entries(RBinFile *hello) {
	r_return_val_if_fail (hello, NULL);
	RList *ret = r_list_newf (free);
	if (ret) {
		RBinAddr *ptr = R_NEW0 (RBinAddr);
		if (ptr) {
			ptr->paddr = ptr->vaddr = 0;
			r_list_append (ret, ptr);
		}
	}
	return ret;
}

RBinPlugin r_bin_plugin_hello = {
	.meta = {
		.name = "hello",
		.desc = "hello world for rbin",
		.license = "MIT",
	},
	.load = &load,
	.destroy = &destroy,
	.check = &check,
	.entries = entries,
	.strings = &strings,
	.info = &info,
};

#ifndef R2_PLUGIN_INCORE
R_API RLibStruct radare_plugin = {
	.type = R_LIB_TYPE_BIN,
	.data = &r_bin_plugin_hello,
	.version = R2_VERSION
};
#endif
