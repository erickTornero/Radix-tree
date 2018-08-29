#ifndef __PARSER__
#define __PARSER__

#include <fstream>
#include <iostream>
struct retrieval_data{
    std::string contain;
    std::string file_location;
    int key;
};
class parser{
    private:
    std::string File_dir;
    bool get_head(){
        
    }

    public:
    parser(std::string f): File_dir(f){};
    retrieval_data get_nex_Document(int counter){
        std::ifstream file_open(File_dir, std::ifstream::binary);
        std::string line;
        while(std::getline(file_open, line)){
            std::cout<<line<<std::endl;
        }
        file_open.close();
    }
};
#endif
