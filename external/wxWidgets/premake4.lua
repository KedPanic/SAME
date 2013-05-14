	dependencies["wxWidgets"] = {
		lib = { },  
		include = { os.getcwd().."/include/" },
		libdir = os.getcwd().."/lib/"
	}

	if os.is("windows") == true then
		dependencies["wxWidgets"].libdir = dependencies["wxWidgets"].libdir.."/vc_lib/"
		table.insert(dependencies["wxWidgets"].include, dependencies["wxWidgets"].libdir.."/mswud")
	elseif os.is("linux") == true then
		dependencies["wxWidgets"].libdir = dependencies["wxWidgets"].libdir.."/gcc_lib/"
		table.insert(dependencies["wxWidgets"].include, dependencies["wxWidgets"].libdir.."/lib/gcc_lib/")
	end	
	
	