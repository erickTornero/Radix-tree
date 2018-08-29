#ifndef __PARSER__
#define __PARSER__

#include <fstream>
#include <iostream>
#include <vector>
struct retrieval_data{
    std::string contain;
    std::string file_location;
    std::string title;
    unsigned int db_index;
    retrieval_data(int _db_i, std::string _t, std::string c, std::string f_l):db_index(_db_i), title(_t),contain(c), file_location(f_l){};
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
    void get_value_of(const std::string & query, const std::string & line, std::string & val){
        std::size_t found = line.find(query);
        std::size_t start_pos = found + query.size();
        std::size_t found_start_number = line.find('"',start_pos)+1;
        std::size_t found_finish_number = line.find('"',found_start_number);
        val = line.substr(found_start_number,found_finish_number-found_start_number);
    }
    void get_value_of(const std::string & query, const std::string & line, unsigned int & val){
        std::string value;
        get_value_of(query,line,value);
        val = std::stol(value);
    }
    public:
    parser(std::string f): File_dir(f){};
    bool get_nex_Document(std::ifstream & file_open, std::vector<retrieval_data> & ans){
        //std::ifstream file_open(File_dir, std::ifstream::binary);
        std::string line;
        int ccc = 0;
        do{
            if(!std::getline(file_open, line))
                return false;
                        
        }while(!get_head(line,ccc));
        unsigned int dbindex;
        get_value_of("dbindex=",line,dbindex);
        std::string title;
        get_value_of("title=",line,title);
        //Get Id of Document
        /*std::size_t found = line.find("id=");
        std::size_t start_pos = found + 3;
        std::size_t found_start_number = line.find('"',start_pos)+1;
        std::size_t found_finish_number = line.find('"',found_start_number);
        std::string id_str = line.substr(found_start_number,found_finish_number-found_start_number);
        */
        //std::cout<<ccc<<""<<found<<std::endl;
        //Get text of document
        std::string content = "";
        while(true){
            if(!std::getline(file_open, line))
                return false;
            if(!get_eo_doc(line) ){
                if(line.substr(0,12) != "ENDOFARTICLE"){
                    content.append(line);
                }
            }
            else{
                break;
            }
        }
        //std::cout<< title<<std::endl<<std::endl;
        //std::cout << content <<std::endl<<std::endl;

        ans.push_back(retrieval_data(dbindex, title, content, this->File_dir));
        return true;
    }
    void get_documents(std::vector<retrieval_data> & ans){
        std::ifstream file_open(File_dir, std::ifstream::binary);
        /*for(int i = 0; i < 20; i++){
            get_nex_Document(cc, file_open, ans);
        }*/
        while(get_nex_Document(file_open, ans)){

        }
        file_open.close();
    }
};
#endif
