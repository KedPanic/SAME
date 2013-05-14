SamBox = {
	dependencies = { "SamCommon", "SamRenderer", "SamSound", "SamInput", "SamEntitySystem", "render", "audio", "input", "wxWidgets" }
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
			
			print(type(dependencies[""..dep].include))
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
		defines { DEBUG_FLAG, "ENABLE_PROFILING" }
		flags { "Symbols", commonFlags }
		objdir("build/".._ACTION.."/obj/debug/SamBox")
		implibdir "lib/debug/"
		targetdir "bin/debug/"			
		libdirs { "lib/debug/", libraries_dir }
		links { "SamProfiling", libraries, "wxbase29ud", "wxexpatd", "wxregexud", "wxzlibd", "wxpngd", "wxjpegd", "wxtiffd", "wxmsw29ud_aui", "wxbase29ud", "wxmsw29ud_core", "rpcrt4", "comctl32" }
			
	configuration "Profile"
		defines { "NDEBUG", "ENABLE_PROFILING" }
		flags { "Symbols", commonFlags }
		objdir("build/".._ACTION.."/obj/profile/SamBox")
		implibdir "lib/profile/"
		targetdir "bin/profile/"
		libdirs { "lib/profile/", libraries_dir }
		links { "SamProfiling", libraries, "wxbase29u", "wxexpat", "wxregexu", "wxzlib", "wxpng", "wxjpeg", "wxtiff", "wxmsw29u_aui", "wxbase29u", "wxmsw29u_core", "rpcrt4", "comctl32" }
				
	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize", "FatalWarnings", commonFlags }
		objdir("build/".._ACTION.."/obj/release/SamBox")
		implibdir "lib/release/"
		targetdir "bin/release/"
		libdirs { "lib/release/", libraries_dir }
		links { libraries }