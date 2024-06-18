#include <map>

namespace trie {

template<int N>
struct trie {
    struct trieNode {
        std::map<char, int> children;
        int type;
    } t[N];
    int tot = 1;

    void insert(const std::string& text, int type = 1) {
        int u = 1;
        for (auto& character : text) {
            if (!t[u].children[character]) {
                t[u].children[character] = ++tot;
            }
            u = t[u].children[character];
        }
        t[u].type |= type;
    }

    int queryNode(const std::string& text) {
        int u = 1;
        for (auto& character : text) {
            if (!t[u].children[character]) {
                return 0;
            }
            u = t[u].children[character];
        }
        return u;
    }

    int queryType(const std::string& text) {
        return t[queryNode(text)].type;
    }

    int count(int u, int type, const std::function<int(int, int)>& relation) {
        int sum = relation(t[u].type, type);
        for (auto& child : t[u].children) {
            sum += countType(child.second, type, relation);
        }
        return sum;
    }

    int countEQType(int u, int type) {
        return count(u, type, [](int a, int b) {
            return a == b;
        });
    }

    int countSubsetType(int u, int type) {
        return count(u, type, [](int a, int b) {
            return (a & b) == a;
        });
    }

    int countSupersetType(int u, int type) {
        return count(u, type, [](int a, int b) {
            return (a & b) == b;
        });
    }
};

}