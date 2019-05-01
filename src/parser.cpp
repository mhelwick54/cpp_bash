#include "../include/parser.h"

/*****************************************************Constructors/Destructors*/
Parser::Parser() {}

Parser::Parser(std::string cmd_line) {
	this->cmd_line = cmd_line;
}

/**********************************************************************Get/Set*/
void Parser::setCmdLine(std::string cmd_line) {
	this->cmd_line = cmd_line;
}

std::string Parser::getCmdLine() {
	return this->cmd_line;
}

Command Parser::getCommand(int index) {
	return this->commands.at(index);
}

std::vector<Command> Parser::getCommands() {
	return this->commands;
}

std::vector<char> Parser::getRedirs() {
	return this->redirs;
}
/**********************************************************************Methods*/
void Parser::parse() {
	splitCmdLine();
	validateCommands();
}

void Parser::makeCommand(std::vector<std::string> tokens) {
	Command cmd;
	auto it = tokens.begin();
	while((*it).length() == 0) {
		++it;
	}
	cmd.setCmd(*it);
	++it;
	while(it != tokens.end()) {
		if((*it)[0] == '-') {
			cmd.addFlag(*it);
		} else {
			cmd.addArg(*it);
		}
		++it;
	}
	this->commands.push_back(cmd);
}

void Parser::makeRedirs() {
	std::vector<std::string> tokens;
	auto it = this->cmd_line.begin();
	while(it != this->cmd_line.end()) {
		if(*it == '|' || *it == '<' || *it == '>' || *it == ';') {
			this->redirs.push_back(*it);
		}
		++it;
	}
}

void Parser::splitCmdLine() {
	std::string msg = "Parsing command line: " + this->cmd_line;
	this->getRedirs();

	std::vector<std::string> cmd;
	auto it = this->cmd_line.begin();
	std::string delims = "|<>; ";
	std::string ret = "";
	while(it != this->cmd_line.end()) {
		ret = tokenizer(it, &(this->cmd_line), delims);
		it += ret.length();
		while(*(ret.begin()) == ' ') {
			ret.erase(ret.begin());
		}
		cmd.push_back(ret);
		if(*it == '|' || *it == '<' || *it == '>' || *it == ';') {
			this->makeCommand(cmd);
			cmd.clear();
		}
		if(it != this->cmd_line.end()) {
			++it;
		}
	}
	this->makeCommand(cmd);
}

bool Parser::validateCommands() {
	return true;
}

void Parser::scrub() {
	this->cmd_line = "";
	this->commands.clear();
	this->redirs.clear();
}

/********************************************************************Overloads*/
