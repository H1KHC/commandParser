#ifndef __H_COMMAND_PARSER_C_WRAPPER__
#define __H_COMMAND_PARSER_C_WRAPPER__

struct CommandParser;
typedef struct CommandParser CommandParser;

CommandParser* createCommandParser(void);

bool addOption(CommandParser *parser, int maxCount, const char *valueName, const char *Short, const char *Long);

int  parse(CommandParser *parser, int argc, char **argv);


bool hasOption  (CommandParser *parser, const char *valueName);
bool checkOption(CommandParser *parser, const char *valueName);
int  countOption(CommandParser *parser, const char *valueName);
int  getOption  (CommandParser *parser, const char *valueName, const char ***container);


void eraseCommandParser(CommandParser * parser);
#endif