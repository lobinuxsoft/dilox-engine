workspace "Dilox_Engine"
    architecture "x86"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Engine"
    location "Engine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/libs/spdlog/include"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "DGE_PLATFORM_WINDOWS",
            "DGE_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
        }

    filter "configurations:Debug"
        defines "DGE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "DGE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "DGE_DIST"
        optimize "On"

project "Game"
        location "Game"
        kind "ConsoleApp"
        language "C++"

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
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "DGE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "DGE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "DGE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "DGE_DIST"
        optimize "On"