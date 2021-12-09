#include "lib.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

void guess(Experiment const& exp, Knowledge2& knowledge2);
void solve(Knowledge2 const& k2, Knowledge3& k3);

int main() {
    Experiment exp;

    size_t count = 0;
    do {
    Knowledge2 knowledge2;
    Knowledge3 knowledge3;
    std::cin>>exp;
    
    while(true) {
        guess(exp, knowledge2);
        solve(knowledge2, knowledge3);
        if (knowledge2.size() == 10 || knowledge3.size() == 7)
            break;
    }

    int disdig = 0;
    std::cerr<<exp<<" ( ";
    for(auto digit: std::get<1>(exp)) {
        for(auto kp: knowledge2) {
            std::vector<char> s1;
            std::copy(digit.begin(), digit.end(), std::back_inserter(s1));
            std::sort(s1.begin(), s1.end());
            std::vector<char> s2;
            std::copy(kp.second.begin(), kp.second.end(), std::back_inserter(s2));
            std::sort(s2.begin(), s2.end());
            if (s1 == s2) {
                std::cerr<<kp.first;
                disdig = kp.first + disdig * 10;
            }
        }
    }
    count+=disdig;
    std::cerr<<" )"<<std::endl;
    
    std::cerr<<knowledge2<<std::endl;
    std::cerr<<knowledge3<<std::endl;
    } while (!std::cin.eof());

    std::cout<<count<<std::endl;
    return 0;
}

void guess(Experiment const& exp, Knowledge2& k2) {
    std::array<Display, 14> digits;
    std::copy(
        std::get<1>(exp).cbegin(), 
        std::get<1>(exp).cend(), 
        std::copy(
            std::get<0>(exp).cbegin(), 
            std::get<0>(exp).cend(), 
            digits.begin()));
    std::for_each(digits.cbegin(), digits.cend(), [&k2](auto digit){
        int digit_len = digit.length();
        std::sort(digit.begin(), digit.end());
        //std::cerr<<digit_len<<std::endl;
        switch (digit_len) {
            case 2: //1
            case 4: //4
            case 3: //7
            case 7: //8
                for(auto c : digit)
                    k2[knowledge1[digit_len]].insert(c);
                break;
            case 6: // 6, 9, 0
                if (k2.find(1) != k2.end()) { // known 1, get 6
                    std::vector<char> tmp;
                    std::set_difference(digit.begin(), digit.end(), k2.at(1).begin(), k2.at(1).end(), std::back_inserter(tmp));
                    if (tmp.size() == 5) {
                        for(auto c : digit)
                            k2[6].insert(c);
                    }
                }
                if (k2.find(7) != k2.end()) { // known 7, get 6
                    std::vector<char> tmp;
                    std::set_difference(digit.begin(), digit.end(), k2.at(7).begin(), k2.at(7).end(), std::back_inserter(tmp));
                    if (tmp.size() == 4) {
                        for(auto c : digit)
                            k2[6].insert(c);
                    }
                }
                if (k2.find(4) != k2.end()) { // known 4, get 9
                    std::vector<char> tmp;
                    std::set_difference(digit.begin(), digit.end(), k2.at(4).begin(), k2.at(4).end(), std::back_inserter(tmp));
                    if (tmp.size() == 2) {
                        for(auto c : digit)
                            k2[9].insert(c);
                    }
                }
                if (k2.find(5) != k2.end()) { // known 5, get 0
                    std::vector<char> tmp;
                    std::set_difference(k2.at(5).begin(), k2.at(5).end(), digit.begin(), digit.end(), std::back_inserter(tmp));
                    if (tmp.size() == 1) {
                        for(auto c : digit)
                            k2[0].insert(c);
                    }
                }
                break;
            case 5: // 2, 3, 5
                if (k2.find(1) != k2.end()) { // known 1, get 3
                    std::vector<char> tmp;
                    std::set_difference(digit.begin(), digit.end(), k2.at(1).begin(), k2.at(1).end(), std::back_inserter(tmp));
                    if (tmp.size() == 3) {
                        for(auto c : digit)
                            k2[3].insert(c);
                    }
                }
                if (k2.find(2) != k2.end()) { // known 2, get 3, 5
                    std::vector<char> tmp;
                    std::set_difference(digit.begin(), digit.end(), k2.at(2).begin(), k2.at(2).end(), std::back_inserter(tmp));
                    if (tmp.size() == 1) {
                        for(auto c : digit)
                            k2[3].insert(c);
                    }
                    else if (tmp.size() == 2) {
                        for(auto c : digit)
                            k2[5].insert(c);
                    }
                }

                if (k2.find(7) != k2.end()) { // known 7, get 3
                    std::vector<char> tmp;
                    std::set_difference(digit.begin(), digit.end(), k2.at(7).begin(), k2.at(7).end(), std::back_inserter(tmp));
                    if (tmp.size() == 2) {
                        for(auto c : digit)
                            k2[3].insert(c);
                    }
                }
                if (k2.find(4) != k2.end()) { // known 4, get 2
                    std::vector<char> tmp;
                    std::set_difference(digit.begin(), digit.end(), k2.at(4).begin(), k2.at(4).end(), std::back_inserter(tmp));
                    if (tmp.size() == 3) {
                        for(auto c : digit)
                            k2[2].insert(c);
                    }
                }
                if (k2.find(9) != k2.end()) { // known 9, get 2
                    std::vector<char> tmp;
                    std::set_difference(digit.begin(), digit.end(), k2.at(9).begin(), k2.at(9).end(), std::back_inserter(tmp));
                    if (tmp.size() == 1) {
                        for(auto c : digit)
                            k2[2].insert(c);
                    }
                }
                if (k2.find(6) != k2.end()) { // known 6, get 5
                    std::vector<char> tmp;
                    std::set_difference(k2.at(6).begin(), k2.at(6).end(), digit.begin(), digit.end(),  std::back_inserter(tmp));
                    if (tmp.size() == 1) {
                        for(auto c : digit)
                            k2[5].insert(c);
                    }
                }
                break;
        }
    });
}

void solve(Knowledge2 const& k2, Knowledge3& k3) {
    // if 1 and 7 known, we know what is a
    if (k2.find(1) != k2.end() && k2.find(7) != k2.end()) {
        std::vector<char> tmp;
        std::set_difference(k2.at(7).begin(), k2.at(7).end(), k2.at(1).begin(),k2.at(1).end(), std::back_inserter(tmp));
        k3['a'] = tmp[0];
    }

    // if 7, 4, and 9 known, we know what is g
    if (k2.find(7) != k2.end() && k2.find(4) != k2.end() && k2.find(9) != k2.end()) {
        std::vector<char> tmp1;
        std::vector<char> tmp2;
        std::set_union(k2.at(7).begin(), k2.at(7).end(), k2.at(4).begin(), k2.at(4).end(), std::back_inserter(tmp1));
        std::sort(tmp1.begin(), tmp1.end());
        std::set_difference(k2.at(9).begin(), k2.at(9).end(), tmp1.begin(), tmp1.end(), std::back_inserter(tmp2));
        k3['g'] = tmp2[0];
    }

    // if 8 and 9 known, we know what is e
    if (k2.find(8) != k2.end() && k2.find(9) != k2.end()) {
        std::vector<char> tmp;
        std::set_difference(k2.at(8).begin(), k2.at(8).end(), k2.at(9).begin(), k2.at(9).end(), std::back_inserter(tmp));
        k3['e'] = tmp[0];
    }

    // if 5 and 6 known, we know what is e
    if (k2.find(6) != k2.end() && k2.find(5) != k2.end()) {
        std::vector<char> tmp;
        std::set_difference(k2.at(6).begin(), k2.at(6).end(), k2.at(5).begin(), k2.at(5).end(), std::back_inserter(tmp));
        k3['e'] = tmp[0];
    }

    // if 8 and 9 known, we know what is c
    if (k2.find(6) != k2.end() && k2.find(8) != k2.end()) {
        std::vector<char> tmp;
        std::set_difference(k2.at(8).begin(), k2.at(8).end(), k2.at(6).begin(), k2.at(6).end(), std::back_inserter(tmp));
        k3['c'] = tmp[0];
    }
    // if 5 and 9 known, we know what is c
    if (k2.find(9) != k2.end() && k2.find(5) != k2.end()) {
        std::vector<char> tmp;
        std::set_difference(k2.at(9).begin(), k2.at(9).end(), k2.at(5).begin(), k2.at(5).end(), std::back_inserter(tmp));
        k3['c'] = tmp[0];
    }

    // if 8 and 0 known, we know what is d
    if (k2.find(0) != k2.end() && k2.find(8) != k2.end()) {
        std::vector<char> tmp;
        std::set_difference(k2.at(8).begin(), k2.at(8).end(), k2.at(0).begin(), k2.at(0).end(), std::back_inserter(tmp));
        k3['d'] = tmp[0];
    }

    // if 1 and 2 known, we know what is f
    if (k2.find(1) != k2.end() && k2.find(2) != k2.end()) {
        std::vector<char> tmp;
        std::set_difference(k2.at(1).begin(), k2.at(1).end(), k2.at(2).begin(), k2.at(2).end(), std::back_inserter(tmp));
        k3['f'] = tmp[0];
    }
    // if 7 and 2 known, we know what is f
    if (k2.find(7) != k2.end() && k2.find(2) != k2.end()) {
        std::vector<char> tmp;
        std::set_difference(k2.at(7).begin(), k2.at(7).end(), k2.at(2).begin(), k2.at(2).end(), std::back_inserter(tmp));
        k3['f'] = tmp[0];
    }
}