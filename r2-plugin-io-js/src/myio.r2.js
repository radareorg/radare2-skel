const ioqjsPlugin = {
	name: "myio",
	desc: "Simple io plugin in javascript",
	license: "MIT",
	check: function (uri, perm) {
		return uri.startsWith("myio://");
	},
	open: function (uri, perm) {
		console.log("open URI is " + uri);
		return true;
	},
	read: function (addr, len) {
		console.log("READ");
		return [1,2,3];
	},
	seek: function (addr, whence) {
		const size = 32; // XXX custom size / resizable?
		const res = (whence === 2) ? size: addr;
		console.log("seek", addr, whence, "=", res);
		return res;
	},
	write: function () {},
	close: function () {},
}

r2.plugin("io", () => ioqjsPlugin);

// show plugin in the io listing
console.log("==> MyIO plugin: (oL~myio), use 'o myio://123' to test it");
console.log(r2.cmd("oL~myio"));
