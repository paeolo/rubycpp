#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "json11.hpp"

using namespace std;
using namespace json11;

typedef struct ParserToken
{
    __uint8_t type;
    __int16_t data;
} __attribute__((packed, aligned(1))) ParserToken;

void getConfig(ifstream *file);
void pushKeys(map<string, Json> key_map, string node);

static int currentNode = 0;
static int currentPos = 0;
static map<string, Json> node_keys;
static vector<string> nodes;
static vector<ParserToken> tokens;
static vector<char> output_string;

int main(int argc, char** argv)
{
  if (argc != 4)
  {
    cerr << "<------------------------------------------------------------------->" << endl;
    cerr << "<--|  Creates a BIN file from a JSON that can be easily parsed.  |-->" << endl;
    cerr << "<--|  Usage: json2bin config_file input_file output_file.        |-->" << endl;
    cerr << "<--|  Notice: The config file is a json with Nodes and Keys.     |-->" << endl;
    cerr << "<------------------------------------------------------------------->" << endl;
    return 1;
  }

  /* GET THE CONFIG */

  ifstream file;
  string json;

  file.open(argv[1]);
  if(file)
  {
    getConfig(&file);
    file.close();
  }
  else
  {
    cerr << "ERROR: File not found: " << argv[1] << endl;
    return 1;
  }

  /* VERIFY THE CONFIG*/

  if(nodes.size() > 16)
  {
    cerr << "ERROR: 16 Nodes maximum" << endl;
    return 1;
  }
  
  for (auto const &keys: node_keys)
  {
    if (keys.second.array_items().size() > 16)
    {
      cerr << "ERROR: Node: " << keys.first << ", 16 Keys maximum" << endl;
      return 1;
    }
  }

  /* PARSE THE JSON - DOM STYLE */

  file.open(argv[2]);

  if(file)
   {
      ostringstream stringStream;
      stringStream << file.rdbuf();
      json = stringStream.str();
      file.close();
   }
   else
   {
     cerr << "ERROR: File not found: " << argv[2] << endl;
     return 1;
   }

  string err;
  const auto root = Json::parse(json, err);

  if(!err.empty())
  {
    cerr << "ERROR: " << err << endl;
    return 1;
  }

  /* CREATE TOKEN ARRAY */

  ParserToken rootToken;
  tokens.push_back(rootToken);

  map<string, Json> root_map = root.object_items();
  vector<string>::iterator node;

  for (node = nodes.begin(); node!= nodes.end(); ++node)
  {
    if(root_map.find(*node) != root_map.end())
    {
      int n_keys = node_keys[*node].array_items().size();

      if(root_map[*node].is_object())
      {
        ParserToken token;
        token.type = (__uint8_t) ((n_keys << 4) + (node - nodes.begin()));
        token.data = (__int16_t) root_map[*node].object_items().size();
        tokens.push_back(token);
        pushKeys(root_map[*node].object_items(), *node);
        currentNode++;
      }
      else if(root_map[*node].is_array())
      {
        vector<Json> array = root_map[*node].array_items();
        vector<Json>::iterator _node;
        for(_node = array.begin(); _node != array.end(); ++_node)
        {
          if(_node->is_object())
          {
            ParserToken token;
            token.type = (__uint8_t) ((n_keys << 4) + (node - nodes.begin()));
            token.data = (__int16_t) _node->object_items().size();
            tokens.push_back(token);
            pushKeys(_node->object_items(), *node);
            currentNode++;  
          }      
        }
      }
    }
  }

  /* SET UP FIRST TOKEN */

  int size;
  size = tokens.size();

  tokens[0].type = currentNode;
  tokens[0].data = (__int16_t) size*sizeof(ParserToken);

  /* CREATE THE BIN */

  ofstream outFile;
  outFile.open(argv[3]);
  for (int i = 0; i < size; ++i)
    outFile.write(reinterpret_cast<char*>(&tokens[i]), sizeof(ParserToken));
  outFile.write(output_string.data(), output_string.size());
  outFile.close();

  return 0;
}

void pushKeys(map<string, Json> key_map, string node)
{
    vector<Json> keys = node_keys[node].array_items();
    vector<Json>::iterator key;

    for (key = keys.begin(); key!= keys.end(); ++key)
    {
      string _key = (*key).string_value();
      if(key_map.find(_key) != key_map.end())
      {
        ParserToken token;
        token.type = (__uint8_t) (key - keys.begin());
        if(key_map[_key].is_string())
        {
          string _string = key_map[_key].string_value();
          copy(_string.begin(), _string.end(), std::back_inserter(output_string));
          output_string.push_back('\0');
          token.data = (__int16_t) currentPos;
          currentPos += _string.size() + 1;
        }
        else if (key_map[_key].is_number())
        {
          token.data = (__int16_t) key_map[_key].int_value();
        }
        else if (key_map[_key].is_bool())
        {
          token.data = (__int16_t) key_map[_key].bool_value();
        }
        tokens.push_back(token);
      }
    }
 }

void getConfig(ifstream *file)
{
  string json;
  ostringstream stringStream;
  stringStream << file->rdbuf();
  json = stringStream.str();
  file->close();

  /* PARSE THE JSON - DOM STYLE */

  string err;
  const auto root = Json::parse(json, err);

  if(!err.empty())
    cerr << "CONFIG ERROR: " << err << endl;

  map<string, Json> root_map = root.object_items();
  if(root_map.find("Node") != root_map.end())
  {
    for (auto const  &item: root_map["Node"].array_items())
      nodes.push_back(item.string_value());
  }
  else
  {
    cerr << "CONFIG ERROR: Node is required as root child" << endl;
  }

  if(root_map.find("Key") != root_map.end())
  {
    node_keys = root_map["Key"].object_items();
  }
  else
  {
    cerr << "CONFIG ERROR: Key is required as root child" << endl;
  }
}