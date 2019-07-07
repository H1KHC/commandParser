## Command Parser

Command parser is a C/C++ library that can help us parse command easily.

It is cross-platform, light-weighted(especially when using C++) and easily-used.


### Build

1. `cd` into the library's directory
2. `cmake .` or more frequently `mkdir .build && cd .build && cmake ..`
3. `make`


### Usage

This is an example in language C. For the example files in language C and C++, you can check the `test.c` or `test.cpp` in example folder.

First, you need to create a parser(File inclusion is ignored):

```cpp
// CommandParser* createCommandParser(void);

CommandParser *parser = createCommandParser();
```


Second, add some options into it:

```cpp
// bool addOption(CommandParser *parser, int maxCount, const char *valueName, const char *Short, const char *Long);

addOption(parser, 0, "help", "h", "help");

addOption(parser, 1, "i", "input", "input");
// Either short or long parameter can be ignored, but you cannot ignore both (Of course I can't!)

addOption(parser, -1, "o", "output", "output option");
// maxCount can be any negative integer, which means infinity
```

Third, you can parse the options:

```cpp
// int  parse(CommandParser *parser, int argc, char **argv);

if(parse(parser, argc, argv)) {
    cout <<"Parse failed\n";
    return 1;
}
```

And forth, get results:

```cpp
// bool hasOption  (CommandParser *parser, const char *valueName);

// bool checkOption(CommandParser *parser, const char *valueName);
    // will crash if name not found

// int  countOption(CommandParser *parser, const char *valueName);
// int  getOption  (CommandParser *parser, const char *valueName, char ***container);
// for the parameter "container" you need to pass the address of a char** variable

// return value is the count of the options
// you don't need to and shouldn't free the container, as it will be free once the parser is deleted

if(checkOption(parser, "help"))
	cout <<"Help flag is set" <<endl;
else cout <<"Help flag is not set" <<endl;

char **options;
int count = getOption(parser, "input", &options);
cout <<"There are "<<count <<" input strings:" <<endl;
for(int i = 0; i < count; ++i)
    cout <<i <<": " <<options[i] <<endl;

count = getOption(parser, "output", &options);
if(count)
    cout <<"Output string is " <<options[0] <<endl;
else cout <<"Output string isn't set" <<endl;
```

In the end, you can delete the parser at any time:

```cpp
// void eraseCommandParser(CommandParser * parser);

eraseCommandParser(parser);
```