#include "inverted_index.h"
#include <sstream>
#include <thread>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <mutex>
#include <iostream>

void InvertedIndex::Message()
{
    std::cout << "InvertedIndex is ready" << std::endl;
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
    docs = std::move(input_docs);
    freq_dictionary.clear();
    std::mutex update;
    std::vector<std::thread> t;

    for (size_t i = 0; i < docs.size(); i++)
    {
        t.emplace_back([this, i, &update]()
                       {
                std::map<std::string, Entry> dictionary;
                std::stringstream ss(docs[i]);
                std::string word;
                while (ss >> word) {
                    if (dictionary.count(word)) {
                        dictionary[word].count++;
                    }
                    else {
                        Entry entry;
                        entry.doc_id = i;
                        entry.count = 1;
                        dictionary[word] = entry;
                    }
                }
                update.lock();
                for (auto it = dictionary.begin(); it != dictionary.end(); it++) 
                {
                    
                    freq_dictionary[it->first].push_back(it->second);
                    
                }
                update.unlock(); });
    }

    for (auto &j : t)
    {
        j.join();
    }
    
};

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word)

{
    
   
    if (freq_dictionary.count(word))
    {
        return freq_dictionary[word];
    }
    else
        return {};
};
