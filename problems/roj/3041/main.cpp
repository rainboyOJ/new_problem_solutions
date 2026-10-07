/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:32
 * update_at: 2026-10-06 11:32
 */
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

const int MAXN = 1000005; // 总长度不超过 1e6，结点数最多为总长 + 1

int trie[MAXN][26]; // trie[u][c] 表示结点 u 沿字符 c 的下一个结点编号
int cnt[MAXN];      // cnt[u] 表示以结点 u 结尾的字符串个数
int node_cnt;       // 当前 Trie 结点总数，结点 0 为根

// 把字符串 s 插入 Trie，并在结尾结点累加计数
void insert(const string &s) {
    int u = 0;
    for (size_t i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        if (trie[u][c] == 0) {
            trie[u][c] = ++node_cnt;
        }
        u = trie[u][c];
    }
    cnt[u]++;
}

// 查询有多少个模式串是 s 的前缀
int query(const string &s) {
    int u = 0;
    int ans = 0;
    for (size_t i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        if (trie[u][c] == 0) {
            break; // 当前前缀不再是任何模式串的前缀，后续也不可能
        }
        u = trie[u][c];
        ans += cnt[u];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }
    string s;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        insert(s);
    }
    for (int i = 1; i <= m; i++) {
        cin >> s;
        cout << query(s) << '\n';
    }
    return 0;
}
