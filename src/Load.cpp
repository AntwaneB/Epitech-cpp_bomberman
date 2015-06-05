#include "Core/Load.hh"

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

//		level = new Level(cfg);
		level = NULL;
		return (level);
	}
	catch (ConfigException const & e)
	{
		throw LoadException("File " + _filename + " not found");
	}
}