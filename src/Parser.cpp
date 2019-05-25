#include "File.h"
#include "Parser.h"

Parser::Parser(File* file)
{
    this->_tokens = (const ParserToken*) file->data();
    this->_string = (int) _tokens + _tokens[0].data;
    this->_i = 0;
    this->_j = this->_tokens[0].type;
    this->_node = 0;
}

int Parser::nextNode()
{
    if(this->_i < this->_j)
    {
        _node = (_node == 0) ? 1 : (_node + _tokens[_node].data + 1);
        int j = 0;

        for(int i = 0; i < (_tokens[_node].type >> 4); ++i)
        {
            if (i == _tokens[_node + j + 1].type)
            {
                _keyValue[i] = _tokens[_node + j + 1].data;
                _keyExists[i] = true;
                ++j;
            }
            else
            {
                _keyValue[i] = 0;
                _keyExists[i] = false;
            }
        }
        ++this->_i;
        return 1;
    }
    else
        return 0;
}

int Parser::node()
{
    return (_tokens[_node].type & 0x0F);
}

bool Parser::exists(int key)
{
    return _keyExists[key];
}

int Parser::value(int key)
{
    return _keyValue[key];
}

const char* Parser::string(int key)
{
    return (const char*) (_string + _keyValue[key]);
}