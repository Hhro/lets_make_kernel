#ifdef INCLUDE_HEADERS
// ADD needed headers here
// Ex: #include <shell.hpp>

#endif


// ADD_SHELL_BUILTIN(func, name, desc)
// Add function to shell builtin. 
// Ex: void echo(char *args);
//     ADD_SHELL_BUILTIN(echo, "echo", "Echo args to output. ")

ADD_SHELL_BUILTIN(help, "help", "Print shell help document. ")
ADD_SHELL_BUILTIN(echo, "echo", "Echo args to output. ")