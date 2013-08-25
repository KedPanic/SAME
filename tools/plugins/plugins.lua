local plugins_project_files = os.matchfiles("**premake4.lua")

plugins = {}
for index, pluginProject in pairs(plugins_project_files) do	
	print("found"..pluginProject)
	include(pluginProject)
end

for index, plugin in pairs(plugins) do
	plugin.folder = path.getdirectory(plugins_project_files[index])
	plugin.name = path.getbasename(plugin.folder)
end

for index, plugin in pairs(plugins) do
	group("plugins/"..plugin.group)
		project(plugin.name)
			location("../../build/".._ACTION)
			kind(plugin.kind)
			language "C++"			
		
			local folder = plugin.folder
			local commonFlags = { "EnableSSE", "EnableSSE2" }
			
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
			for i, dep in pairs(plugin.dependencies) do
				if dependencies[""..dep] ~= nil then
					table.insert(libraries, dependencies[""..dep].lib)
					table.insert(includes, dependencies[""..dep].include)
				
					if dependencies[""..dep].libdir then
						table.insert(libraries_dir, dependencies[""..dep].libdir)
					end
				end
			end
			includedirs { "../../include/sam", "../../include/"..platformRootFolder, includes }	
			
			-- create virtual folder.
			local filePattern = { folder.."**.h", folder.."**.inl", folder.."**.cpp" }
			vpaths {
				["**"] = filePattern,
			}
								
			files { 
				filePattern,
			}
			
			------------------------------------------------------------
			--------------------------------------------  CONFIGURATIONS
			configuration "Debug"
				defines { DEBUG_DEF, "ENABLE_PROFILING", plugin.defines }
				flags { "Symbols", commonFlags }
				objdir("../../build/".._ACTION.."/obj/debug/"..plugin.name)
				implibdir "../../bin/debug/"
				targetdir "../../bin/debug/"			
				debugdir  "../../bin/debug/"
				libdirs { "../../lib/debug/", libraries_dir }
				links { "SamProfiling", libraries }
				
			configuration "Profile"
				defines { "NDEBUG", "ENABLE_PROFILING", plugin.defines }
				flags { "Symbols", commonFlags }
				objdir("../../build/".._ACTION.."/obj/profile/"..plugin.name)
				implibdir "../../bin/profile/"
				targetdir "../../bin/profile/"
				debugdir  "../../bin/profile/"
				libdirs { "../../lib/profile/", libraries_dir }
				links { "SamProfiling", libraries }
				
			configuration "Release"
				defines { "NDEBUG", plugin.defines }
				flags { "Optimize", "FatalWarnings", commonFlags }
				objdir("../../build/".._ACTION.."/obj/release/"..plugin.name)
				implibdir "../../bin/release/"
				targetdir "../../bin/release/"
				debugdir  "../../bin/release/"
				libdirs { "../../lib/release/", libraries_dir }
				links { libraries }
			------------------------------------------------------------	
end
