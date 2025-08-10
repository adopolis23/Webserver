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
    includedirs { "src" }

    filter "configurations:Debug"
    symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter "system:windows"
        defines { "PLATFORM_WINDOWS" }

    filter "system:linux"
        defines { "PLATFORM_LINUX" }