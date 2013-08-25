SamExporter = {
	lib = {
		name = "LibSamExporter",
		kind = "StaticLib",
		pch = "SamExporter/lib/SamExporterPCH",
		includeDir = "SamExporter/lib/",
		targetDir = "lib",
		projectFiles = { "SamExporter/lib/**.h", "SamExporter/lib/**.cpp", "SamExporter/lib/**.inl" },
		dependencies = { "SamCommon", "SamRenderer", "SamSound", "SamInput", "SamEntitySystem", "render", "audio", "input" }
	},
	tool = {
		name = "SamExporter",
		kind = "WindowedApp",
		pch = "SamExporter/tool/SamExporterPCH",
		includeDir = "SamExporter/tool/",
		targetDir = "bin",
		projectFiles = { "SamExporter/tool/**.h", "SamExporter/tool/**.cpp", "SamExporter/tool/**.inl" },
		dependencies = { "SamCommon", "SamRenderer", "SamSound", "SamInput", "SamEntitySystem", "render", "audio", "input", "wxWidgets" }
	}
}

-- Create dependency information
dependencies["LibSamExporter"] = {
	lib = "LibSamExporter",
	include = os.getcwd().."\\"..SamExporter.lib.includeDir,
}

for i, proj in pairs(SamExporter) do			
	project(proj.name)
		location("../build/".._ACTION)
		kind(proj.kind)
		language "C++"			
				
		local commonFlags = { "WinMain", "EnableSSE", "EnableSSE2", "unicode" }
				
		-- precompiled header
		pchheader(proj.pch..".h")
		pchsource(proj.pch..".cpp")
		
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
		for i, dep in pairs(proj.dependencies) do
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
		includedirs { "../include/sam", "../include/"..platformRootFolder, proj.includeDir, includes }			
				
				
		------------------------------------------------------------
		-------------------------------------------------  ADD FILES			
		-- create virtual folder.
		vpaths {
			["**"] = proj.projectFiles,
		}
							
		files {
			proj.projectFiles,
		}
		------------------------------------------------------------
				
				
				
		------------------------------------------------------------
		--------------------------------------------  CONFIGURATIONS
		configuration "Debug"
			defines { DEBUG_DEF, "ENABLE_PROFILING" }
			flags { "Symbols", commonFlags }
			objdir("build/".._ACTION.."/obj/debug/"..proj.name)
			implibdir("../bin/"..proj.targetDir.."/debug/")
			targetdir("../"..proj.targetDir.."/debug/")
			debugdir  "../bin/debug/"
			libdirs { "../lib/debug/", libraries_dir }
			links { "SamProfiling", libraries, "wxbase29ud", "wxbase29ud_xml", "wxexpatd", "wxjpegd", "wxmsw29ud_adv", "wxmsw29ud_aui", "wxmsw29ud_core", "wxmsw29ud_html", "wxmsw29ud_xrc", "wxpngd", "wxregexud", "wxzlibd", "wxtiffd", "rpcrt4", "comctl32" }
				
		configuration "Profile"
			defines { "NDEBUG", "ENABLE_PROFILING" }
			flags { "Symbols", commonFlags }
			objdir("build/".._ACTION.."/obj/profile/"..proj.name)
			implibdir("../bin/"..proj.targetDir.."/profile/")
			targetdir("../"..proj.targetDir.."/profile/")
			debugdir  "../bin/profile/"
			libdirs { "../lib/profile/", libraries_dir }
			links { "SamProfiling", libraries, "wxbase29u", "wxexpat", "wxregexu", "wxzlib", "wxpng", "wxjpeg", "wxtiff", "wxmsw29u_aui", "wxbase29u", "wxmsw29u_core", "rpcrt4", "comctl32" }
					
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize", "FatalWarnings", commonFlags }
			objdir("../build/".._ACTION.."/obj/release/"..proj.name)
			implibdir("../bin/"..proj.targetDir.."/release/")
			targetdir("../"..proj.targetDir.."/release/")
			debugdir  "../bin/release/"
			libdirs { "../lib/release/", libraries_dir }
			links { libraries, "wxbase29u", "wxexpat", "wxregexu", "wxzlib", "wxpng", "wxjpeg", "wxtiff", "wxmsw29u_aui", "wxbase29u", "wxmsw29u_core", "rpcrt4", "comctl32" }
end