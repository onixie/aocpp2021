#include <iostream>
#include "lib.hpp"

using day2::Command, day2::Dir;

int main(){
    uint horizontal_pos = 0;
    int depth = 0;

    Command cmd;
    do {
        std::cin>>cmd;
        switch(cmd.dir) {
            case Dir::Forward:
            horizontal_pos+=cmd.moves;
            break;
            case Dir::Up:
            depth-=cmd.moves;
            break;
            case Dir::Down:
            depth+=cmd.moves;
            break;
        } 
        std::cerr<<cmd<<" "<<horizontal_pos<<" "<<depth<<std::endl;
    } while(!std::cin.eof());

    std::cout<<horizontal_pos*depth<<std::endl;
    return 0;
}