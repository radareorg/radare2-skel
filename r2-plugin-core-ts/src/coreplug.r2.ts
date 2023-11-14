import { r2, R, NativePointer } from  "r2papi";

function InstantiateCorePlugin() {
    r2.unload("core", "mycore");
    r2.plugin("core", function() {
        console.log("==> The 'mycore' plugin has been instantiated. Type 'mycore' to test it");
	function coreCall(cmd: string) {
		if (cmd.startsWith("mycore")) {
			console.log("Hello From My Core!");
			return true;
		}
		return false;
	}
	return {
		"name": "mycore",
		"license": "MIT",
		"desc": "simple core plugin in typescript for radare2",
		"call": coreCall,
	}
    });
}

InstantiateCorePlugin();
