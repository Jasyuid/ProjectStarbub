workspace "ProjectStarbud"
	architecture "x86"
	startproject "Starbud"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Starbud"
	location "Starbud"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/SFML/include"
	}

	libdirs
	{
		"%{prj.name}/vendor/SFML/lib"
	}

	links
	{
		"flac.lib",
		"freetype.lib",
		"jpeg.lib",
		"ogg.lib",
		"openal32.lib",
		"vorbis.lib",
		"vorbisfile.lib",
		"opengl32.lib",
		"winmm.lib",
		"gdi32.lib",
		"ws2_32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"GAME_PLATFORM_WINDOWS",
			"SFML_STATIC"
		}

	filter "configurations:Debug"
		defines "GAME_DEBUG"
		runtime "Debug"
		symbols "On"

		links
		{
			"sfml-audio-s-d.lib",
			"sfml-graphics-s-d.lib",
			"sfml-network-s-d.lib",
			"sfml-system-s-d.lib",
			"sfml-window-s-d.lib"
		}

	filter "configurations:Release"
		defines "CB_RELEASE"
		runtime "Release"
		optimize "On"

		links
		{
			"sfml-audio-s.lib",
			"sfml-graphics-s.lib",
			"sfml-network-s.lib",
			"sfml-system-s.lib",
			"sfml-window-s.lib"
		}
