from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain, cmake_layout


class SetUp(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    options = { "sanitizer": ["asan", "tsan", "msan", "ubsan"] }
    default_options = { "sanitizer": "asan" }

    def configure(self):
        # DEBUG
        if self.settings.build_type == "Debug":
            print("Configuring DEBUG build.")

            # ENABLE ALL WARNINGS
            warning_flags = [
                "-Wall", "-Wextra", "-Wpedantic", "-Wshadow", "-Wnon-virtual-dtor",
                "-Wcast-align", "-Wunused", "-Woverloaded-virtual","-Wdouble-promotion",
                "-Wconversion", "-Wmisleading-indentation",
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

    
    def generate(self):
        cmake = CMakeToolchain(self)
        cmake.generator = "Ninja"
        if self.settings.compiler.cppstd:
            cmake.variables["CMAKE_CXX_STANDARD"] = str(self.settings.compiler.cppstd)
            cmake.variables["CMAKE_CXX_STANDARD_REQUIRED"] = "ON"
        cmake.generate()

        deps = CMakeDeps(self)
        deps.generate()
        

    def layout(self):
        cmake_layout(self)