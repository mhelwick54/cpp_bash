#ifndef LIBS_H
#define LIBS_H

/* c header */
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <unistd.h>
#include <errno.h>

#include <iostream>
#include <string>
#include <filesystem>

#include "debug.h"
#include "parser.h"
#include "funcs.h"

#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define GREEN "\033[1;32m"

void prompt() {
	struct passwd *pw = getpwuid(getuid());
	char *hostname = new char[128];
	if(gethostname(hostname, 128) < 0) {
		debug("Hostname retrieval failed");
		exit(-1);
	}
	std::cout << CYAN << pw->pw_name << WHITE << "@" << GREEN << hostname << WHITE << ">";
}

void arguments(Command cmd, char* args[], int args_count) {
	int index = 0;
	args[0] = (char *)malloc((cmd.getCmd().length() + 1) * sizeof(char));
	std::strcpy(args[0], cmd.getCmd().c_str());
	++index;
	for(auto flag : cmd.getFlags()) {
		args[index] = (char *)malloc((flag.length() + 1) * sizeof(char));
		std::strcpy(args[index], flag.c_str());
		++index;
	}
	for(auto arg : cmd.getArgs()) {
		args[index] = (char *)malloc((arg.length() + 1) * sizeof(char));
		std::strcpy(args[index], arg.c_str());
		++index;
	}
	args[index] = NULL;
}

void printArgs(char* args[], int args_count) {
	for(int i = 0; i < args_count; ++i) {
		debug(args[i]);
	}
}

void execute(Command cmd) {
	pid_t pid = fork();
	if(pid == -1) {
		debug("Fork failed, execution aborting...");
		return;
	} else if(pid == 0) {
		int args_count = cmd.getFlags().size() + cmd.getArgs().size() + 2;
		char* args[args_count];
		arguments(cmd, args, args_count);

		if(DEBUG) {
			printArgs(args, args_count);
		}
		if(execv(args[0], args) < 0) {
			args[0] = (char *)realloc(args[0], ((cmd.getCmd().length() + 6) * sizeof(char)));
			std::strcpy(args[0], ("/bin/" + cmd.getCmd()).c_str());
			if(DEBUG) {
				printArgs(args, args_count);
			}
			if(execv(args[0], args) < 0) {
				args[0] = (char *)realloc(args[0], ((cmd.getCmd().length() + 10) * sizeof(char)));
				std::strcpy(args[0], ("/usr/bin/" + cmd.getCmd()).c_str());
				if(DEBUG) {
					printArgs(args, args_count);
				}
				if(execv(args[0], args) < 0) {
					debug("Execv failed");
					perror("execv");
				}
			}
		}
	} else {
		wait(NULL);
	}
}

void cd(Command cmd) {
	if(chdir((*cmd.getArgs().begin()).c_str()) < 0) {
		debug("chdir failed");
	}
}

#endif
