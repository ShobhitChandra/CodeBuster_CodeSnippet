#include "CodeSnippetManager.h"
#include <iostream>
using namespace std;

std::string toLowerCase(std::string input_string)
  {
    std::string lowercased_string = "";
    for (char &c : input_string)
    {
      if (c >= 'A' && c <= 'Z')
      {
        lowercased_string += c + ('a' - 'A');
      }
      else
      {
        lowercased_string += c;
      }
    }
    return lowercased_string;
  }

int main()
{
    CodeSnippetManager manager;

    if (manager.LoadFromFile())
    {
        cout << "Snippets are loaded from the file" << endl;
        manager.LoadInvertedIndex();
    }
    else
    {
        cout << "No saved snippets found.Starting with an empty manager" << endl;
    }

    while (true)
    {
        cout << ("------------------------------------") << endl;
        cout << ("|                START             |") << endl;
        cout << ("------------------------------------") << endl;
        cout << ("|  1.Add Snippet                   |") << endl;
        cout << ("|                                  |") << endl;
        cout << ("|  2.Retrieve Snippet              |") << endl;
        cout << ("|                                  |") << endl;
        cout << ("|  3.Deleting Snippet              |") << endl;
        cout << ("|                                  |") << endl;
        cout << ("|  4.Updating Snippet              |") << endl;
        cout << ("|                                  |") << endl;
        cout << ("|  5.Search By Tag                 |") << endl;
        cout << ("|                                  |") << endl;
        cout << ("|  6.Search By Contents            |") << endl;
        cout << ("|                                  |") << endl;
        cout << ("|  7.Exit the Program              |") << endl;
        cout << ("|                                  |") << endl;
        cout << ("------------------------------------") << endl;

        cout << ("------------------------------------") << endl;
        cout << ("|         Choose an option:        |") << endl;
        cout << ("------------------------------------") << endl;
        int choice;
        cin >> choice;
        cin.ignore();

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

        else if (choice == 2)
        {
            string tag;
            cout << "Enter the tag to retrieve snippet: ";
            cin >> tag;
            tag = toLowerCase(tag);
            manager.RetrieveSnippet(tag);
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

        else if (choice == 4)
        {
            string tag, code;
            cout << "Enter the tag to Update the snippet: ";
            cin >> tag;
            tag = toLowerCase(tag);

            /**
             * Search for the snippet before asking for the update
             */
            if (!manager.RetrieveSnippet(tag))
            {
                // File is not available
                cout << "File does not exist for a given tag" << endl;
            }
            else
            {
                cout << "Enter the updated code snippet:\n";
                string line;
                code = "";

                while (getline(cin, line) && line != "%%")
                {
                    code = code + line + "\n";
                }
                manager.UpdateSnippet(tag, code);
            }
        }

        else if (choice == 5)
        {
            string tagPrefix;
            cout << "Tell me which snippet you want to search for: ";
            getline(cin,tagPrefix);
            tagPrefix = toLowerCase(tagPrefix);
            vector<string> Results = manager.SearchSnippetsByTag(tagPrefix);
            if (!Results.empty())
            {
                cout << "Matching snippets:" << endl;
                for (const auto &tag : Results)
                {
                    cout << "- " << tag << endl;
                }
            }
            else
            {
                cout << "No snippets found for the given query." << endl;
            }
        }
        else if (choice == 6)
        {
            string input;
            cout << "Enter keywords to search for snippets (separated by spaces): ";
            cin.ignore();
            getline(cin, input);
            input = toLowerCase(input);
            istringstream iss(input);
            vector<string> keywords;
            string keyword;
            while (iss >> keyword)
            {
                keywords.push_back(keyword);
            }
            vector<string> matchingTags = manager.SearchSnippetsByContent(keywords);
            if (!matchingTags.empty())
            {
                cout << "Matching snippets:" << endl;
                for (const auto &tag : matchingTags)
                {
                    cout << "- " << tag << endl;
                }
            }
            else
            {
                cout << "No snippets found for the given query." << endl;
            }
        }
        else if (choice == 7)
        {
            manager.SaveToFile();
            manager.SaveInvertedIndex();
            cout
                << "Snippets saved to file. Exiting the program." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice.Choose a given option" << endl;
        }
    }

    return 0;
}
