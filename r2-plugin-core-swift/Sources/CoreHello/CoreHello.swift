import Foundation

private struct HelloData {
    var greeting: String
}

@_cdecl("swift_hello_call")
func hello_call(_ cps: OpaquePointer, _ input: UnsafePointer<CChar>) -> Bool {
    let command = String(cString: input)
    guard command.hasPrefix("hello") else {
        return false
    }

    let core = get_core(cps)
    let cons = get_cons(core)

    let sessionGreeting = sessionData(in: cps)?.pointee.greeting ?? "Swift"
    printLine(cons, "Hello \(sessionGreeting)! Fetching binary info...")

    guard let jsonString = commandOutput(from: core, command: "ij") else {
        printLine(cons, "Failed to read JSON from `ij` command")
        return true
    }

    switch parseBinaryInfo(from: jsonString) {
    case let .success(info):
        printLine(cons, info)
    case let .failure(error):
        printLine(cons, "Failed to parse JSON: \(error.localizedDescription)")
    }

    return true
}

@_cdecl("swift_hello_init")
func hello_init(_ cps: OpaquePointer) -> Bool {
    let dataPointer = UnsafeMutablePointer<HelloData>.allocate(capacity: 1)
    dataPointer.initialize(to: HelloData(greeting: "from Swift"))
    set_session_data(cps, UnsafeMutableRawPointer(dataPointer))
    return true
}

@_cdecl("swift_hello_fini")
func hello_fini(_ cps: OpaquePointer) -> Bool {
    if let raw = get_session_data(cps) {
        let pointer = raw.assumingMemoryBound(to: HelloData.self)
        pointer.deinitialize(count: 1)
        pointer.deallocate()
        set_session_data(cps, nil)
    }
    return true
}

// MARK: - Helpers

private func sessionData(in cps: OpaquePointer) -> UnsafeMutablePointer<HelloData>? {
    guard let raw = get_session_data(cps) else {
        return nil
    }
    return raw.assumingMemoryBound(to: HelloData.self)
}

private func commandOutput(from core: OpaquePointer, command: String) -> String? {
    command.withCString { cString in
        guard let outputPtr = r_core_cmd_str(core, cString) else {
            return nil
        }
        defer { outputPtr.deallocate() }
        return String(cString: outputPtr)
    }
}

private func parseBinaryInfo(from jsonString: String) -> Result<String, Error> {
    guard let data = jsonString.data(using: .utf8) else {
        return .failure(JSONError.encoding)
    }

    do {
        let object = try JSONSerialization.jsonObject(with: data, options: [])
        if let dict = object as? [String: Any],
           let bin = dict["bin"] as? [String: Any],
           let arch = bin["arch"] as? String,
           let bits = bin["bits"] as? Int {
            return .success("Binary arch: \(arch) (\(bits) bits)")
        }
        return .success("ij JSON: \(object)")
    } catch {
        return .failure(error)
    }
}

private func printLine(_ cons: OpaquePointer, _ message: String) {
    (message + "\n").withCString { cString in
        r_cons_print(cons, cString)
    }
}

private enum JSONError: Error {
    case encoding
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

@_silgen_name("r_core_cmd_str")
func r_core_cmd_str(_ core: OpaquePointer, _ cmd: UnsafePointer<CChar>) -> UnsafeMutablePointer<CChar>?

@_silgen_name("r_cons_print")
func r_cons_print(_ cons: OpaquePointer, _ str: UnsafePointer<CChar>)


