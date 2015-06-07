#include "Core/Load.hh"
#include "Core/Save.hh"

Load::Load(const std::string filename) : _filename(filename)
{
}

Load::~Load()
{
}

Level*
Load::load(void) const
{
	Config	cfg;

	try
	{
		cfg.importFile(_filename);
		Level	*level;

		level = new Level(cfg);
		Save	save(level, "load.xml");
		save.save();
		return (level);
	}
	catch (ConfigException const & e)
	{
		throw LoadException("File " + _filename + " not found");
	}
}