	location("build/".._ACTION)
	local SamProjects = { 
		SamProfiling = {
			name = "SamProfiling",
			subfolder = "profiling",
			dependencies = {}
		},
		SamCommon = {
			name = "SamCommon",
			subfolder = "common",
			dependencies = { "cJSON", "tinyxml2" }
		},
		SamRenderer = {
			name = "SamRenderer",
			subfolder = "renderer",
			dependencies = { "SamCommon", "render" }
		},
		SamSound = {
			name = "SamSound",
			subfolder = "sound",
			dependencies = { "SamCommon", "audio" }
		},
		SamInput = {
			name = "SamInput",
			subfolder = "input",
			dependencies = { "SamCommon", "input" }
		},
		SamEntitySystem = {
			name = "SamEntitySystem",
			subfolder = "entitysystem",
			dependencies = { "SamCommon", "SamRenderer", "SamSound", "SamInput" }
		}, 
		SamFramework = {
			name = "SamFramework",
			subfolder = "framework",
			dependencies = { "SamCommon", "SamRenderer", "SamSound", "SamInput", "SamEntitySystem", "render", "audio", "input" }
		},		
	}	
	-- create dependencies informations.
	for index, proj in pairs(SamProjects) do
		dependencies[proj.name] = {
			lib = proj.name,
			include = "",
		}
	end
	
	for index, proj in pairs(SamProjects) do
		project(proj.name)
			location("build/".._ACTION)
			kind "SharedLib"
			language "C++"			
			
			local commonFlags = { "EnableSSE", "EnableSSE2", "NoExceptions" }
			
			-- local useful variables.
			local lowerName = proj.subfolder
			local upperName = string.upper(proj.subfolder)
			local folder = "sam/"..lowerName.."/"
			local platformFolder = "sam/platform/"
			local platformRootFolder = "sam/platform/"
			
			-- precompiled header
			pchheader("include/"..folder..proj.name.."PCH.h")
			pchsource("src/"..folder..proj.name.."PCH.cpp")
			
			-- set specific platform source folder.
			if os.is("windows") == true then
				platformFolder = platformFolder.."win/"..lowerName.."/"
				platformRootFolder = platformRootFolder.."win/"
			elseif os.is("linux") == true then
				platformFolder = platformFolder.."linux/"..lowerName.."/"
				platformRootFolder = platformRootFolder.."linux/"
			end
			
			-- include and library directories
			local includes = {}
			local libraries = {}
			local libraries_dir = {}
			for i, dep in pairs(proj.dependencies) do
				if dependencies[""..dep] ~= nil then
					table.insert(libraries, dependencies[""..dep].lib)
					table.insert(includes, dependencies[""..dep].include)
				
					if dependencies[""..dep].libdir then
						table.insert(libraries_dir, dependencies[""..dep].libdir)
					end
				end
			end
			includedirs { "include/sam", "include/"..folder, "include/"..platformRootFolder, includes }			
			
			
			------------------------------------------------------------
			-------------------------------------------------  ADD FILES
			-- create files patterns.
			local projectFiles = { "include/sam/"..proj.name..".h", "include/"..folder.."**.h", "src/"..folder.."**.cpp", "include/"..folder.."**.inl" }
			local platformFiles = { "include/"..platformFolder.."**.h", "src/"..platformFolder.."**.cpp", "include/"..platformFolder.."**.inl" }
			
			-- create virtual folder.
			vpaths {
				["**"] = projectFiles,
				["platform/**"] = platformFiles
			}
						
			files {
				projectFiles,
				platformFiles
			}
			------------------------------------------------------------
			
			
			
			------------------------------------------------------------
			--------------------------------------------  CONFIGURATIONS
			configuration "Debug"
				defines { "DEBUG", "ENABLE_PROFILING", "SAM_"..upperName.."_EXPORTS" }
				flags { "Symbols", commonFlags }
				objdir("build/".._ACTION.."/obj/debug/"..proj.name)
				implibdir "lib/debug/"
				targetdir "lib/debug/"			
				libdirs { "lib/debug/", libraries_dir }
				if index ~= "SamProfiling" then
					links { "SamProfiling", libraries }
				else
					links { libraries }
				end
				
			configuration "Profile"
				defines { "NDEBUG", "ENABLE_PROFILING" }
				flags { "Symbols", commonFlags }
				objdir("build/".._ACTION.."/obj/profile/"..proj.name)
				implibdir "lib/profile/"
				targetdir "lib/profile/"
				libdirs { "lib/profile/", libraries_dir }
				if index ~= "SamProfiling" then
					links { libraries }
				else
					links { libraries }
				end
				
			configuration "Release"
				defines { "NDEBUG" }
				flags { "Optimize", "FatalWarnings", commonFlags }
				objdir("build/".._ACTION.."/obj/release/"..proj.name)
				implibdir "lib/release/"
				targetdir "lib/release/"
				libdirs { "lib/release/", libraries_dir }
				links { libraries }
			------------------------------------------------------------	
	end
