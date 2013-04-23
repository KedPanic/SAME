	dependencies["tinyxml2"] = {
		lib = "tinyxml2",
		include = os.getcwd(),
	}
	
	project "tinyxml2"
		location("")
		kind "StaticLib"
		language "C++"	
				
		-- create virtual folder.
		vpaths {
			["**"] = { "**.h", "**.cpp" }
		}
							
		files { "**.h", "**.cpp" }
		
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

