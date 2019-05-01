#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <iostream>

class Command {
private:
	std::string 				cmd;
	std::vector<std::string>	flags;
	std::vector<std::string> 	args;
public:
/*****************************************************Constructors/Destructors*/
	Command();
	Command(std::string cmd, std::vector<std::string> flags, std::vector<std::string> args);
/**********************************************************************Get/Set*/
	void 						setCmd(std::string cmd);
	void 						addFlag(std::string flag);
	void 						addArg(std::string arg);
	std::string 				getCmd();
	std::string 				getFlag(int index);
	std::string 				getArg(int index);
	std::vector<std::string> 	getFlags();
	std::vector<std::string> 	getArgs();
/**********************************************************************Methods*/

/********************************************************************Overloads*/
	friend std::ostream& operator <<(std::ostream& os, const Command& cmd);
};

#endif
