/* radare - MIT - Copyright 2026 */

#include <r_fs.h>

typedef struct {
	// TODO shared fs data
} HelloData;

static RFSFile *fs_hello_open(RFSRoot *root, const char *path, bool create) {
	RFSFile *file = r_fs_file_new (root, path); 
	if (!file) {
		return NULL;
	}

	// TODO filesystem-specific open logic here

	return file;
}

static int fs_hello_read(RFSFile *file, ut64 addr, int len) {
	// TODO read implementation here
	// Read from file->ptr at offset addr
	// Store result in file->data
	// Return bytes read
	return -1;
}

static void fs_hello_close(RFSFile *file) {
	R_RETURN_IF_FAIL (file);
	R_FREE(file->ptr);
}


static RList *fs_hello_dir(RFSRoot *root, const char *path, int view /*ignored*/) {
	RList *list = r_list_new ();
	if (!list) {
		return NULL;
	}

	// TODO directory listing logic here
	// For each entry, create an RFSFile and append to list:
	//     RFSFile *fsf = r_fs_file_new (NULL, name);
	//     fsf->type = 'd' or 'f'; // directory or file
	//     fsf->size = file_size;
	//     r_list_append (list, fsf);
	return list;
}

static bool fs_hello_mount(RFSRoot *root) {
	HelloData *ctx = R_NEW0 (HelloData);
	if (!ctx) {
		return false;
	}

	// TODO Mount logic here

	root->ptr = ctx;
	return true;
}

static void fs_hello_umount(RFSRoot *root) {
	R_RETURN_IF_FAIL (root);
	R_FREE (root->ptr);
}


RFSPlugin r_fs_plugin_hello = {
	.meta = {
		.name = "hello",
		.desc = "HELLO filesystem",
		.license = "MIT",
	},
	.open = fs_hello_open,
	.read = fs_hello_read,
	.close = fs_hello_close,
	.dir = fs_hello_dir,
	.mount = fs_hello_mount,
	.umount = fs_hello_umount,
};

#ifndef R2_PLUGIN_INCORE
R_API RLibStruct radare_plugin = {
	.type = R_LIB_TYPE_FS,
	.data = &r_fs_plugin_hello,
	.version = R2_VERSION
};
#endif
