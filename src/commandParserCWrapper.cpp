#include "commandParser.hpp"

CommandParser* createCommandParser(void) {
	return new CommandParser();
}

bool addOption(CommandParser *parser, int maxCount, const char *valueName, const char *Short, const char *Long) {
	return parser->addOption(maxCount, valueName, Short, Long);
}

int  parse(CommandParser *parser, int argc, char **argv) {
	return parser->parse(argc, argv);
}


bool hasOption  (CommandParser *parser, const char *valueName) {
	return parser->hasOption(valueName);
}
bool checkOption(CommandParser *parser, const char *valueName) {
	return parser->checkOption(valueName);
}
int  countOption(CommandParser *parser, const char *valueName) {
	return parser->countOption(valueName);
}
int  getOption  (CommandParser *parser, const char *valueName,
				 const char ***container) {
	return parser->getOption(valueName, container);
}


void eraseCommandParser(CommandParser * parser) {
	delete parser;
}