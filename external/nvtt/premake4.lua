	local nvttProjects = {
		nvcore = {
			name = "nvcore",
			include = { "src", "extern/poshlib"  },
			files = { "src/nvcore/*.inl", "src/nvcore/*.h", "src/nvcore/*.cpp" },
			excludes = { },
			defines = { "NVTT_EXPORTS", "__SSE2__", "__SSE__", "__MMX__" },
		},
		nvmath = {
			name = "nvmath",
			include = { "src", "extern/poshlib"  },
			files = { "src/nvmath/*.inl", "src/nvmath/*.h", "src/nvmath/*.cpp" },
			excludes = { },
			defines = { "NVTT_EXPORTS", "__SSE2__", "__SSE__", "__MMX__" },
		},
		nvthread = {
			name = "nvthread",
			include = { "src", "extern/poshlib"  },
			files = { "src/nvthread/*.inl", "src/nvthread/*.h", "src/nvthread/*.cpp" },
			excludes = { },
			defines = { "NVTT_EXPORTS", "__SSE2__", "__SSE__", "__MMX__" },
		},
		nvimage = {
			name = "nvimage",
			include = { "src", "extern/poshlib"  },
			files = { "src/nvimage/*.h", "src/nvimage/*.cpp" },
			excludes = { "src/nvimage/KtxFile.h", "src/nvimage/KtxFile.cpp" },
			defines = { "NVTT_EXPORTS", "__SSE2__", "__SSE__", "__MMX__" },
			libraries = { "nvcore", "nvmath" },
		},
		squish = {
			name = "squish",
			include = { },
			files = { 
				"src/nvtt/squish/colourblock.h", 				
				"src/nvtt/squish/colourblock.cpp",
				"src/nvtt/squish/colourfit.h", 
				"src/nvtt/squish/colourfit.cpp",
				"src/nvtt/squish/colourset.h", 
				"src/nvtt/squish/colourset.cpp",
				"src/nvtt/squish/maths.h", 
				"src/nvtt/squish/maths.cpp",
				"src/nvtt/squish/simd.h", 
				"src/nvtt/squish/simd_sse.h", 
				"src/nvtt/squish/simd_ve.h", 
				"src/nvtt/squish/weightedclusterfit.h", 
				"src/nvtt/squish/weightedclusterfit.cpp",
			},
			excludes = { },
			defines = { "NVTT_EXPORTS", "__SSE2__", "__SSE__", "__MMX__" },
		},
		nvtt = {
			name = "nvtt",
			include = { "src", "extern/poshlib" },
			files = { "src/nvtt/*.h", "src/nvtt/*.cpp" },
			excludes = { "src/nvtt/CompressorDX11.h", "src/nvtt/CompressorDX11.cpp" },
			defines = { "NVTT_EXPORTS", "__SSE2__", "__SSE__", "__MMX__" },
			libraries = { "nvimage" },
		},
	}
	
	local nvttRootPath = os.getcwd()
	dependencies["nvtt"] = {
		lib = { "squish", "nvcore", "nvmath", "nvthread", "nvimage", "nvtt" },
		include = { nvttRootPath.."/src/" }
	}
	
	for i, proj in pairs(nvttProjects) do
		group("external/nvtt")
			project(proj.name)
				location("build")
				kind "StaticLib"
				language "C++"	
						
				includedirs { proj.include }
				
				-- platform defines
				local platformDefine = ""
				if os.is("windows") then
					platformDefine = { "WIN32", "_WINDOWS" }
				end
				
				-- create virtual folder.
				vpaths {
					["**"] = { proj.files }
				}
									
				files { proj.files }
				excludes { proj.excludes }
				
				------------------------------------------------------------
				--------------------------------------------  CONFIGURATIONS
				configuration "Debug"
					defines { "DEBUG", platformDefine, proj.defines }
					flags { "Symbols" }
					objdir("build/obj/debug/")
					implibdir "../../lib/debug/"
					targetdir "../../lib/debug/"	
					if proj.libraries ~= nil then
						links { proj.libraries }
					end					
							
				configuration "Profile"
					defines { "NDEBUG", platformDefine, proj.defines }
					flags { "Symbols" }
					objdir("build/obj/profile/")
					implibdir "../../lib/profile/"
					targetdir "../../lib/profile/"
					if proj.libraries ~= nil then
						links { proj.libraries }
					end					
					
				configuration "Release"
					defines { "NDEBUG", platformDefine, proj.defines }
					flags { "Optimize", "FatalWarnings" }
					objdir("build/obj/release/")
					implibdir "../../lib/release/"
					targetdir "../../lib/release/"
					if proj.libraries ~= nil then
						links { proj.libraries }
					end										
	end