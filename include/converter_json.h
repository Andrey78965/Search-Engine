#pragma once
#include <vector>
#include <string>
#include "search_server.h"



class ConverterJSON
{
public:
    ConverterJSON() = default;

    void Message();

    //Метод получения содержимого файлов
    //Возвращает список с содержимым файлов перечисленных в config.json
    std::vector<std::string> GetTextDocuments();
    
    //Метод считывает поле max_responses для определения предельного
    //количества ответов на один запрос
     
    int GetResponsesLimit();

    //Метод получения запросов изфайла requests.json
    //возвращает список запросов из файла requests.json
    std::vector<std::string> GetRequests();

    //Положить в файл answers.json результаты поисковых запросов
    void putAnswers(std::vector<std::vector<RelativeIndex>> answers);
};