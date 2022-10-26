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
IncludeDir["stb_image"] = "Engine/libs/stb_image"

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
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/libs/stb_image/**.h",
        "%{prj.name}/libs/stb_image/**.cpp",
        "%{prj.name}/libs/glm/glm/**.hpp",
        "%{prj.name}/libs/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/libs/spdlog/include",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
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
            "DGE_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Game/\"")
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
        staticruntime "off"

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