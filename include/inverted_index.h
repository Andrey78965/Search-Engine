#pragma once
#include <vector>
#include <string>
#include <map>



struct Entry
{
    size_t doc_id, count = 0;
    bool operator==(const Entry &other) const
    {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};
class InvertedIndex
{
public:
    InvertedIndex() = default;

    void Message();

    //Обновить или заполнить базу документов
    void UpdateDocumentBase(std::vector<std::string> input_docs);

    //Метод определяет количество вхождений слова word в загруженной базе документов
    std::vector<Entry> GetWordCount(const std::string &word);

private:
    std::vector<std::string> docs;                             // список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный словарь
};