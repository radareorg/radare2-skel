import Foundation

class RCore {
    let ptr: OpaquePointer

    init(_ ptr: OpaquePointer) {
        self.ptr = ptr
    }

    func cmd(_ command: String) -> Int {
        return command.withCString { r_core_cmd(ptr, $0) }
    }

    func cmd_str(_ command: String) -> String? {
        return command.withCString { cCmd in
            if let output = r_core_cmd_str(ptr, cCmd) {
                let result = String(cString: output)
                output.deallocate()
                return result
            }
            return nil
        }
    }

    func cmdj(_ command: String) -> Any? {
        if let output = cmd_str(command) {
            if let data = output.data(using: .utf8) {
                return try? JSONSerialization.jsonObject(with: data, options: [])
            }
        }
        return nil
    }

    var cons: RCons {
        let consPtr = get_cons(ptr)
        return RCons(consPtr)
    }
}

class RCons {
    let ptr: OpaquePointer

    init(_ ptr: OpaquePointer) {
        self.ptr = ptr
    }

    func print(_ str: String) {
        (str + "\n").withCString { r_cons_print(ptr, $0) }
    }
}

// MARK: - C Symbols

@_silgen_name("get_core")
func get_core(_ cps: OpaquePointer) -> OpaquePointer

@_silgen_name("get_cons")
func get_cons(_ core: OpaquePointer) -> OpaquePointer

@_silgen_name("get_session_data")
func get_session_data(_ cps: OpaquePointer) -> UnsafeMutableRawPointer?

@_silgen_name("set_session_data")
func set_session_data(_ cps: OpaquePointer, _ data: UnsafeMutableRawPointer?)

@_silgen_name("r2_core_cmd")
func r_core_cmd(_ core: OpaquePointer, _ cmd: UnsafePointer<CChar>) -> Int

@_silgen_name("r_core_cmd_str")
func r_core_cmd_str(_ core: OpaquePointer, _ cmd: UnsafePointer<CChar>) -> UnsafeMutablePointer<CChar>?

@_silgen_name("r_cons_print")
func r_cons_print(_ cons: OpaquePointer, _ str: UnsafePointer<CChar>)