import Foundation
import R2Pipe

// print(R2Pipe.features)
#if USE_CCALL
if let r2p = R2Pipe("#!ccall") {
    print("Testint ccall")
    if let res = r2p.cmdSync("?E Hello World") {
        print(res)
    } else {
        print("Cannot run command")
    }
} else {
    print("Cannot open ccall")
}
#endif

if let r2p = R2Pipe("#!pipe") {
    print("Testint ccall")
    if let res = r2p.cmdSync("?E Hello World") {
        print(res)
    } else {
        print("Cannot run command")
    }
} else {
    print("Cannot open pipe")
}

print("Hello Swift")
