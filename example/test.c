#include "../commandParserCWrapper.h"
#include <stdio.h>

int main(int argc, char **argv) {
	// First, create a parser
    CommandParser *parser = createCommandParser();

	// Second, add some options into it
	addOption(parser, 2, "add", "a", "add");
    addOption(parser, 0, "x", "x", "xx");

	// Third, parse the arg
    parse(parser, argc, argv);

	// Forth, get the results
    printf("Flag x is%s set.\n", checkOption(parser, "x") ? "" : "n't");

    const char **options;
    int c = getOption(parser, "add", &options);
    printf("There are %d parameters for option add%c\n", c, c ? ':' : '.');
    for(int i = 0; i < c; ++i)
        printf("\t%s\n", options[i]);

    c = getOption(parser, "", &options);
    printf("And %d unmatched options%c\n", c, c ? ':' : '.');
    for(int i = 0; i < c; ++i)
        printf("\t%s\n", options[i]);

	// And fifth, delete the parser
	eraseCommandParser(parser);
}

/*
Example parameters:
1. test
2. test -x
3. test -a 123 456 abc
4. test u -a 123 456 abc
5. test --add 123 -x abc def
*/