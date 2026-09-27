#include "search_server.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include <set>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


void SearchServer::Message() {
    std::cout << "SearchServer is ready" << std::endl;
}

std::vector<std::vector<RelativeIndex>> SearchServer::Search(const std::vector<std::string> &queries_input)
{
    std::vector<std::vector<RelativeIndex>> result;

    for (int i = 0; i < queries_input.size(); i++)
    {
        std::vector<std::string> words;
        std::map<std::string, std::vector<Entry>> words_map;

        std::istringstream ss(queries_input[i]);
        std::string word;

        while (ss >> word)
        {
            if (!words_map.count(word))
            {
                std::vector<Entry> entry;
                entry = _index.GetWordCount(word);
                words_map[word] = entry;
            }
        }
        

        std::multimap<int, std::string> sorted_map;
        for (const auto &it : words_map)
        {
            int count = 0;
            for (auto j : it.second)
            {
                count += j.count;
            }
            sorted_map.insert({count, it.first});
        }
        

        for (auto &i : sorted_map)
        {
            words.push_back(i.second);
        }

        std::map<int, std::vector<int>> doc_map;

        for (auto i = 0; i < words.size(); i++)
        {
            std::vector<Entry> ent;
            ent = words_map[words[i]];
            for (auto j : ent)
            {
                if (i == 0)
                {
                    doc_map[j.doc_id].push_back(j.count);
                }
                else
                {
                    if (doc_map.count(j.doc_id))
                    {
                        doc_map[j.doc_id].push_back(j.count);
                    }
                }

                
            }
        }
        
        std::map<int, int> sum_doc_map;
        int max_rank = 0;
        for (auto &i : doc_map)
        {
            if (i.second.size() == words.size())
            {
                std::vector<int> count_vec = doc_map[i.first];
                int count = 0;
                for (auto &j : count_vec)
                {
                    
                    count += j;
                }
                if (count > max_rank)
                    max_rank = count;
                sum_doc_map[i.first] = count;
            }
        }
        std::vector<RelativeIndex> rel_vec;

        if (max_rank == 0)
        {
            result.push_back(rel_vec);
            continue;
        }

        
        for (auto &k : sum_doc_map)
        {
           
            RelativeIndex rel_idx;
            rel_idx.doc_id = k.first;
            rel_idx.rank = (float)k.second / max_rank;
            rel_vec.push_back(rel_idx);
        }
        std::sort(rel_vec.begin(), rel_vec.end(), [](const RelativeIndex &a, const RelativeIndex &b)
                  {
            if (a.rank != b.rank) return a.rank > b.rank;
            else return a.doc_id < b.doc_id; });
        
        

        result.push_back(rel_vec);
        
    }
    return result;
    
}