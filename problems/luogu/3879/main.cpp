#include <bits/stdc++.h>
using namespace std;

const int MAXNODE = 500005;

int trie[MAXNODE][26];
int node_cnt = 1; // 1 号点作为根

vector<int> belong[MAXNODE]; // belong[p] 记录单词 s 出现在了哪些文章里

int get_new_node() {
    ++node_cnt;
    return node_cnt;
}

// 把一个单词插入字典树，并把它出现的文章编号 article 记到结尾节点。
void insert_word(const string &s, int article) {
    int p = 1;
    for (int i = 0; i < (int) s.size(); i++) {
        int ch = s[i] - 'a';
        if (trie[p][ch] == 0) {
            trie[p][ch] = get_new_node();
        }
        p = trie[p][ch]; // p 成为当前前缀的唯一节点编号
    }

    if (belong[p].empty() || belong[p].back() != article) {
        belong[p].push_back(article);
    }
}

int find_word(const string &s) {
    int p = 1;
    for (int i = 0; i < (int) s.size(); i++) {
        int ch = s[i] - 'a';
        if (trie[p][ch] == 0) {
            return 0; // 路径断开，单词不在 Trie 中
        }
        p = trie[p][ch]; // p 成为当前前缀的唯一节点编号
    }
    return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int cnt;
        cin >> cnt;
        for (int j = 1; j <= cnt; j++) {
            string s;
            cin >> s;
            insert_word(s, i);
        }
    }

    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        string s;
        cin >> s;
        int p = find_word(s);

        if (p == 0 || belong[p].empty()) {
            cout << '\n';
            continue;
        }

        for (int j = 0; j < (int) belong[p].size(); j++) {
            if (j > 0) {
                cout << ' ';
            }
            cout << belong[p][j];
        }
        cout << '\n';
    }

    return 0;
}
