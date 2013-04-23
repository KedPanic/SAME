	dependencies["cJSON"] = {
		lib = "cJSON",
		include = os.getcwd(),
	}
	
	project "cJSON"
		location("")
		kind "StaticLib"
		language "C++"	
				
		-- create virtual folder.
		vpaths {
			["**"] = { "**.h", "**.c" }
		}
							
		files { "**.h", "**.c" }
		
		------------------------------------------------------------
		--------------------------------------------  CONFIGURATIONS
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
			objdir("obj/debug/")
			implibdir "../../lib/debug/"
			targetdir "../../lib/debug/"		
					
		configuration "Profile"
			defines { "NDEBUG" }
			flags { "Symbols" }
			objdir("obj/profile/")
			implibdir "../../lib/profile/"
			targetdir "../../lib/profile/"
						
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize", "FatalWarnings" }
			objdir("obj/release/")
			implibdir "../../lib/release/"
			targetdir "../../lib/release/"

