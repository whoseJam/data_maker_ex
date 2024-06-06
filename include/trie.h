#include <map>

namespace trie {

template<int N>
struct trie {
    struct trieNode {
        std::map<char, trieNode*> children;
    } t[N];
    void insert(const std::string& text) {
        int u = 1;
        for (auto& character : text) {
            if (!children[character]) {
                children[]
            }
        }
    }
};

}