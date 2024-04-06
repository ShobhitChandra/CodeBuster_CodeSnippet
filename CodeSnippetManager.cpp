#include "CodeSnippetManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>

CodeSnippetManager::CodeSnippetManager(const string &prefix) : filePrefix(prefix)
{
    LoadFromFile();
    LoadInvertedIndex();
}

CodeSnippetManager::~CodeSnippetManager()
{
    SaveToFile();
    SaveInvertedIndex();
}


bool CodeSnippetManager::AddSnippet(const string &tag, const string &code)
{
    snippets[tag] = code;

    // Update the inverted index
    istringstream iss(code);
    string word;
    while (iss >> word)
    {
        invertedIndex[word].insert(tag);
    }
    UpdateInvertedIndex(tag, code);
    SaveToFile();
    SaveInvertedIndex();
    return true;
}

bool CodeSnippetManager::DeleteSnippet(const string &tag)
{
    auto it = snippets.find(tag);
    if (it != snippets.end())
    {
        // Remove the snippet from the inverted index
        const string &code = it->second;
        RemoveFromInvertedIndex(tag, code);
        istringstream iss(code);
        string word;
        while (iss >> word)
        {
            auto indexIt = invertedIndex.find(word);
            if (indexIt != invertedIndex.end())
            {
                indexIt->second.erase(tag);
                if (indexIt->second.empty())
                {
                    invertedIndex.erase(indexIt);
                }
            }
        }

        snippets.erase(it);
        fs::remove(filePrefix + tag + ".txt");
        SaveToFile();
        SaveInvertedIndex();
        cout << "Snippet deleted successfully." << endl;
        return true;
    }
    else
    {
        cout << "No snippet found for tag: " << tag << endl;
        return false;
    }
}
void CodeSnippetManager::RemoveFromInvertedIndex(const string &tag, const string &code)
{
    istringstream iss(code);
    string word;
    while (iss >> word)
    {
        auto it = invertedIndex.find(word);
        if (it != invertedIndex.end())
        {
            it->second.erase(tag);
            if (it->second.empty())
            {
                invertedIndex.erase(it);
            }
        }
    }
}
void CodeSnippetManager::Retrieve_Snippets(const string& tag)
{
    auto it = snippets.find(tag);
    if (it != snippets.end())
    {
        cout << "Snippets for tag is: " << tag << ":\n" << it->second << endl;
    }
    else
    {
        cout << "No snippets found for tag: " << tag << "." << endl;
    }
}

bool CodeSnippetManager:: Save_to_file(const string& filename)
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

bool CodeSnippetManager:: Load_to_file(const string& filename)
{
    ifstream ifile(filename);
    if (!ifile)
    {
        cout << "Error: Unable to open the file for reading." << endl;
        return false;
    }

    snippets.clear();
    string line;
    string currentTag;
    string currentCode;

    while (getline(ifile, line))
    {
        if (line.find("Tag: ") == 0)
        {
            currentTag = line.substr(5);
        }
        else if (line.find("Code: ") == 0)
        {
            currentCode = "";
            while (getline(ifile, line) && line != "")
            {
                currentCode += line + "\n";
            }
            snippets[currentTag] = currentCode;
        }
    }
    ifile.close();
    cout << "Snippets loaded from file: " << filename << endl;
    return true;
}
