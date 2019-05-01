#include "../include/command.h"

/*****************************************************Constructors/Destructors*/
Command::Command() {}

Command::Command(std::string cmd, std::vector<std::string> flags, std::vector<std::string> args) {
	this->cmd = cmd;
	this->flags = flags;
	this->args = args;
}

/**********************************************************************Get/Set*/
void Command::setCmd(std::string cmd) {
	this->cmd = cmd;
}

void Command::addFlag(std::string flag) {
	this->flags.push_back(flag);
}

void Command::addArg(std::string arg) {
	this->args.push_back(arg);
}

std::string Command::getCmd() {
	return this->cmd;
}

std::string Command::getFlag(int index) {
	return this->flags.at(index);
}

std::string Command::getArg(int index) {
	return this->args.at(index);
}

std::vector<std::string> Command::getFlags() {
	return this->flags;
}

std::vector<std::string> Command::getArgs() {
	return this->args;
}

/**********************************************************************Methods*/

/********************************************************************Overloads*/
std::ostream& operator <<(std::ostream& os, const Command& cmd) {
	std::string space = " ";
	os << cmd.cmd << space;
	for(auto flag : cmd.flags) {
		os << flag << space;
	}
	for(auto arg : cmd.args) {
		os << arg << space;
	}
	return os;
}
