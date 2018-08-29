#include "parser.hpp"
#include <iostream>
int main(){
    parser p("/home/erick/Documentos/DATA_SEARCH_ENGINE/raw.es/spanishText_20000_25000");
    std::vector<retrieval_data> docs;
    p.get_documents(docs);
    std::cout<<docs.size()<<" #Docs..."<<std::endl;
}