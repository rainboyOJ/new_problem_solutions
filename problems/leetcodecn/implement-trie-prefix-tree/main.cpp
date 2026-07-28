#include <bits/stdc++.h>
using namespace std;
class Trie {
    array<Trie*, 26> next = {};
    bool end = false;
public:
    Trie() {}
    void insert(string word) {
        auto cur = this;
        for (char ch : word) {
            int c = ch - 'a';
            if (!cur->next[c]) cur->next[c] = new Trie();
            cur = cur->next[c];
        }
        cur->end = true;
    }
    bool search(string word) {
        auto cur = this;
        for (char ch : word) {
            int c = ch - 'a';
            if (!cur->next[c]) return false;
            cur = cur->next[c];
        }
        return cur->end;
    }
    bool startsWith(string prefix) {
        auto cur = this;
        for (char ch : prefix) {
            int c = ch - 'a';
            if (!cur->next[c]) return false;
            cur = cur->next[c];
        }
        return true;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int q; cin >> q;
    Trie trie;
    while (q--) {
        string op, s; cin >> op >> s;
        if (op == "insert") trie.insert(s);
        else if (op == "search") cout << trie.search(s) << ' ';
        else cout << trie.startsWith(s) << ' ';
    }
    return 0;
}
