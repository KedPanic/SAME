local plugin = {
	kind = "SharedLib",
	group = "exporter",
	dependencies = { "SamCommon", "SamRenderer", "LibSamExporter" }
}
table.insert(plugins, plugin)