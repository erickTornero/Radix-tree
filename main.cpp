#include "Radix_trie.hpp"
#include "parser.hpp"
#include <iostream>
void print_answer(const std::vector<std::vector<doc_type> *> & ans){
    for(int i = 0; i < ans.size(); i++){
        std::cout <<"Doc: "<<i+1<<std::endl;
        for(int j = 0; j < ans[i]->size(); j++){
            std::cout << ans[i]->at(j).key<< "\t" <<ans[i]->at(j).file_direction<<std::endl; 
        }
    }
}
int main(){
    Radix_tree * tree = new Radix_tree();
    /*tree->insert("hola");
    tree->insert("holi");
    tree->insert("holac");*/
    tree->insert("doge", doc_type("File1", 23));
    tree->insert("dog", doc_type("File1", 18));
    tree->insert("dogo", doc_type("File2", 3));
    tree->insert("doctor", doc_type("File3", 24));
    tree->insert("dacia", doc_type("File3", 2));
    tree->insert("holi", doc_type("File4", 32));
    tree->insert("dogo", doc_type("File5", 11));

    std::vector<std::vector<doc_type> *> ans;
    tree->search("dogo",ans);
    print_answer(ans);
    parser p("/home/erick/Documentos/DATA_SEARCH_ENGINE/raw.es/spanishText_20000_25000");
    p.get_nex_Document(1);
    int xx = 21;
}