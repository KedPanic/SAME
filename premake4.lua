--[[ 
========================================================================
			SAM ENGINE PREMAKE CONFIGURATION FILE
========================================================================	
Copyright (C) 2013 Cedric Liaudet

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to
do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.			
]]--
solution "SamEngine"
	location("build/".._ACTION)
	--[[ 
		Debug: non optimized with debug information
		Profile: optimized with debug information
		Release: optimized without debug information
	]]--
	configurations { "Debug", "Profile", "Release" }
	
	--------------------------------------------------------------------
	---------------------------  CREATION EXTERNAL DEPENDENCIES PROJECTS
	dependencies = {}
	local dependencie_folder = {
		"external/cJSON/premake4.lua",
		"external/tinyxml2/premake4.lua",
	}
	
	group "external"
		for index, file in pairs(dependencie_folder) do
			include(file)
		end
	
	--------------------------------------------------------------------
	-------------------------------------- specific library per platform
	if os.is("windows") == true then
		dependencies["render"] = {
			lib = { "d3dx11", "d3dcompiler", "dxgi", "DxErr", "d3d11" },
			include = "$(DXSDK_DIR)/Include",
			libdir = "$(DXSDK_DIR)/Lib/x86",
		}
		
		dependencies["input"] = {
			lib = { "XInput", "dinput8", "dxguid" },
			include = "$(DXSDK_DIR)/Include",
			libdir = "$(DXSDK_DIR)/Lib/x86",
		}
		
		dependencies["audio"] = {
			lib = { "X3DAudio" },
			include = "$(DXSDK_DIR)/Include",
			libdir = "$(DXSDK_DIR)/Lib/x86",
		}
	end
	
	--------------------------------------------------------------------
	------------------------------------------  CREATION OF SAM PROJECTS
	group "engine"
		dofile("samengine.lua")
