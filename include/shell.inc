#ifdef INCLUDE_HEADERS
// ADD needed headers here
// Ex: #include <shell.hpp>

#include <banner.hpp>

#endif


// ADD_SHELL_BUILTIN(func, name, desc)
// Add function to shell builtin. 
// Ex: void echo(char *args);
//     ADD_SHELL_BUILTIN(echo, "echo", "Echo args to output. ")

ADD_SHELL_BUILTIN(help, "help", "Print shell help document. ")
ADD_SHELL_BUILTIN(echo, "echo", "Echo args to output. ")
ADD_SHELL_BUILTIN(banner, "banner", "Prints front 10 chars from args bigger. ")
ADD_SHELL_BUILTIN(dump_cpuinfo, "cpuinfo", "Dump cpuinfo to output. ")
ADD_SHELL_BUILTIN(start_test_task, "testtask", "Start test task. ")
