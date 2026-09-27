#pragma once
#include <vector>
#include <string>
#include "inverted_index.h"


struct RelativeIndex {
    int doc_id;
    float rank;
    bool operator== (const RelativeIndex& other) const {return(doc_id== other.doc_id && rank==other.rank);
    }
};
class SearchServer {
    public:

    SearchServer (InvertedIndex& idx): _index(idx){};

    void Message();

//Метод обработки поисковых запросов
//queries_input поисковые запросы взятые из файла requests.json
//возвращает отсортированный список релевантных ответов для заданных запросов
    std::vector<std::vector<RelativeIndex>> Search(const std::vector<std::string>& queries_input);
    private:
    InvertedIndex& _index;
};
