// swift-tools-version: 5.9
import PackageDescription
import Foundation

let env = ProcessInfo.processInfo.environment

var includePrefixes: [String] = []
if let r2Prefix = env["R2_PREFIX"], !r2Prefix.isEmpty {
    includePrefixes.append(r2Prefix)
}
if let prefix = env["PREFIX"], !prefix.isEmpty {
    includePrefixes.append(prefix)
}
includePrefixes.append(contentsOf: [
    "/usr/local",
    "/usr",
    "/opt/homebrew"
])

let includeSubdirs = [
    "include",
    "include/libr",
    "include/libr/sdb",
    "include/libr/socket",
    "include/libr/util"
]

let fileManager = FileManager.default
let includeDirs = Array(
    Set(
        includePrefixes.flatMap { prefix in
            includeSubdirs.map { "\(prefix)/\($0)" }
        }
    )
)
.filter { fileManager.fileExists(atPath: $0) }
.sorted()

let cSettings: [CSetting] = [
    .define("R_LOG_ORIGIN", to: "\"core.hello\""),
    .headerSearchPath("."),
] + includeDirs.map { .unsafeFlags(["-I", $0]) }

let package = Package(
    name: "r2-plugin-core-swift",
    products: [
        .library(
            name: "CoreHello",
            type: .dynamic,
            targets: ["CoreHello"]
        ),
    ],
    targets: [
        .systemLibrary(
            name: "CRadare2",
            path: "Sources/CRadare2",
            pkgConfig: "r_core",
            providers: [
                .apt(["libr2-dev"]),
                .brew(["radare2"])
            ]
        ),
        .target(
            name: "CoreHello",
            dependencies: ["CRadare2"],
            path: "Sources/CoreHello",
            linkerSettings: [
                .linkedLibrary("r_core"),
                .linkedLibrary("r_config"),
                .linkedLibrary("r_debug"),
                .linkedLibrary("r_bin"),
                .linkedLibrary("r_lang"),
                .linkedLibrary("r_anal"),
                .linkedLibrary("r_bp"),
                .linkedLibrary("r_egg"),
                .linkedLibrary("r_asm"),
                .linkedLibrary("r_arch"),
                .linkedLibrary("r_esil"),
                .linkedLibrary("r_flag"),
                .linkedLibrary("r_reg"),
                .linkedLibrary("r_search"),
                .linkedLibrary("r_syscall"),
                .linkedLibrary("r_fs"),
                .linkedLibrary("r_io"),
                .linkedLibrary("r_socket"),
                .linkedLibrary("r_cons"),
                .linkedLibrary("r_magic"),
                .linkedLibrary("r_muta"),
                .linkedLibrary("r_util"),
                .linkedLibrary("dl"),
            ]
        ),
    ]
)
