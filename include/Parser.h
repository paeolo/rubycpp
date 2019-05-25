#ifndef PARSER_H
#define PARSER_H

#include "File.h"
#include "ParserKey.h"

typedef struct ParserToken
{
    u8 type;
    s16 data;
} __attribute__((packed, aligned(1))) ParserToken;

class Parser
{
    public:
        Parser() = delete;
        Parser(File* file);
        int nextNode();
        int node();
        int value(int key);
        const char* string(int key);
        bool exists(int key);
    private:
        int _keyValue[MAX_KEY];
        bool _keyExists[MAX_KEY];
        const ParserToken* _tokens;
        int _string;
        int _i;
        int _j;
        int _node;
};

#endif