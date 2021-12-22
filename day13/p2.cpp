#include <cstdio>
#include <ncurses.h>
#include "lib.hpp"
#include <unistd.h>

int main() {
    Dots dots;
    std::cin>>dots;
    //std::cerr<<dots;

    Folds folds;
    std::cin>>folds;
    //std::cerr<<folds;

    for(auto& fold: folds) {
        if (fold.x != 0) {
            fold_left(fold.x, dots);
        } else if (fold.y != 0) {
            fold_up(fold.y, dots);
        }
    }

    std::cerr<<dots<<std::endl;
    std::cout.flush();
    std::cerr.flush();

    initscr();
    clear();
    noecho();
    leaveok(stdscr, true);
    scrollok(stdscr, false);
    for(auto& dot: dots) {
        mvprintw(dot.y, dot.x, "*");
    }
    refresh();
    sleep(5);
    endwin(); //fixme: clear screen in pipe
    return 0;
}