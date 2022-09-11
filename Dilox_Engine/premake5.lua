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
IncludeDir["glm"] = "Engine/libs/glm"

include "Engine/libs/glfw"
include "Engine/libs/glad"
include "Engine/libs/imgui"

project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    pchheader "dgepch.h"
    pchsource "Engine/src/dgepch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/libs/glm/glm/**.hpp",
        "%{prj.name}/libs/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/libs/spdlog/include",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "glfw",
        "glad",
        "imgui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "DGE_PLATFORM_WINDOWS",
            "DGE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "DGE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "DGE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "DGE_DIST"
        runtime "Release"
        optimize "on"

project "Game"
        location "Game"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++latest"
        staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Engine/libs/spdlog/include",
        "Engine/src",
        "Engine/libs",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Engine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "DGE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "DGE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "DGE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "DGE_DIST"
        runtime "Release"
        optimize "on"