#ifndef CODE_SNIPPET_MANAGER_H
#define CODE_SNIPPET_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

class CodeSnippetManager
{
private:
  std::map<std::string, std::string> snippets;
  std::string filePrefix;
  std::unordered_map<std::string, std::unordered_set<std::string>> invertedIndex;

public:
  CodeSnippetManager(const std::string &prefix = "./snippets/");
  ~CodeSnippetManager();

  bool AddSnippet(const std::string &tag, const std::string &code);
  bool RetrieveSnippet(const std::string &tag);
  bool DeleteSnippet(const std::string &tag);
  bool UpdateSnippet(const std::string &tag, const std::string &code);
  std::vector<std::string> SearchSnippetsByTag(const std::string &tagPrefix);
  std::vector<std::string> SearchSnippetsByContent(const std::vector<std::string> &keywords);
  bool SaveToFile();
  bool LoadFromFile();
  void LoadInvertedIndex();
  void SaveInvertedIndex();
  void UpdateInvertedIndex(const std::string &tag, const std::string &code);
  void RemoveFromInvertedIndex(const std::string &tag, const std::string &code);
};

#endif
