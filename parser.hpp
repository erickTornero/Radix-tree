#ifndef __PARSER__
#define __PARSER__

#include <fstream>
#include <iostream>
#include <vector>
struct retrieval_data{
    std::string contain;
    std::string file_location;
    int key;
    retrieval_data(int _k, std::string c, std::string f_l):key(_k), contain(c), file_location(f_l){};
};
class parser{
    private:
    std::string File_dir;
    bool get_head(const std::string & s, int & c){
        if(s.size() > 3){
            if(s.substr(0,4) == "<doc")
            {
                c++;
                return true;
            }
        }
    }

    bool get_eo_doc(const std::string & s){
        if(s.substr(0,6) == "</doc>")
            return true;
        return false;
    }
    public:
    parser(std::string f): File_dir(f){};
    bool get_nex_Document(int & counter, std::ifstream & file_open, std::vector<retrieval_data> & ans){
        //std::ifstream file_open(File_dir, std::ifstream::binary);
        std::string line;
        int ccc = 0;
        do{
            if(!std::getline(file_open, line))
                return false;
                        
        }while(!get_head(line,ccc));
        //Get Id of Document
        std::size_t found = line.find("id=");
        std::size_t start_pos = found + 3;
        std::size_t found_start_number = line.find('"',start_pos)+1;
        std::size_t found_finish_number = line.find('"',found_start_number);
        std::string id_str = line.substr(found_start_number,found_finish_number-found_start_number);
        //std::cout<<ccc<<""<<found<<std::endl;
        //Get text of document
        std::string content = "";
        while(true){
            if(!std::getline(file_open, line))
                return false;
            if(!get_eo_doc(line) ){
                if(line.substr(0,12) != "ENDOFARTICLE" && line != ""){
                    content.append(line);
                }
            }
            else{
                break;
            }
        }
        //std::getline(file_open,line);
        //file_open.close();
        ans.push_back(retrieval_data(std::stol(id_str), content, this->File_dir));
        return true;
    }
    void get_documents(std::vector<retrieval_data> & ans){
        std::ifstream file_open(File_dir, std::ifstream::binary);
        int cc ;
        while(get_nex_Document(cc, file_open, ans)){

        }
        file_open.close();
    }
};
#endif
