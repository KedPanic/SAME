        -- libjpeg platform specific configuration
        if os.is("windows") == true then            
            os.copyfile("Source/LibJPEG/jconfig.vc", "Source/LibJPEG/jconfig.h")
        elseif os.is("linux") == true then
            os.copyfile("Source/LibJPEG/jconfig.linux", "Source/LibJPEG/jconfig.h")
        end
	
        local freeimageProjects = {
		libjpeg = {
			name = "LibJPEG",
			source = { "Source/LibJPEG/" },
			files = { "Source/LibJPEG/*.h", "Source/LibJPEG/*.c" },
			excludes = { 
				windows = { "Source/LibJPEG/jmemmac.c", "Source/LibJPEG/jmemdos.c", "Source/LibJPEG/jmemansi.c" },
                linux = { "Source/LibJPEG/jmemmac.c", "Source/LibJPEG/jmemdos.c", "Source/LibJPEG/jmemansi.c" },
			},
			language = "C",
			kind = "StaticLib",
			defines = { "_LIB", "_CRT_SECURE_NO_DEPRECATE" },
            buildoptions = {
                linux = { "-fPIC" }
            }
		},
		libopenjpeg = {
			name = "LibOpenJPEG",
			source = { "Source/LibOpenJPEG/" },
			files = { "Source/LibOpenJPEG/*.h", "Source/LibOpenJPEG/*.c" },
			language = "C",
			kind = "StaticLib",
			defines = { "_LIB", "_CRT_SECURE_NO_DEPRECATE", "OPJ_STATIC" },
            buildoptions = {
                linux = { "-fPIC" }
            }
		},
		libpng = {
			name = "LibPNG",
			source = { "Source/LibPNG/", "Source/ZLib/" },
			files = { "Source/LibPNG/*.h", "Source/LibPNG/*.c" },
			excludes = { "Source/LibPNG/example.c", "Source/LibPNG/pngtest.c" },
			language = "C",
			kind = "StaticLib",
			defines = { "_LIB", "_CRT_SECURE_NO_DEPRECATE" },
            buildoptions = {
                linux = { "-fPIC" }
            }
		},
		librawlite = {
			name = "LibRawLite",
			source = { "Source/LibRawLite/" },
			files = { "Source/LibRawLite/libraw/*.h", "Source/LibRawLite/src/*.cpp", "Source/LibRawLite/internal/*.h", "Source/LibRawLite/internal/*.cpp" },
			language = "C++",
			kind = "StaticLib",
			defines = { "_LIB", "_CRT_SECURE_NO_DEPRECATE", "LIBRAW_NODLL" },
            flags = {
                common = { "Unicode" },
            },
            buildoptions = {
                linux = { "-fPIC" }
            }
		},
		libtiff4 = {
			name = "LibTIFF4",
			source = { "Source/LibTIFF4/" },
			files = { "Source/LibTIFF4/*.h", "Source/LibTIFF4/*.c" },
			excludes = { 
				windows = { "Source/LibTIFF4/mkg3states.c", "Source/LibTIFF4/mkspans.c", "Source/LibTIFF4/tif_vms.c", "Source/LibTIFF4/tif_wince.c", "Source/LibTIFF4/tif_unix.c" },
                linux = { "Source/LibTIFF4/mkg3states.c", "Source/LibTIFF4/mkspans.c", "Source/LibTIFF4/tif_vms.c", "Source/LibTIFF4/tif_wince.c", "Source/LibTIFF4/tif_unix.c", "Source/LibTIFF4/tif_win32.c" },
			},
			language = "C",
			kind = "StaticLib",
			defines = { "_LIB", "_CRT_SECURE_NO_DEPRECATE" },
            buildoptions = {
                linux = { "-fPIC" }
            }
		},
		openexr = {
			name = "OpenEXR",
			source = { 
				"Source/OpenEXR/", 
				"Source/OpenEXR/Half/", 
				"Source/OpenEXR/Iex/", 
				"Source/OpenEXR/IlmImf/",
				"Source/OpenEXR/IlmThread/",
				"Source/OpenEXR/Imath/",
				"Source/ZLib/"
			},
			files = { 
				"Source/OpenEXR/IlmBaseConfig.h", 
				"Source/OpenEXR/Half/*.h", 
				"Source/OpenEXR/Half/*.cpp", 
				"Source/OpenEXR/Iex/*.h", 
				"Source/OpenEXR/Iex/*.cpp", 
				"Source/OpenEXR/IlmImf/*.h", 				
				"Source/OpenEXR/IlmImf/*.cpp",
				"Source/OpenEXR/IlmThread/*.h",				
				"Source/OpenEXR/IlmThread/*.cpp",
				"Source/OpenEXR/Imath/*.h",
				"Source/OpenEXR/Imath/*.cpp"
			},
			excludes = { 
				"Source/OpenEXR/Half/eLut.cpp", 
				"Source/OpenEXR/Half/toFloat.cpp",
				"Source/OpenEXR/IlmImf/b44ExpLogTable.cpp",
				"Source/OpenEXR/IlmImf/ImfAcesFile.cpp",
				"Source/OpenEXR/IlmImf/ImfAcesFile.h",
				"Source/OpenEXR/IlmThread/IlmThreadMutexPosix.cpp",				
				"Source/OpenEXR/IlmThread/IlmThreadMutexWin32.cpp",
				"Source/OpenEXR/IlmThread/IlmThreadSemaphorePosix.cpp",
				"Source/OpenEXR/IlmThread/IlmThreadSemaphorePosixCompat.cpp",
				"Source/OpenEXR/IlmThread/IlmThreadSemaphoreWin32.cpp",
				"Source/OpenEXR/IlmThread/IlmThreadWin32.cpp",
				"Source/OpenEXR/Imath/ImathFrustumTest.cpp",
				"Source/OpenEXR/Imath/ImathInt64.cpp",
			},
			language = "C++",
			kind = "StaticLib",
			defines = { "_LIB", "_CRT_SECURE_NO_DEPRECATE" },
            buildoptions = {
                linux = { "-fPIC" }
            }
		},
		zlib = {
			name = "ZLib",
			source = { "Source/ZLib/" },
			files = { "Source/ZLib/*.h", "Source/ZLib/*.c" },
			language = "C",
			kind = "StaticLib",
			defines = { "_LIB", "_CRT_SECURE_NO_DEPRECATE" },
            buildoptions = {
                linux = { "-fPIC" }
            }
		},
		freeimage = {
			name = "FreeImage",
			source = { 
				"Source/",
				"Source/DeprecationManager/",
				"Source/ZLib/",
				"Source/OpenEXR/Half/", 
				"Source/OpenEXR/Iex/", 
				"Source/OpenEXR/IlmImf/",
				"Source/OpenEXR/IlmThread/",
				"Source/OpenEXR/Imath/",
			},
			files = { "Source/*.h", "Source/FreeImage/*.h", "Source/FreeImage/*.c", "Source/FreeImage/*.cpp", "Source/FreeImageToolkit/*.h", "Source/FreeImageToolkit/*.cpp", "Source/Metadata/*.cpp", "Source/Metadata/*.h" },
			language = "C++",
			kind = "SharedLib",
			defines = { "_LIB", "_CRT_SECURE_NO_DEPRECATE", "FREEIMAGE_EXPORTS", "LIBRAW_NODLL", "OPJ_STATIC" },
			copy = true,
			libraries = { "LibJPEG", "LibOpenJPEG", "LibPNG", "LibRawLite", "LibTIFF4", "OpenEXR", "ZLib" }
		},
	}
	
	local freeimageRootPath = os.getcwd()
	dependencies["freeimage"] = {
		lib = "freeimage",
		include = { freeimageRootPath.."/Source/" }
	}
	
	for i, proj in pairs(freeimageProjects) do
		group("external/freeimage")
			project(proj.name)
				location("build")
				kind(proj.kind)
				language(proj.language)
                                
				-- platform defines
				if os.is("windows") then				
					if proj.copy == true then
						postbuildcommands { "copy \"$(TargetPath)\" \"$(TargetDir)\\..\\..\\bin\\$(Configuration)\\$(TargetFileName)\" /Y" }
					end
				end
						
				includedirs { proj.source }
				
				-- create virtual folder.
				vpaths {
					["**"] = { proj.files }
				}
									
				files { proj.files }
				
				-- excludes specific files
				if proj.excludes ~= nil then
					if os.is("windows") == true and proj.excludes.windows ~= nil then
						excludes { proj.excludes.windows }
					elseif os.is("linux") == true and proj.excludes.linux ~= nil then
                        excludes { proj.excludes.linux }
					else
						excludes { proj.excludes }
					end
				end

                -- flags
                local lFlags = {}
                if proj.flags ~= nil then
                    if os.is("windows") == true and proj.flags.windows ~= nil then
                        lFlags = proj.flags.windows
                    elseif os.is("linux") == true and proj.flags.linux ~= nil then
                        lFlags = proj.flags.linux
                    end

                    if proj.flags.common ~= nil then
                        for i, flag in pairs(proj.flags.common) do
                            table.insert(lFlags, flag)
                        end
                    end
                end

                -- buildoptions 
                local lBuildoptions = {}
                if proj.buildoptions ~= nil then
                    if os.is("windows") == true and proj.buildoptions.windows ~= nil then
                        lBuildoptions = proj.buildoptions.windows
                    elseif os.is("linux") == true and proj.buildoptions.linux ~= nil then
                        lBuildoptions = proj.buildoptions.linux
                    end

                    if proj.buildoptions.common ~= nil then
                        for i, option in pairs(proj.buildoptions.common) do
                            table.insert(lBuildoptions, option)
                        end
                    end
                end

				------------------------------------------------------------
				--------------------------------------------  CONFIGURATIONS
				configuration "Debug"
					defines { DEBUG_DEF, proj.defines, PLATFORM_DEF }
					flags { "Symbols", lFlags }
					objdir("build/obj/debug/")
					implibdir "../../lib/debug/"
					targetdir "../../lib/debug/"
					if proj.libraries ~= nil then
						links { proj.libraries }
					end
                    buildoptions { lBuildoptions }
							
				configuration "Profile"
					defines { "NDEBUG", proj.defines, PLATFORM_DEF }
					flags { "Symbols", lFlags }
					objdir("build/obj/profile/")
					implibdir "../../lib/profile/"
					targetdir "../../lib/profile/"
					if proj.libraries ~= nil then
						links { proj.libraries }
					end
                    buildoptions { lBuildoptions }
								
				configuration "Release"
					defines { "NDEBUG", proj.defines, PLATFORM_DEF }
					flags { "Optimize", "FatalWarnings", lFlags }
					objdir("build/obj/release/")
					implibdir "../../lib/release/"
					targetdir "../../lib/release/"
					if proj.libraries ~= nil then
						links { proj.libraries }
					end
                    buildoptions { lBuildoptions }
	end
