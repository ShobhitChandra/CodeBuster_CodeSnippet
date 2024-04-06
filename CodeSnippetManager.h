#ifndef CODE_SNIPPET_MANAGER_H
#define CODE_SNIPPER_MANAGER_H
using namespace std;

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

class CodeSnippetManager{
  private:
  map<string,string> snippets;
  string filePrefix;
  unordered_map<string, unordered_set<string>> invertedIndex;

   public:
    CodeSnippetManager(const string &prefix = "./snippets/");

    void Add_Snippets(string& tag,const string& code);
    void Retrieve_Snippets(const string& tag);
    bool DeleteSnippet(const string &tag);
    void RemoveFromInvertedIndex(const string &tag, const string &code);
    bool Save_to_file(const string& filename);
    bool Load_to_file(const string& filename);  


    





};

#endif
