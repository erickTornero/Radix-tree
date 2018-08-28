#ifndef RADIX_TRIE
#define RADIX_TRIE
#include <string>
#include <vector>

int get_maximum_similariy(const std::string & s1, const std::string & s2){
    int c = 0;
    int sz = s1.size();
    if(s2.size() > sz)
        sz = s2.size();
    for(int i = 0; i < sz; i++){
        if(s1[i] == s2[i])
            c++;
        else
            break;
    }
    return c;
}
struct doc_type{
    std::string file_direction;
    int key;
    doc_type(std::string f = "", int k = 0):file_direction(f), key(k){};
};
class Node_radix{
    private:
    std::vector<doc_type> documents; 

    int number_childrens;
    int number_documents;
    std::string value;
    public: 
    Node_radix * father;
    std::vector<Node_radix* > childrens;
    Node_radix(bool __l, Node_radix * f = nullptr):number_documents(0),number_childrens(0), father(f){};
    Node_radix(bool __l, std::string s, Node_radix * f = nullptr):number_documents(0),number_childrens(0), value(s), father(f){};
    void push_child(std::string s, doc_type doc){
        Node_radix * my_node = new Node_radix(true, s, this);
        my_node->push_document(doc);
        childrens.push_back(my_node);
        //documents.push_back(doc);
        number_childrens++;
    }
    void push_child(Node_radix * node, doc_type doc){
        childrens.push_back(node);
        //documents.push_back(doc);
        number_childrens++;
    }
    void push_document(doc_type doc){
        this->documents.push_back(doc);
        number_documents++;
    }
    std::string get_value(){return value;}
    void set_value(std::string s){value = s; }
    int get_number_children(){return number_childrens;}
    int get_number_documents(){return number_documents;}

    int search_for_indx(std::string s, int & indx){
        int sim;
        for(int i = 0; i < this->get_number_children(); i++){
            sim = get_maximum_similariy(s, this->childrens[i]->get_value());
            if(sim > 0){
                indx = i;
                return sim;
            }
        }
        return 0;
    }
};

class Radix_tree{
    private:
    Node_radix * root;
   
    void insert(const std::string & s, Node_radix * node, doc_type doc){
        if(s != ""){
            if(this->root ==nullptr){
                root = new Node_radix(false);
                root->push_child(s, doc);
                return;
            }
        
            bool wasInsert = false;
            int index;
            int sim = node->search_for_indx(s, index);
            if(sim > 0){
                if(sim == node->childrens[index]->get_value().size())
                    insert(s.substr(sim,s.size()-1),node->childrens[index], doc);
                else{
                    Node_radix * newInterNode = new Node_radix(false, node->childrens[index]->get_value().substr(0,sim),node);
                    newInterNode->push_child(node->childrens[index], doc);
                    
                    node->childrens[index]->set_value(node->childrens[index]->get_value().substr(sim,node->get_value().size()-1));
                    node->childrens[index]->father = newInterNode;
                    node->childrens[index] = newInterNode;

                    std::string remaining = s.substr(sim, s.size());
                    if(remaining != "")
                        insert(s.substr(sim, s.size()), newInterNode, doc);
                    else
                        newInterNode->push_document(doc);
                }
            }
            else{
                node->push_child(s, doc);   
            }
        }
    }
    public:
    void insert(const std::string & s, doc_type doc){
        insert(s, this->root, doc);
    }
};


#endif