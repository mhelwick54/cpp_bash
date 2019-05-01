#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <regex>

#include "debug.h"
#include "command.h"
#include "funcs.h"

class Parser {
private:
	std::string 			cmd_line;
	std::vector<Command> 	commands;
	std::vector<char>		redirs;
public:
/*****************************************************Constructors/Destructors*/
	Parser();
	Parser(std::string cmd_line);
/**********************************************************************Get/Set*/
	void 					setCmdLine(std::string cmd_line);
	std::string 			getCmdLine();
	Command					getCommand(int index);
	std::vector<Command> 	getCommands();
	std::vector<char>		getRedirs();
/**********************************************************************Methods*/
	void	parse();
	void 	makeCommand(std::vector<std::string> tokens);
	void 	makeRedirs();
	void 	splitCmdLine();
	bool 	validateCommands();
	void 	scrub();
/********************************************************************Overloads*/

};

#endif
