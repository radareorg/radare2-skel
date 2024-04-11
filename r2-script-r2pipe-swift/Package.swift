// swift-tools-version: 5.10
import PackageDescription

let pacakge = Package(
        name: "r2pipe-example",
        products: [
             .executable(name: "r2pipeExample", targets: ["r2pipeExample"]),
        ],
        dependencies: [
                .package(
                    url: "https://github.com/radareorg/radare2-r2pipe", revision: "1.0.5"
                ),
        ],
        targets: [
            .executableTarget(
                name: "r2pipeExample",
                dependencies: [
                    .product(name: "r2pipe", package: "radare2-r2pipe")
                ],
                swiftSettings: [
                    .define("USE_CCALL")
                ]
            )
        ]
)
