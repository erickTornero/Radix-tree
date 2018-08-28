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
class Node_radix{
    private:
    
    
    int number_childrens;
    int number_elements;
    std::vector<int> keys;
    std::string value;
    public: 
    Node_radix * father;
    std::vector<Node_radix* > childrens;
    Node_radix(bool __l, Node_radix * f = nullptr):is_leaf(__l),number_elements(0),number_childrens(0), father(f){};
    Node_radix(bool __l, std::string s, Node_radix * f = nullptr):is_leaf(__l),number_elements(0),number_childrens(0), value(s), father(f){};
    void push_child(std::string s){
        childrens.push_back(new Node_radix(true, s, this));
        number_childrens++;
    }
    std::string get_value(){return value;}
    void set_value(std::string s){value = s; }
    int get_children(){return number_childrens;}
    //bool is_leaf(){return is_leaf;}
    bool is_leaf;
};

class Radix_tree{
    private:
    Node_radix * root;
   
    void insert(const std::string & s, Node_radix * node){
        if(this->root ==nullptr){
            root = new Node_radix(false);
            root->push_child(s);
            return;
        }
        if(!node->is_leaf){
            bool wasInsert = false;
            for(int i = 0; i < node->get_children(); i++){
                int sim = get_maximum_similariy(s, node->childrens[i]->get_value());
                if(sim > 0){
                    Node_radix * newInterNode = new Node_radix(false, node->childrens[i]->get_value().substr(0,sim-1),node->father);
                    node->childrens[i]->set_value(node->childrens[i]->get_value().substr(0,sim-1));
                }
            }
            if(!wasInsert){
                node->push_child(s);
                
            }
        }
    }
    public:
    void insert(const std::string & s){
        insert(s, this->root);
    }
};


#endif