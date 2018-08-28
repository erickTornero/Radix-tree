#include "Radix_trie.hpp"

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
    int xx = 21;
}