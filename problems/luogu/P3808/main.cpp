#include <bits/stdc++.h>
using namespace std;

const int MAXNODE = 1000005;
const int SIGMA = 26;

int n;
int trie[MAXNODE][SIGMA];
int fail_link[MAXNODE];
int end_count[MAXNODE]; // end_count[u] 表示有多少个模式串在 u 结尾
int node_cnt;
string text;

void insert_pattern(const string &s) {
    int u = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        int c = s[i] - 'a';
        if (trie[u][c] == 0) {
            node_cnt++;
            trie[u][c] = node_cnt;
        }
        u = trie[u][c];
    }
    end_count[u]++;
}

void build_ac_automaton() {
    queue<int> q;
    for (int c = 0; c < SIGMA; c++) {
        int v = trie[0][c];
        if (v != 0) {
            fail_link[v] = 0;
            q.push(v);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int c = 0; c < SIGMA; c++) {
            int v = trie[u][c];
            if (v != 0) {
                fail_link[v] = trie[fail_link[u]][c];
                q.push(v);
            } else {
                // 补全转移：失配时直接跳到 fail 后能走到的状态。
                trie[u][c] = trie[fail_link[u]][c];
            }
        }
    }
}

long long count_matched_patterns() {
    long long ans = 0;
    int u = 0;

    for (int i = 0; i < (int)text.size(); i++) {
        int c = text[i] - 'a';
        u = trie[u][c];

        // 沿 fail 链统计所有以当前位置结尾的模式串。
        // 统计过的节点标成 -1，保证同一个模式串编号只贡献一次。
        int p = u;
        while (p != 0 && end_count[p] != -1) {
            ans += end_count[p];
            end_count[p] = -1;
            p = fail_link[p];
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        insert_pattern(s);
    }
    cin >> text;

    build_ac_automaton();
    cout << count_matched_patterns() << "\n";

    return 0;
}
