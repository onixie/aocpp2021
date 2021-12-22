#include "lib.hpp"

int main() {
    Dots dots;
    std::cin>>dots;
    std::cerr<<dots;

    Folds folds;
    std::cin>>folds;
    std::cerr<<folds;

    for(auto& fold: folds) {
        if (fold.x != 0) {
            fold_left(fold.x, dots);
            std::cout<<dots.size()<<std::endl;
        } else if (fold.y != 0) {
            fold_up(fold.y, dots);
            std::cout<<dots.size()<<std::endl;
        }
        break;
    }
    
    return 0;
}