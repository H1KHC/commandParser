/**
 * @file commandParser.hpp
 * @author H1MSK (ksda47832338@outlook.com)
 * @version 0.0.2
 * @date 2019-08-13
 * 
 * homepage at https://github.com/H1KHC/CommandParser
 * 
 * @copyright Copyright (c) 2019 H1MSK
 * 
 */

#ifndef __H_COMMAND_PARSER_HPP___
#define __H_COMMAND_PARSER_HPP___

#include <vector>
#include <string>
#include <sstream>
#include <cstring>

template<class DATA, class TYPE = char, int T = (1 << (sizeof(TYPE) << 3))>
class CommandParserData {
	struct Node {
		Node *son[T];
		DATA *pointer;
		Node() : pointer(nullptr) {
			memset(son, 0, sizeof(Node*) * T);
		}
	} *root;

public:
	bool addString(const TYPE* str, DATA* pointer) {
		Node *pt = root;
		while(*str) {
			Node *&t = pt->son[(int)*str];
			if(t == nullptr) t = new Node();
			else if(t->pointer != nullptr) return false;
			pt = t;
			++str;
		}
		pt->pointer = pointer;
		return true;
	}

	const TYPE* findString(const TYPE* str, DATA*& pointer) {
		Node *pt = root;
		pointer = nullptr;
		while(*str) {
			Node *&t = pt->son[(int)*str];
			if(t == nullptr) {
				pointer = nullptr;
				return str;
			}
			pt = t;
			++str;
			if(pt->pointer) {
				pointer = pt->pointer;
				return str;
			}
		}
		pointer = pt->pointer;
		return nullptr;
	}

	void clear() {
		for(int i = 0; i < T; ++i) {
			Node *&t = root->son[i];
			if(t != nullptr) {
				recycleTree(t);
				t = nullptr;
			}
		}
	}

	static void recycleTree(Node *x) {
		for(int i = 0; i < T; ++i)
			if(x->son[i]) recycleTree(x->son[i]);
		delete x;
	}

	CommandParserData() : root(new Node) {}
	~CommandParserData() {
		recycleTree(root);
	}
};


typedef class CommandParser {
	typedef struct Value {
		bool appeared;
		int max;
		std::vector<const char *> container;
		bool full() { return container.size() >= (unsigned)max; }
		Value(int _max) : appeared(false), max(_max) { if(max < 0) max = 0x7FFFFFFF; }
	} Value;
	CommandParserData<Value> ShortCommand, LongCommand;
	CommandParserData<Value> ValueTrie;
	Value unmatched;
	std::stringstream helpStringStream;
	std::string helpString;

public:
	bool addOption(int maxCount, const char *valueName,
				   const char *Short, const char *Long,
				   const char* Description = "") {

		if(*Short == '-' || *valueName == '\0' ||
		  (*Short == '\0' && *Long == '\0'))
			return false;
		
		Value *value = new Value(maxCount);
		if(*Short) ShortCommand.addString(Short, value);
		if(*Long) LongCommand.addString(Long, value);
		ValueTrie.addString(valueName, value);
		
		helpStringStream <<"\n  " <<Short <<'\t' <<Long << '\t' <<Description;

		return true;
	}

	int parse(int argc, char **argv) {
		Value *current = &unmatched;
		for(int i = 1; i < argc; ++i) {
			// simple string
			if(*argv[i] != '-') {
				if(current->full()) current = &unmatched;
				current->container.push_back(argv[i]);
			}
			else {
				bool longOption = argv[i][1] == '-';
				char *beg = argv[i] + 1 + (longOption);
				CommandParserData<Value>*trie = (longOption) ? &LongCommand : &ShortCommand;
				Value *pointer;
				const char *end = trie->findString(beg, pointer);

				// option not found, treat as simple string
				if(pointer == nullptr) {
					if(current->full()) current = &unmatched;
					current->container.push_back(argv[i]);
				} else {
					current = pointer;
					current->appeared = true;
					if(!*end) continue;
					else if(longOption) {
						if(*end == '=' && end[1]) {
							if(current->full()) current = &unmatched;
							current->container.push_back(end + 1);
						}
					}
					else if(*end) {
						if(current->full()) current = &unmatched;
						current->container.push_back(end);
					}
				}
			}
		}
		return 0;
	}

	bool hasOption  (const char *valueName) {
		Value* pointer;
		const char *pt = ValueTrie.findString(valueName, pointer);
		return *pt == '\0' && pointer != nullptr;
	}
	bool checkOption(const char *valueName) {
		if(!*valueName) {
			return !unmatched.appeared;
		}
		Value* pointer;
		const char *pt = ValueTrie.findString(valueName, pointer);
		return !*pt && pointer != nullptr && pointer->appeared;
	}
	int  countOption(const char *valueName) {
		if(!*valueName) {
			return unmatched.container.size();
		}
		Value* pointer;
		const char *pt = ValueTrie.findString(valueName, pointer);
		if(*pt != '\0' || pointer == nullptr) return 0;
		return pointer->container.size();
	}
	int  getOption  (const char *valueName, const char ***container) {
		if(!*valueName) {
			*container = unmatched.container.data();
			return unmatched.container.size();
		}
		Value* pointer;
		const char *pt = ValueTrie.findString(valueName, pointer);
		if(*pt != '\0' || pointer == nullptr) return 0;
		*container = pointer->container.data();
		return pointer->container.size();
	}

	void setUsage(const char *usageDescription) {
		helpString = std::string(usageDescription);
	}

	const char *getHelpString() {
		helpString += helpStringStream.str();
		return helpString.c_str();
	}

	CommandParser(const std::string& description = "")
	  : unmatched(0x7FFFFFFF)
	{
		helpStringStream << description << "\nShort\tLong\tDescription";
	}
} CommandParser;

#endif  // __H_COMMAND_PARSER_HPP___