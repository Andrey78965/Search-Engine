#include "search_server.h"
#include "converter_json.h"
#include "inverted_index.h"
#include <iostream>
#include <exception>

int main()
{
    ConverterJSON converter;
    InvertedIndex idx;
    SearchServer server(idx);

    
    try 
    {
        auto docs = converter.GetTextDocuments();
        idx.UpdateDocumentBase(docs);
        auto requests = converter.GetRequests();
        auto server_answers = server.Search(requests);
        converter.putAnswers(server_answers);
    }
    catch (const std::exception& x)
    {
        std::cerr << "Caught: " << x.what() << std::endl;
    }
    

    
    //std::vector<std::vector<std::pair<int, float>>> answers;
}
