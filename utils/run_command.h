#ifndef RUN_COMMAND_H_
#define RUN_COMMAND_H_
void run_command(char* command,enum ptype type,redirect io_info);
void sequential(char* str);
int isCommand(char* str);
#endif