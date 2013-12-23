local sample_project_files = os.matchfiles("**premake4.lua")
table.remove(sample_project_files, 1)

samples = {}
for index, sampleProject in pairs(sample_project_files) do	
	dofile(sampleProject)
end

for index, sample in pairs(samples) do
	sample.folder = path.getdirectory(sample_project_files[index])
	sample.name = path.getbasename(sample.folder)
end

for folder, sample in pairs(samples) do
	group("samples/"..sample.group)
		project(sample.name)
			local folder = sample.folder
			location(folder)
			kind(sample.kind)
			language "C++"			
					
			local commonFlags = { "WinMain", "EnableSSE", "EnableSSE2" }
			
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
			for i, dep in pairs(sample.dependencies) do
				if dependencies[""..dep] ~= nil then
					table.insert(libraries, dependencies[""..dep].lib)
					table.insert(includes, dependencies[""..dep].include)
				
					if dependencies[""..dep].libdir then
						table.insert(libraries_dir, dependencies[""..dep].libdir)
					end
				end
			end
			includedirs { "../include/sam", "../include/"..platformRootFolder, includes, folder.."/../../sampleapp/" }	
			
			-- create virtual folder.
			local filePattern = { folder.."**.h", folder.."**.cpp", folder.."/readme.txt" }
			local commonPattern = { folder.."/../../sampleapp/**.h", folder.."/../../sampleapp/**.cpp" }
			vpaths {
				["**"] = filePattern,
				["sampleapp/**"] = commonPattern
			}
								
			files { 
				filePattern,
				commonPattern
			}
			
			------------------------------------------------------------
			--------------------------------------------  CONFIGURATIONS
			configuration "Debug"
				defines { DEBUG_DEF, "ENABLE_PROFILING", sample.defines }
				flags { "Symbols", commonFlags }
				objdir(folder.."/obj/debug/")
				implibdir "../bin/debug/"
				targetdir "../bin/debug/"			
				debugdir  "../bin/debug/"
				libdirs { "../lib/debug/", libraries_dir }
				links { "SamProfiling", libraries }
				
			configuration "Profile"
				defines { "NDEBUG", "ENABLE_PROFILING", sample.defines }
				flags { "Symbols", commonFlags }
				objdir(folder.."/obj/profile/")
				implibdir "../bin/profile/"
				targetdir "../bin/profile/"
				debugdir  "../bin/profile/"
				libdirs { "../lib/profile/", libraries_dir }
				links { "SamProfiling", libraries }
				
			configuration "Release"
				defines { "NDEBUG", sample.defines }
				flags { "Optimize", "FatalWarnings", commonFlags }
				objdir(folder.."/obj/release/")
				implibdir "../bin/release/"
				targetdir "../bin/release/"
				debugdir  "../bin/release/"
				libdirs { "../lib/release/", libraries_dir }
				links { libraries }
			------------------------------------------------------------	
end
