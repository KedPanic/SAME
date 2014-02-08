	location("build/".._ACTION)
	local SceneManagerProjects = { 
		GenericSceneManager = {
			name = "GenericSceneManager",
			subfolder = "generic",
			dependencies = { "SamCommon", "SamRenderer", "SamSound", "SamInput", "SamEntitySystem", "render", "audio", "input" }
		},		
	}	
	-- create dependencies informations.
	for index, proj in pairs(SceneManagerProjects) do
		dependencies[proj.name] = {
			lib = proj.name,
			include = "",
		}
	end
	
	for index, proj in pairs(SceneManagerProjects) do
		project(proj.name)
			location("build/".._ACTION)
			kind "SharedLib"
			language "C++"				
			
			local commonFlags = { "EnableSSE", "EnableSSE2", "NoExceptions" }
			
			-- local useful variables.
			local lowerName = proj.subfolder
			local upperName = string.upper(proj.subfolder)
			local folder = "scenemanagers/"..lowerName.."/"
			local platformFolder = "sam/platform/"
			local platformRootFolder = "sam/platform/"
			
			-- precompiled header
            if os.is("linux") == true then
    			pchheader("../../"..folder..proj.name.."PCH.h")
            else
                pchheader(folder..proj.name.."PCH.h")
            end
			pchsource(folder..proj.name.."PCH.cpp")
			
			-- set specific platform source folder.
			if os.is("windows") == true then
				platformFolder = platformFolder.."win/"..lowerName.."/"
				platformRootFolder = platformRootFolder.."win/"
				
				postbuildcommands { "copy \"$(TargetPath)\" \"$(TargetDir)\\..\\..\\bin\\$(Configuration)\\plugins\\$(TargetFileName)\" /Y" }
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
			includedirs { "include/sam", folder, "include/"..platformRootFolder, includes }			
			
			
			------------------------------------------------------------
			-------------------------------------------------  ADD FILES
			-- create files patterns.
			local projectFiles = { folder.."**.h", folder.."**.cpp", folder.."**.inl" }
			
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
				defines { DEBUG_DEF, "ENABLE_PROFILING", "SAM_"..upperName.."_EXPORTS" }
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
				defines { "NDEBUG", "ENABLE_PROFILING", "SAM_"..upperName.."_EXPORTS" }
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
				defines { "NDEBUG", "SAM_"..upperName.."_EXPORTS" }
				flags { "Optimize", "FatalWarnings", commonFlags }
				objdir("build/".._ACTION.."/obj/release/"..proj.name)
				implibdir "lib/release/"
				targetdir "lib/release/"
				libdirs { "lib/release/", libraries_dir }
				links { libraries }
			------------------------------------------------------------	
	end
