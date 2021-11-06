workspace "cpp-design-patterns"
architecture "x64"
startproject "command_pattern1"

configurations
{
    "Debug","Release"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

-- setup for one project:
function create_project(name)
    project (name)
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    
    targetdir("bin/" .. outputdir)
    objdir("bin-int/ .. outputdir")
   
    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.hpp",
        "%{prj.name}/**.c",
        "%{prj.name}/**.cpp"
    }
    
    filter "system:windows"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"

    filter "configurations:Debug"
    symbols "On"
    filter "configurations:Release"
    optimize "On"
end

-- projects:
create_project("command_pattern1")
create_project("command_pattern2")
