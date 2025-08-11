workspace "Webserver"
    configurations {"Debug", "Release"}
    architecture "x86_64"
    startproject "Webserver"

project "Webserver"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files { "src/**.cpp" }
    files { "src/**.h" }
    includedirs { "src" }


    externalincludedirs { "vendor/spdlog/include" }
    defines { "FMT_UNICODE=0" }

    filter "configurations:Debug"
    symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter "system:windows"
        links { "ws2_32" }
        defines { "PLATFORM_WINDOWS" }

    filter "system:linux"
        defines { "PLATFORM_LINUX" }