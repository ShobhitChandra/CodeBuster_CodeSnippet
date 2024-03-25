#ifndef CODE_SNIPPET_MANAGER_H
#define CODE_SNIPPER_MANAGER_H
using namespace std;

#include <string>
#include <map>

class CodeSnippetManager{
  private:
   map <string,string> snippets;

   public:

    void Add_Snippets(string& tag,const string& code);
    void Retrieve_Snippets(const string& tag);

    void Save_to_file(const string& filename);
    void Load_to_file(const string& filename);  


    





};

#endif