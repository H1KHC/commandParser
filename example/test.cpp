#include "../commandParser.hpp"
#include <cstdio>

int main(int argc, char **argv) {
	// First, create a parser
    CommandParser *parser = new CommandParser;

	// Second, add some options into it
	parser->addOption(2, "add", "a", "add");
    parser->addOption(0, "x", "x", "xx");

	// Third, parse the arg
    parser->parse(argc, argv);

	// Forth, get the results
    printf("Flag x is%s set.\n", parser->checkOption("x") ? "" : "n't");

    const char **options;
    int c = parser->getOption("add", &options);
    printf("There are %d parameters for option add%c\n", c, c ? ':' : '.');
    for(int i = 0; i < c; ++i)
        printf("\t%s\n", options[i]);

    c = parser->getOption("", &options);
    printf("And %d unmatched options%c\n", c, c ? ':' : '.');
    for(int i = 0; i < c; ++i)
        printf("\t%s\n", options[i]);

	// And fifth, delete the parser
	delete parser;
}

/*
Example parameters:
1. test
2. test -x
3. test -a 123 456 abc
4. test u -a 123 456 abc
5. test --add 123 -x abc def
*/