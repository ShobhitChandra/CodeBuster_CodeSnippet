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
    for (const auto &entry : snippets)
    {
        string filename = filePrefix + entry.first + ".txt";
        ofstream outFile(filename);
        if (!outFile)
        {
            cerr << "Error opening file: " << filename << endl;
            return false;
        }
        outFile << entry.second;
        outFile.close();
    }
    return true;
}

bool CodeSnippetManager:: Load_to_file(const string& filename)
{
    snippets.clear();
    for (const auto &entry : fs::directory_iterator("./snippets/"))
    {
        if (entry.path().extension() == ".txt")
        {
            string filename = entry.path().filename().string();
            string tag = filename.substr(0, filename.length() - 4);
            ifstream inFile(entry.path());
            if (!inFile)
            {
                cerr << "Error opening file: " << filename << endl;
                return false;
            }
            string code((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
            snippets[tag] = code;
            inFile.close();
        }
    }
    return true;
}

void CodeSnippetManager::LoadInvertedIndex()
{
    ifstream file("inverted_index.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string word;
            if (iss >> word)
            {
                string tag;
                while (iss >> tag)
                {
                    invertedIndex[word].insert(tag);
                }
            }
        }
        file.close();
    }
}

void CodeSnippetManager::SaveInvertedIndex()
{
    ofstream file("inverted_index.txt");
    if (file.is_open())
    {
        for (const auto &entry : invertedIndex)
        {
            const string &word = entry.first;
            const unordered_set<string> &tags = entry.second;
            file << word;
            for (const string &tag : tags)
            {
                file << " " << tag;
            }
            file << endl;
        }
        file.close();
    }
}
