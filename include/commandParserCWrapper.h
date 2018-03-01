#ifndef __H_COMMAND_PARSER_C_WRAPPER__
#define __H_COMMAND_PARSER_C_WRAPPER__

#if   defined(STATIC_LIB)
#   define COM_PAR_API
#elif defined(__linux__)
#   define COM_PAR_API __attribute__(("visibility=hidded"))
#elif defined(DLL_IMPLEMENTED)
#   define COM_PAR_API __declspec(dllexport)
#else
#   define COM_PAR_API __declspec(dllimport)
#endif

struct CommandParser;
typedef struct CommandParser CommandParser;

COM_PAR_API CommandParser* createCommandParser(void);

COM_PAR_API bool addOption(CommandParser *parser, int maxCount, const char *valueName, const char *Short, const char *Long);

COM_PAR_API int  parse(CommandParser *parser, int argc, char **argv);


COM_PAR_API bool hasOption  (CommandParser *parser, const char *valueName);
COM_PAR_API bool checkOption(CommandParser *parser, const char *valueName);
COM_PAR_API int  countOption(CommandParser *parser, const char *valueName);
COM_PAR_API int  getOption  (CommandParser *parser, const char *valueName, const char ***container);


COM_PAR_API void eraseCommandParser(CommandParser * parser);
#endif