#ifndef _LIB_HPP_
#define _LIB_HPP_
namespace day2 {
enum class Dir {
    Forward, Up, Down
};

struct Command {
    Dir dir;
    uint moves;
};

extern std::ostream& operator<<(std::ostream& out, Dir const& dir);
extern std::ostream& operator<<(std::ostream& out, Command const& cmd);
extern std::istream& operator>>(std::istream& in, Dir& dir);
extern std::istream& operator>>(std::istream& in, Command& cmd);
}
#endif // _LIB_HPP_