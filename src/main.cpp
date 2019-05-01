#include "../include/main.h"

int main() {
	Parser parser;
	std::string cmd_line;
	bool exit_flag = false;

	while(1) {
		exit_flag = false;
		prompt();
		std::getline(std::cin, cmd_line);
		parser.setCmdLine(cmd_line);
		parser.parse();
		std::vector<Command> cmds = parser.getCommands();
		for(auto cmd : cmds) {
			if(cmd.getCmd() == "Exit" || cmd.getCmd() == "exit") {
				exit_flag = true;
			} else if(cmd.getCmd() == "cd") {
				cd(cmd);
			} else {
				execute(cmd);
			}
		}
		parser.scrub();
		if(exit_flag == true) {
			break;
		}
	}
	return 0;
}
