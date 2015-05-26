/**
 * Copyright 2015 Antoine Buchser
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * 	 http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CONFIG_HPP
#define	CONFIG_HPP

#include <string>
#include <map>
#include <ostream>
#include "pugixml.hpp"

class Config
{
public:
	class Param
	{
	public:
		enum Status { MAP, VALUE };

	public:
		Param();
		Param(std::string const & value);
		Param(std::map<std::string, Param> const & map);

		operator bool () const;
		operator char () const;
		operator short () const;
		operator int () const;
		operator long () const;
		operator double () const;
		operator float () const;
		operator std::string () const;
		operator unsigned char () const;
		operator unsigned short () const;
		operator unsigned int () const;
		operator unsigned long () const;

		Param& operator = (bool);
		Param& operator = (char);
		Param& operator = (short);
		Param& operator = (int);
		Param& operator = (long);
		Param& operator = (double);
		Param& operator = (float);
		Param& operator = (std::string const &);
		Param& operator = (const char[]);

		bool operator == (bool);
		bool operator == (char);
		bool operator == (short);
		bool operator == (int);
		bool operator == (long);
		bool operator == (double);
		bool operator == (float);
		bool operator == (std::string const &);
		bool operator == (const char[]);
		bool operator != (bool);
		bool operator != (char);
		bool operator != (short);
		bool operator != (int);
		bool operator != (long);
		bool operator != (double);
		bool operator != (float);
		bool operator != (std::string const &);
		bool operator != (const char[]);
		bool operator <= (bool);
		bool operator <= (char);
		bool operator <= (short);
		bool operator <= (int);
		bool operator <= (long);
		bool operator <= (double);
		bool operator <= (float);
		bool operator < (bool);
		bool operator < (char);
		bool operator < (short);
		bool operator < (int);
		bool operator < (long);
		bool operator < (double);
		bool operator < (float);
		bool operator >= (bool);
		bool operator >= (char);
		bool operator >= (short);
		bool operator >= (int);
		bool operator >= (long);
		bool operator >= (double);
		bool operator >= (float);
		bool operator >= (std::string const &);
		bool operator >= (const char[]);
		bool operator > (bool);
		bool operator > (char);
		bool operator > (short);
		bool operator > (int);
		bool operator > (long);
		bool operator > (double);
		bool operator > (float);

		Param& operator [] (std::string const &);
		Param& operator [] (const char[]);
//		Param const & operator [] (std::string const &) const;
//		Param const & operator [] (const char[]) const;

		std::map<std::string, Param>::iterator			find(const std::string &);
		std::map<std::string, Param>::iterator			begin(void);
		std::map<std::string, Param>::iterator			end(void);

		std::map<std::string, Param>::const_iterator	find(const std::string &) const;
		std::map<std::string, Param>::const_iterator	begin(void) const;
		std::map<std::string, Param>::const_iterator	end(void) const;

		void											insert(std::map<std::string, Param>::value_type);

		bool											isEmpty(void) const;

		bool											hasChild(void) const;

		const std::string								toXML(void) const;

	private:

	private:
		Param::Status						_status;
		std::string							_value;
		std::map<std::string, Param>	_map;
	};

public:
	Config();
	Config& operator=(Config::Param const &);
	virtual ~Config();

	Config::Param&	operator [] (std::string const &);
	Config::Param&	operator [] (const char[]);
//	Config::Param const & operator [] (std::string const &) const;
//	Config::Param const & operator [] (const char[]) const;

	std::map<std::string, Param>::iterator	find(const std::string &);
	std::map<std::string, Param>::iterator	begin(void);
	std::map<std::string, Param>::iterator	end(void);

	std::map<std::string, Param>::const_iterator	find(const std::string &) const;
	std::map<std::string, Param>::const_iterator	begin(void) const;
	std::map<std::string, Param>::const_iterator	end(void) const;

	bool	isEmpty(void) const;

	const std::string	toXML(void) const;

	void	importFile(std::string const &);
	void	exportFile(std::string const &) const;

private:
	Config::Param	fillParams(pugi::xml_node, Config::Param, int);

private:
	Config::Param	_params;
};

std::ostream&	operator << (std::ostream &, const Config &);
std::ostream&	operator << (std::ostream &, const Config::Param &);

#endif	/* CONFIG_HPP */
