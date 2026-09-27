#include "converter_json.h"
#include <sstream>
#include <iostream>
#include <vector>
#include "nlohmann/json.hpp"
#include <fstream>
#include <iomanip>

void ConverterJSON::Message()
{
    std::cout << "ConverterJSON is ready" << std::endl;
}
std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::ifstream conf("../resources/config/config.json");
    if (!conf.is_open())
    {
        throw std::runtime_error("config file is missing");
    }

    nlohmann::json file;
    conf >> file;

    if (file.contains("config") == 0)
    {
        throw std::runtime_error("config file is empty");
    }

    auto numResources = file["files"].size();

    std::vector<std::string> textDocuments;
    for (int i = 0; i < (int)numResources; i++)
    {
        std::string filePath = file["files"][i];

        std::ifstream data(filePath);
        if (data.is_open())
        {
            std::ostringstream ss;
            ss << data.rdbuf();
            std::string text;
            textDocuments.push_back(ss.str());
        }
        else
            std::cerr << "Error with file" << std::endl;
    }
    return textDocuments;
};

int ConverterJSON::GetResponsesLimit()
{
    std::ifstream conf("../resources/config/config.json");
    nlohmann::json file;
    conf >> file;
    if (file["config"].contains("max_responses"))
    {
        int max_responses = file["config"]["max_responses"];
        // std::cout << max_responses;
        return max_responses;
    }
    else return 5;
};

std::vector<std::string> ConverterJSON::GetRequests()
{
    std::ifstream req("../resources/config/requests.json");
    nlohmann::json file;
    req >> file;
    std::vector<std::string> requests;
    int num_req = file["requests"].size();
    for (int i = 0; i < num_req; i++)
    {
        requests.push_back(file["requests"][i]);
    }
    return requests;
};

std::string RequestIdentifier(int num)
{
    std::string request = "request";
    int number[3] = {0, 0, 0};
    if (num < 10)
        number[2] = num;
    else if (num < 100)
        number[2] = num % 10, number[1] = num / 10;
    else if (num < 1000)
        number[2] = num % 10, number[1] = num / 10 % 10, number[0] = num / 100;
    else
        number[0] = -1;

    for (int i = 0; i < 3; i++)
    {
        if (number[i] == -1)
            request + std::to_string(1000);
        else
        {
            request += std::to_string(number[i]);
        }
    }
    return request;
}
void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> answers)
{
    // чистим файл
    std::ofstream ofs;
    ofs.open("../resources/config/answers.json", std::ofstream::trunc);
    ofs.close();

    nlohmann::json answer;

    int num_req = answers.size();
    for (int i = 0; i < num_req; i++)
    {
        nlohmann::json request;
        if (answers[i].size() >= 1)
        {
            request["result"] = "true";
            std::vector<nlohmann::json> relevance;
            int limit = GetResponsesLimit();
            int limit_ans = answers[i].size();
            int num_ans = (limit_ans < limit) ? limit_ans : limit;

            for (int j = 0; j < num_ans; j++)
            {
                nlohmann::json relev;
                relev["docid"] = answers[i][j].doc_id;
                relev["rank"] = answers[i][j].rank;
                relevance.push_back(relev);
            }

            request["relevance"] = relevance;
        }
        else
            request["result"] = "false";
        std::string id_request = RequestIdentifier(i + 1);
        answer[id_request] = request;
    }

    nlohmann::json file_content;
    file_content["answers"] = answer;

    std::ofstream ofs1("../resources/config/answers.json");
    ofs1 << std::setw(4) << file_content;
    ofs1.close();
};
