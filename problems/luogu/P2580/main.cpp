#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXNODE = 500005;

int n, m;
int trie[MAXNODE][26];
bool is_end[MAXNODE];   // 这个节点是否对应某个合法姓名的结尾
bool called[MAXNODE];   // 这个姓名是否已经被点过
int node_cnt = 1;       // 1 号点作为根

// 把一个姓名插入字典树。
void insert_name(const string &s) {
    int p = 1;
    for (int i = 0; i < (int) s.size(); i++) {
        int ch = s[i] - 'a';
        if (trie[p][ch] == 0) {
            ++node_cnt;
            trie[p][ch] = node_cnt;
        }
        p = trie[p][ch];
    }
    is_end[p] = true;
}

// 查询当前姓名对应的终止节点。
// 如果不存在，返回 0。
int find_name(const string &s) {
    int p = 1;
    for (int i = 0; i < (int) s.size(); i++) {
        int ch = s[i] - 'a';
        if (trie[p][ch] == 0) {
            return 0;
        }
        p = trie[p][ch];
    }
    if (!is_end[p]) {
        return 0;
    }
    return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        insert_name(s);
    }

    cin >> m;
    for (int i = 1; i <= m; i++) {
        string s;
        cin >> s;
        int p = find_name(s);

        if (p == 0) {
            cout << "WRONG\n";
        } else if (!called[p]) {
            called[p] = true;
            cout << "OK\n";
        } else {
            cout << "REPEAT\n";
        }
    }

    return 0;
}
