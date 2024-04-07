#ifndef CODE_SNIPPET_MANAGER_H
#define CODE_SNIPPET_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
using namespace std;

class CodeSnippetManager
{
private:
  map<string,string> snippets;
  string filePrefix;
  unordered_map<string, unordered_set<string>> invertedIndex;

public:
  CodeSnippetManager(const string &prefix = "./snippets/");
  ~CodeSnippetManager();

  bool AddSnippet(const string &tag, const string &code);
  bool RetrieveSnippet(const string &tag);
  bool DeleteSnippet(const string &tag);
  bool UpdateSnippet(const string &tag, const string &code);
  vector<string> SearchSnippetsByTag(const string &tagPrefix);
  vector<string> SearchSnippetsByContent(const vector<string> &keywords);
  bool SaveToFile();
  bool LoadFromFile();
  void LoadInvertedIndex();
  void SaveInvertedIndex();
  void UpdateInvertedIndex(const string &tag, const string &code);
  void RemoveFromInvertedIndex(const string &tag, const string &code);
};

#endif
