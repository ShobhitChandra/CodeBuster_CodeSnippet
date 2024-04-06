#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <map>
using namespace std;

class CodeSnippetManager{
  
   private:
   map <string,string> snippets;

   public:

    void Add_Snippets(const string& tag,const string& code);
    void Retrieve_Snippets(const string& tag);
    
    bool Save_to_file(const string& filename);
    bool Load_to_file(const string& filename);
};


void CodeSnippetManager :: Add_Snippets(const string& tag, const string& code){
    
    snippets[tag] = code;
}

void CodeSnippetManager :: Retrieve_Snippets(const string& tag)
{
    
    auto it = snippets.find(tag);
    if (it != snippets.end())
    {
        cout << "Snippets for tag '" << tag << "':" << endl;
        cout << it->second << endl;
    }
    
    else
    {
        cout << "No snippets found for tag '" << tag << "'." << endl;
    }
}

bool CodeSnippetManager :: Save_to_file(const string& filename)
{
    ofstream outFile(filename);
    
    if (!outFile)
    {
        cout << "Error opening the file." << endl;
        return false;
    }

   for (const auto& entry : snippets)
      {
        outFile << "Tag: " << entry.first << endl;
        outFile << "Code:\n" << entry.second << "\n";
      }

    outFile.close();
    cout << "Snippets saved to the file: " << filename << endl;
    return true;
}

bool CodeSnippetManager :: Load_to_file(const string& filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cout << "Error: Unable to open the file for reading." << endl;
        return false;
    }
    snippets.clear();
    string line;
    string currentTag;
    string currentCode;

    while (getline(inFile, line))
      {
        if (line.find("Tag: ") == 0)
        {
            currentTag = line.substr(5);
        }
       
        else if (line.find("Code: ") == 0)
        {
            currentCode = "";
            while (getline(inFile, line) && line != "")
            {
                currentCode += line + "\n";
            }
            snippets[currentTag] = currentCode;
        }
    }
    
      inFile.close();
      cout << "Snippets loaded from file: " << filename << endl;
      return true;
}


int main()
{
   CodeSnippetManager manager;

   if(manager.Load_to_file("snippets.txt"))
    {
       cout << "Snippets are loaded from the file" << endl;
    }
    
    else
    {
    cout << "No saved snippets found.Starting with an empty manager" << endl;
    }
  
  while(true)
   {  
     cout << "1.Add Snippet " << endl;
     cout << "2.Retrieve Snippet" << endl;
     cout << "3.Exit" << endl;
     cout << "Choose an option: " ;
   
   int choice;
    
    cin >> choice;
    if(choice == 1)
    {
      string tag,code;
      cout << "Enter the tag: ";
      cin >> tag;
      cout << "Enter the code snippet: \n";
      string line;
      code = "";

   while(getline(cin,line) && line!= "%%")
      {
        code += line+"\n";
      }
      
      manager.Add_Snippets(tag,code);
      cout << "Snippets are added."<< endl;
    }
  
   else if(choice == 2){
      string tag;
      cout << "Enter the tag to retrieve snippet: " ;
      cin >> tag;
      manager.Retrieve_Snippets(tag);
}

else if(choice == 3)
   {
     manager.Save_to_file("snippets.txt");
     cout << "Snippets saved to file.Exiting the program." << endl;
     break;   
    }
    
    else
    {
     cout << "Invalid choice.Choose a given option" << endl;
    }

}
   return 0;
}
