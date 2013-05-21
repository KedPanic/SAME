local sample_project_files = {
	"renderer/1_basic/premake4.lua",
}

samples = {}
for _, project in pairs(sample_project_files) do
	include(project)
end

for folder, sample in pairs(samples) do
	group("samples/"..sample.group)
		project(sample.name)
			location(folder)
			kind "WindowedApp"
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
			includedirs { "../include/sam", "../include/"..platformRootFolder, includes }	
			
			-- create virtual folder.
			vpaths {
				["**"] = { "**.h", "**.cpp" }
			}
								
			files { "**.h", "**.cpp" }
			
			------------------------------------------------------------
			--------------------------------------------  CONFIGURATIONS
			configuration "Debug"
				defines { DEBUG_DEF, "ENABLE_PROFILING" }
				flags { "Symbols", commonFlags }
				objdir(folder.."/obj/debug/")
				implibdir "../bin/debug/"
				targetdir "../bin/debug/"			
				libdirs { "../lib/debug/", libraries_dir }
				links { libraries }
				
			configuration "Profile"
				defines { "NDEBUG", "ENABLE_PROFILING" }
				flags { "Symbols", commonFlags }
				objdir(folder.."/obj/profile/")
				implibdir "../bin/profile/"
				targetdir "../bin/profile/"
				libdirs { "../lib/profile/", libraries_dir }
				links { libraries }
				
			configuration "Release"
				defines { "NDEBUG" }
				flags { "Optimize", "FatalWarnings", commonFlags }
				objdir(folder.."/obj/release/")
				implibdir "../bin/release/"
				targetdir "../bin/release/"
				libdirs { "../lib/release/", libraries_dir }
				links { libraries }
			------------------------------------------------------------	
end
