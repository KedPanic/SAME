SamBox = {
	dependencies = { "SamCommon", "SamRenderer", "SamSound", "SamInput", "SamEntitySystem", "LibSamExporter", "render", "audio", "input", "wxWidgets" }
}
		
project("SamBox")
	location("build/".._ACTION)
	kind "WindowedApp"
	language "C++"			
			
	local commonFlags = { "WinMain", "EnableSSE", "EnableSSE2", "unicode" }
			
	-- precompiled header
	pchheader("include/box/SamBoxPCH.h")
	pchsource("src/box/SamBoxPCH.cpp")
	
	-- set specific platform source folder.
	local platformRootFolder = "sam/platform/"
	if os.is("windows") == true then
		platformRootFolder = platformRootFolder.."win/"
	elseif os.is("linux") == true then
		platformRootFolder = platformRootFolder.."linux/"
	end
			
	-- include and library directories
	local includes = {}
	local libraries = {}
	local libraries_dir = {}
	for i, dep in pairs(SamBox.dependencies) do
		if dependencies[""..dep] ~= nil then
			table.insert(libraries, dependencies[""..dep].lib)
			--if type(dependencies[""..dep].include) ~= "array" then
				table.insert(includes, dependencies[""..dep].include)
			--[[else
				for index, include in pairs(dependencies[""..dep].include) do
					table.insert(includes, include)
				end
			end]]
		
			if dependencies[""..dep].libdir then
				table.insert(libraries_dir, dependencies[""..dep].libdir)
			end
		end
	end
	includedirs { "include/sam", "include/box", "include/"..platformRootFolder, includes }			
			
			
	------------------------------------------------------------
	-------------------------------------------------  ADD FILES
	-- create files patterns.
	local projectFiles = { "include/box/**.h", "src/box/**.cpp", "include/box/**.inl" }
			
	-- create virtual folder.
	vpaths {
		["**"] = projectFiles,
	}
						
	files {
		projectFiles,
	}
	------------------------------------------------------------
			
			
			
	------------------------------------------------------------
	--------------------------------------------  CONFIGURATIONS
	configuration "Debug"
		defines { DEBUG_DEF, "ENABLE_PROFILING" }
		flags { "Symbols", commonFlags }
		objdir("build/".._ACTION.."/obj/debug/SamBox")
		implibdir "bin/debug/"
		targetdir "bin/debug/"
		debugdir  "bin/debug/"
		libdirs { "lib/debug/", libraries_dir }
		links { "SamProfiling", libraries, "wxbase29ud", "wxbase29ud_xml", "wxexpatd", "wxjpegd", "wxmsw29ud_adv", "wxmsw29ud_aui", "wxmsw29ud_core", "wxmsw29ud_html", "wxmsw29ud_xrc", "wxpngd", "wxregexud", "wxzlibd", "wxtiffd", "rpcrt4", "comctl32" }
			
	configuration "Profile"
		defines { "NDEBUG", "ENABLE_PROFILING" }
		flags { "Symbols", commonFlags }
		objdir("build/".._ACTION.."/obj/profile/SamBox")
		implibdir "bin/profile/"
		targetdir "bin/profile/"
		debugdir  "bin/profile/"
		libdirs { "lib/profile/", libraries_dir }
		links { "SamProfiling", libraries, "wxbase29u", "wxexpat", "wxregexu", "wxzlib", "wxpng", "wxjpeg", "wxtiff", "wxmsw29u_aui", "wxbase29u", "wxmsw29u_core", "rpcrt4", "comctl32" }
				
	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize", "FatalWarnings", commonFlags }
		objdir("build/".._ACTION.."/obj/release/SamBox")
		implibdir "bin/release/"
		targetdir "bin/release/"
		debugdir  "bin/release/"
		libdirs { "lib/release/", libraries_dir }
		links { libraries, "wxbase29u", "wxexpat", "wxregexu", "wxzlib", "wxpng", "wxjpeg", "wxtiff", "wxmsw29u_aui", "wxbase29u", "wxmsw29u_core", "rpcrt4", "comctl32" }