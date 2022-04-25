-- TODO: fix building on other projects

workspace "2DEngine"
    configurations {"Debug", "Release"}
    architecture "x86_64"

idirs = {}
ldirs = {}

idirs["raylib-mingw"] = "_raylib-mingw/include"
ldirs["raylib-mingw"] = "_raylib-mingw/lib"

project "2DEngine"
    kind "StaticLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}/%{prj.name}"

    idirs["2DEngine"] = "./2DEngine/include"
    includedirs {"./2DEngine/include"}

    files {"./2DEngine/include/**.h", "./2DEngine/include/**.hpp", "./2DEngine/src/**.c", "./2DEngine/src/**.cpp"}

    filter {"system:linux", "action:gmake2"}
        links {"raylib", "GL", "m", "pthread", "dl", "rt", "X11"}

    filter {"system:windows", "action:gmake2"}
        links {"raylib", "opengl32", "gdi32", "winmm"}
        libdirs {ldirs["raylib-mingw"]}
        includedirs {idirs["raylib-mingw"]}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "Linux-Jam-2022"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
    
    includedirs {"./Linux-Jam-2022/include", idirs["2DEngine"]}

    files {"./Linux-Jam-2022/include/**.h", "./Linux-Jam-2022/include/**.hpp", "./Linux-Jam-2022/src/**.c", "./Linux-Jam-2022/src/**.cpp"}

    links {"2DEngine", "raylib", "GL", "m", "pthread", "dl", "rt", "X11"}

    postbuildcommands {
        "{MKDIR} bin/%{cfg.buildcfg}/%{prj.name}/data",
        "{COPYDIR} data/global bin/%{cfg.buildcfg}/%{prj.name}/data/global", -- global data
        "{COPYDIR} data/%{prj.name} bin/%{cfg.buildcfg}/%{prj.name}/data" -- local data
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "Sandbox"
        kind "ConsoleApp"
        language "C++"
        targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
        staticruntime "On"
        
        includedirs {"./Sandbox/include", idirs["2DEngine"]}
    
        files {"./Sandbox/include/**.h", "./Sandbox/include/**.hpp", "./Sandbox/src/**.c", "./Sandbox/src/**.cpp"}
    
        -- For some reason Sandbox also needs to link to raylib, which may cause issues when it comes to multiple apis
        links {"2DEngine", "raylib", "GL", "m", "pthread", "dl", "rt", "X11"}
    
        postbuildcommands {
            "{MKDIR} bin/%{cfg.buildcfg}/%{prj.name}/data",
            "{COPYDIR} data/global bin/%{cfg.buildcfg}/%{prj.name}/data/global", -- global data
            "{COPYDIR} data/%{prj.name} bin/%{cfg.buildcfg}/%{prj.name}/data" -- local data
        }
    
        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
    
        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"

project "FlappyBird"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
    
    includedirs {"./%{prj.name}/include", idirs["2DEngine"]}

    files {"./%{prj.name}/include/**.h", "./%{prj.name}/include/**.hpp", "./%{prj.name}/src/**.c", "./%{prj.name}/src/**.cpp"}

    links {"2DEngine", "raylib", "GL", "m", "pthread", "dl", "rt", "X11"}

    filter { "system:linux", "action:gmake2" }
        linkoptions { "-no-pie" }

    postbuildcommands {
        "{MKDIR} bin/%{cfg.buildcfg}/%{prj.name}/data",
        "{COPYDIR} data/global bin/%{cfg.buildcfg}/%{prj.name}/data/global", -- global data
        "{COPYDIR} data/%{prj.name} bin/%{cfg.buildcfg}/%{prj.name}/data" -- local data
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "Pong"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
    
    includedirs {"./%{prj.name}/include", idirs["2DEngine"]}

    files {"./%{prj.name}/include/**.h", "./%{prj.name}/include/**.hpp", "./%{prj.name}/src/**.c", "./%{prj.name}/src/**.cpp"}

    links {"2DEngine", "raylib", "GL", "m", "pthread", "dl", "rt", "X11"}

    filter {"system:linux", "action:gmake2"}
        links {"2DEngine", "raylib", "GL", "m", "pthread", "dl", "rt", "X11"}
        linkoptions { "-no-pie" }

    filter {"system:windows", "action:gmake2"}
        links {"2DEngine", "raylib", "opengl32", "gdi32", "winmm"}
        libdirs {ldirs["raylib-mingw"]}
        includedirs {idirs["raylib-mingw"]}

    filter {}
        
    postbuildcommands {
        "{MKDIR} bin/%{cfg.buildcfg}/%{prj.name}/data",
        "{COPYDIR} data/global bin/%{cfg.buildcfg}/%{prj.name}/data/global", -- global data
        "{COPYDIR} data/%{prj.name} bin/%{cfg.buildcfg}/%{prj.name}/data" -- local data
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
