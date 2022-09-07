workspace "Dilox_Engine"
    architecture "x86"
    startproject "Game"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["glfw"] = "Engine/libs/glfw/include"
IncludeDir["glad"] = "Engine/libs/glad/include"
IncludeDir["imgui"] = "Engine/libs/imgui"

include "Engine/libs/glfw"
include "Engine/libs/glad"
include "Engine/libs/imgui"

project "Engine"
    location "Engine"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    pchheader "dgepch.h"
    pchsource "Engine/src/dgepch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/libs/spdlog/include",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}"
    }

    links
    {
        "glfw",
        "glad",
        "imgui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++latest"
        staticruntime "off"
        systemversion "latest"

        defines
        {
            "DGE_PLATFORM_WINDOWS",
            "DGE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Game/\"")
        }

    filter "configurations:Debug"
        defines "DGE_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "DGE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "DGE_DIST"
        runtime "Release"
        optimize "On"

project "Game"
        location "Game"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++latest"
        staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Engine/libs/spdlog/include",
        "Engine/src"
    }

    links
    {
        "Engine"
    }

    filter "system:windows"
        cppdialect "C++latest"
        systemversion "latest"

        defines
        {
            "DGE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "DGE_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "DGE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "DGE_DIST"
        runtime "Release"
        optimize "On"