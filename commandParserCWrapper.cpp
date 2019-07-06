#include "commandParser.hpp"

extern "C" CommandParser* createCommandParser(void) {
	return new CommandParser();
}

extern "C" int addOption(CommandParser *parser, int maxCount, const char *valueName, const char *Short, const char *Long) {
	return parser->addOption(maxCount, valueName, Short, Long);
}

extern "C" int  parse(CommandParser *parser, int argc, char **argv) {
	return parser->parse(argc, argv);
}


extern "C" int hasOption  (CommandParser *parser, const char *valueName) {
	return parser->hasOption(valueName);
}
extern "C" int checkOption(CommandParser *parser, const char *valueName) {
	return parser->checkOption(valueName);
}
extern "C" int  countOption(CommandParser *parser, const char *valueName) {
	return parser->countOption(valueName);
}
extern "C" int  getOption  (CommandParser *parser, const char *valueName,
				 const char ***container) {
	return parser->getOption(valueName, container);
}


extern "C" void eraseCommandParser(CommandParser * parser) {
	delete parser;
}