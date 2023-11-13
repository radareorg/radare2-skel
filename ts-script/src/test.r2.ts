// import { NativePointer, R, R2Pipe, r2 } from "r2papi";
import { r2, R, NativePointer } from  "r2papi";

function Main() {
    const msg = r2.cmd("?E Hello World");
    console.log(msg);r2.cmd
    const main = new NativePointer("main");
    const res = main.analyzeFunction();
    R.analyzeProgram();
    main.disassemble();
    res.functionBasicBlocks().forEach((bb) => {
        console.log(` - ${bb}`);
    });
}

Main();