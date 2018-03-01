## Command Parser

Command parser is a C/C++ library that can help us parse command easily.

It is cross-platform, light-weighted(especially when using C++) and easy-used.


### Build

1. `cd` into the library's directory
2. `make [(all|static|dynamic)] [example] [DEBUG=true]`
3. If necessary, `make install [INSTALL_PREFIX=...]`



### Usage

>
> If you are using C++, you can just include the hpp file and use the class directly.
>

Firstly, you need to create a parser:

```cpp
CommandParser* createCommandParser(void);
CommandParser *parser = createCommandParser();
```



Then, add some options into it:

```cpp
bool addOption(CommandParser *parser, int maxCount, const char *valueName, const char *Short, const char *Long);

// The parameter "Long" can be ignored
// maxCount can be any negative integer, which means infinity

addOption(parser, 0, "help", "h", "help");
addOption(parser, 1, "i", "input", "input");
addOption(parser, -1, "o", "output", "output option");
```



After that, you can parse the options:

```cpp
int  parse(CommandParser *parser, int argc, char **argv);

if(parse(parser, argc, argv)) {
    cout <<"Parse failed\n";
    return 1;
}
```



And get results:

```cpp
bool hasOption  (CommandParser *parser, const char *valueName);
bool checkOption(CommandParser *parser, const char *valueName); // will crash if name not found
int  countOption(CommandParser *parser, const char *valueName);
int  getOption  (CommandParser *parser, const char *valueName, char ***container);
// for the parameter "container" in c style function, you need to pass a container's address
// return value is the count of the options
// you don't need to free the container, it will be free once deleted the parser

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



In the end, you can at any time delete it:

```cpp
void eraseCommandParser(CommandParser * parser);

eraseCommandParser(parser);
```