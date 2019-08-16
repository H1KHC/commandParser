/**
 * @file commandParserCWrapper.h
 * @author H1MSK (ksda47832338@outlook.com)
 * @version 0.0.2
 * @date 2019-08-16
 * 
 * @copyright Copyright (c) 2018-2019 H1MSK
 */

#ifndef __H_COMMAND_PARSER_C_WRAPPER__
#define __H_COMMAND_PARSER_C_WRAPPER__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CommandParser CommandParser;

CommandParser* createCommandParser(void);

int addOption(CommandParser *parser,
              int maxCount,
              const char *valueName,
              const char *Short,
              const char *Long,
              const char *description);

int parse(CommandParser *parser, int argc, char **argv);


int hasOption  (CommandParser *parser, const char *valueName);
int checkOption(CommandParser *parser, const char *valueName);
int countOption(CommandParser *parser, const char *valueName);
int getOption  (CommandParser *parser, const char *valueName, const char ***container);

void setUsage(CommandParser *parser, const char *usageDescription);
const char *getHelpString(CommandParser *parser);

void eraseCommandParser(CommandParser * parser);

#ifdef __cplusplus
}
#endif


#endif