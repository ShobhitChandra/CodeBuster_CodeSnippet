#include "CodeSnippetManager.h"
#include <iostream>
using namespace std;

int main()
{
   CodeSnippetManager manager;

   if(manager.Load_to_file("snippets.txt")){
       cout << "Snippets are loaded from the file" << endl;
    }
    else{
    cout << "No saved snippets found.Starting with an empty manager" << endl;

    }

 while(true)
 {
    cout << "1.Add Snippet" << endl;
    cout << "2.Retrieve Snippet" << endl;
    cout << "3.Exit" << endl;
    cout << "Choose an option" << endl;

    int choice;
    cin >> choice;

    if (choice == 1)
        {
            string tag, code;
            cout << "Enter the tag: ";
            cin >> tag;
            tag = toLowerCase(tag);
            cin.ignore();

            cout << "Enter the code snippet:\n";
            string line;
            code = "";

            while (getline(cin, line) && line != "%%")
            {
                code = code + line + "\n";
            }
            manager.AddSnippet(tag, code);
            cout << "Snippets are added." << endl;
        }

  
    else if(choice == 2){
      string tag;
      cout << "Enter the tag to retrieve snippet: ";
      cin >> tag;
      manager.Retrieve_Snippet(tag);

   }

   else if (choice == 3)
        {
            string tag;
            cout << "Enter the tag to Delete the snippet: ";
            cin >> tag;
            tag = toLowerCase(tag);
            manager.DeleteSnippet(tag);
            manager.SaveToFile();
        }

   else if (choice == 7)
        {
            manager.SaveToFile();
            manager.SaveInvertedIndex();
            cout
                << "Snippets saved to file. Exiting the program." << endl;
            break;
        }

    else{
     cout << "Invalid choice.Choose a given option" << endl;


    }
   



 }

 return 0;
}

