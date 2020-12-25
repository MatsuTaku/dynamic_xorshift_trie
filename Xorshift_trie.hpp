#ifndef XORSHIFT__xorshift_trie_HPP_
#define XORSHIFT__xorshift_trie_HPP_
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

#include "Xorshift.hpp"

namespace kuroda {

class xorshift_trie{
private:
kuroda::Xorshift shift;
static constexpr uint8_t kLeafChar = 0;

private:
//static constexpr uint8_t kLeafChar = '0';
int create_seed(int node, uint8_t c)const{
    return (node << 8) + c;
}

int node_count = 0; 
public:
void xor_try(const std::string& str) {
    int node = 0;
    int collision = 0;
    int parity = 0;
    //std::cout << "-----key_word-------" << str << std::endl;
    for (uint8_t c : str) {
        int t = shift.get_nextnode(create_seed(node,c));
        if(shift.exists[t]){    
            node = t;
            //std::cout << "--common--" << "\n";
        }
        else{
           // std::cout << "---new_node---" << std::endl;
            shift.set(create_seed(node,c));
            //std::cout << "new s : new t " << node << " --> " << t << std::endl;
            node = shift.get_nextnode(create_seed(node,c));//衝突回数の分修正する
            node_count++;
        }
    }
    //終端文字格納
    shift.set(create_seed(node,kLeafChar));
    node_count++;
    int t = shift.get_nextnode(create_seed(node,kLeafChar));
    shift.display();
    std::cout << "node : " << node_count << std::endl;
}


};

}

#endif //XORSHIFT__XORSHIFT_HPP_
