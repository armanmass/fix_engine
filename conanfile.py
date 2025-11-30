import os
from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import replace_in_file, load
from conan.errors import ConanException


class SetUp(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    options = { "sanitizer": ["asan", "tsan", "msan", "ubsan"] }
    default_options = { "sanitizer": "asan" }

    def validate(self):
        # verify user has kdb+ files
        kdb_files = ["vendor/kdb/k.h", "vendor/kdb/c.o"]
        missing = [f for f in kdb_files if not os.path.exists(f)]
        if missing:
            raise ConanException (
                f"Missing kdb+ files: {missing}\n"
                 "Download from: https://github.com/KxSystems/kdb"
                 "Extract k.h and c.o to vendor/kdb/"
            )

    def configure(self):
        # DEBUG
        if self.settings.build_type == "Debug":
            print("Configuring DEBUG build.")

            # ENABLE ALL WARNINGS
            warning_flags = [
                "-Wall", "-Wextra", "-Wpedantic", "-Wshadow", "-Wnon-virtual-dtor",
                "-Wcast-align", "-Wunused", "-Woverloaded-virtual","-Wdouble-promotion",
                "-Wconversion", "-Wmisleading-indentation", "-Wno-nullability-extension",
            ]

            # SELECT SANITIZER
            sanitizer_flags = []
            if self.options.sanitizer == "asan":
                sanitizer_flags = ["-fsanitize=address", "-fsanitize=leak"]
            elif self.options.sanitizer == "tsan":
                sanitizer_flags = ["-fsanitize=thread"]
            elif self.options.sanitizer == "msan":
                sanitizer_flags = ["-fsanitize=memory"]
            elif self.options.sanitizer == "ubsan":
                sanitizer_flags = ["-fsanitize=undefined"]

            debug_flags = warning_flags + sanitizer_flags
            debug_flags.extend(["-Og", "-g", "-fno-omit-frame-pointer"])
        
            if self.settings.compiler in ["clang", "gcc"]:
                self.conf.define("tools.build:cxxflags", debug_flags)
                self.conf.define("tools.build:cflags", debug_flags)
                if sanitizer_flags:
                    self.conf.define("tools.build:sharedlinkflags", sanitizer_flags)
                    self.conf.define("tools.build:exelinkflags", sanitizer_flags)

        # RELEASE
        elif self.settings.build_type == "Release":
            print("Configuring RELEASE build.")
            if self.settings.compiler in ["gcc"]:
                release_flags = ["-O3", "-DNDEBUG", "-march=native"]
                self.conf.define("tools.build:cflags", release_flags)
                self.conf.define("tools.build:cxxflags", release_flags)
    
    
    def requirements(self):
        self.requires("quickfix/1.15.1")
        self.requires("grpc/1.72.0")

    
    def generate(self):
        for dep in self.dependencies.values():
            if dep.ref.name == "quickfix":
                utility_h_path = os.path.join(dep.package_folder, "include", "quickfix", "Utility.h")
                if "std::unique_ptr" not in load(self, utility_h_path):
                    replace_in_file(self, utility_h_path, "#define SmartPtr std::auto_ptr", "#include <memory>\n#define SmartPtr std::unique_ptr")

        cmake = CMakeToolchain(self)
        cmake.generator = "Ninja"
        cmake.variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = "ON"
        cmake.generate()

        deps = CMakeDeps(self)
        deps.generate()
        

    def layout(self):
        cmake_layout(self)
