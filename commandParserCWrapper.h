#ifndef __H_COMMAND_PARSER_C_WRAPPER__
#define __H_COMMAND_PARSER_C_WRAPPER__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CommandParser CommandParser;

CommandParser* createCommandParser(void);

int addOption(CommandParser *parser, int maxCount, const char *valueName, const char *Short, const char *Long);

int parse(CommandParser *parser, int argc, char **argv);


int hasOption  (CommandParser *parser, const char *valueName);
int checkOption(CommandParser *parser, const char *valueName);
int countOption(CommandParser *parser, const char *valueName);
int getOption  (CommandParser *parser, const char *valueName, const char ***container);


void eraseCommandParser(CommandParser * parser);

#ifdef __cplusplus
}
#endif


#endif