#include"Parser.hpp"

Parser::Parser(void)
{
	return ;
}

Parser::~Parser()
{
	return ;
}

//Add an argument to parse and specify the type as "int", "double" or "string".
void	Parser::addArgToParse(std::string argname, std::string type)
{
	if (type != "int" && type != "double" && type != "string")
		throw TypeErrorException(type);
	if (this->_data.find(argname) != this->_data.end())
		return ;
	std::vector<std::string>	sample;
	this->_data.emplace(argname, sample);
	this->_types.emplace(argname, type);
	return ;
}

static bool	isnumber(std::string str, bool isfloat)
{
	size_t len = str.size();

	if (std::count(str.begin(), str.end(), '.') > static_cast<int>(isfloat))
		return (false);
	for (size_t i = 0; i < len; i++)
	{
		if (!isdigit(str[i]))
		{
			if (i == 0 && str[i] != '-' && str[i] != '+')
				return (false);
			else if (i != 0 && str[i] != '.')
				return (false);
		}
	}
	return (true);
}

std::unordered_map<std::string, std::vector<std::string> > const	&Parser::parse(char **argv, int argc)
{
	std::string	to_parse;

	int i = 1;
	while (i < argc)
		to_parse += std::string(argv[i++]) + ' ';

	std::string	actual_arg;
	std::string	word;
	for (char &c: to_parse)
	{
		if (isspace(c))
		{
			if (this->_data.find(word) != this->_data.end())
				actual_arg = word;
			else if (!(actual_arg.empty()))
				this->_data[actual_arg].push_back(word);
			word.clear();
		}
		else
			word.push_back(c);
	}
	for (auto &arg_map : this->_data)
	{
		std::vector<std::string>	&arg_vec = arg_map.second;
		std::string					&type_name = this->_types[arg_map.first];

		TYPE type;
		if (type_name == "int")
			type = TYPE::INT;
		else if (type_name == "double" || type_name == "float")
			type = TYPE::DOUBLE;
		else
			type = TYPE::STRING;

		if (type != TYPE::STRING)
		{
			for (auto &arg : arg_vec)
			{
				if (!isnumber(arg, (type == TYPE::INT) ? false : true))
					throw TypeMissmatchException(arg_map.first, type_name, arg);
			}
		}
	}
	return (this->_data);
}

std::unordered_map<std::string, std::vector<std::string> > const	&Parser::getParsedData(void) const
{
	return (this->_data);
}