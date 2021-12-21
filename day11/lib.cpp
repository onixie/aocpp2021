#include "lib.hpp"

std::istream& operator>>(std::istream& in, Cavern& cave) {
    int row = 0;
    int col = 0;
    do {
        char c; in.get(c);

        if (in.eof()) {
            return in;
        }

        if (c == '\n' || c == '\r') {
            row++;
            col = 0;
            continue;
        }

        cave.octs[row][col++] = c - '0';
    } while (true);
    return in;
}

std::ostream& operator<<(std::ostream& out, Cavern const& map) {
    for(auto& row: map.octs) {
        for(auto& cell: row) {
            out<<static_cast<int>(cell)<<(cell.flashed ? '*' : ' ')<<" ";
        }
        out<<std::endl;
    }
    return out;
}

bool inc1(Oct& oct) {
    if (oct.flashed)
        return false;
    
    if (oct.c == 9) {
        oct.c = 0;
        oct.flashed = true;
        return true; /* flashing */
    }

    oct.c++;
    return false;
}

int visit(int col, int row, Cavern& cave) {
    if (col < 0 || col >= cave.octs[0].size() || row < 0 || row >= cave.octs.size())
        return 0;
        
    if (inc1(cave.octs[row][col])) {
        return 1 /* flash once */
        + visit(col+1, row-1, cave)
        + visit(col+1, row, cave)
        + visit(col+1, row+1, cave)
        + visit(col-1, row-1, cave)
        + visit(col-1, row, cave)
        + visit(col-1, row+1, cave)
        + visit(col, row+1, cave)
        + visit(col, row-1, cave);
    }

    return 0;
}

int visit_all(Cavern& cave) {
    int flash_cnt = 0;
    for(int row = 0; row < cave.octs.size(); row++) {
        for (int col = 0; col < cave.octs[0].size(); col++) {
            flash_cnt += visit(col, row, cave);
        }
    }
    return flash_cnt;
}

int step1(Cavern& cave) {
    auto ret = visit_all(cave);

    for(auto& row: cave.octs) {
        for(auto& cell: row) {
            cell.flashed = false;
        }
    }
    return ret;
}