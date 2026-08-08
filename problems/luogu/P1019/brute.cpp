#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
string word[MAXN];
int len_word[MAXN];
vector<int> overlap_list[MAXN][MAXN];  // 记录所有合法重叠长度
int used[MAXN];
char start_ch;
int ans = 0;

bool same_overlap(const string &s, const string &t, int k) {
    int len_s = (int)s.size();
    for (int i = 0; i < k; i++) {
        if (s[len_s - k + i] != t[i]) {
            return false;
        }
    }
    return true;
}

void build_overlap_list() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            overlap_list[i][j].clear();
            int limit = min(len_word[i], len_word[j]) - 1;
            for (int k = 1; k <= limit; k++) {
                if (same_overlap(word[i], word[j], k)) {
                    overlap_list[i][j].push_back(k);
                }
            }
        }
    }
}

// 暴力：每次不仅枚举下一个单词，还枚举本次采用哪一种合法重叠长度。
void dfs(int last, int cur_len) {
    if (cur_len > ans) {
        ans = cur_len;
    }

    for (int nxt = 1; nxt <= n; nxt++) {
        if (used[nxt] >= 2) {
            continue;
        }
        int sz = (int)overlap_list[last][nxt].size();
        for (int i = 0; i < sz; i++) {
            int overlap_len = overlap_list[last][nxt][i];
            used[nxt]++;
            dfs(nxt, cur_len + len_word[nxt] - overlap_len);
            used[nxt]--;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> word[i];
        len_word[i] = (int)word[i].size();
    }
    cin >> start_ch;

    build_overlap_list();

    for (int i = 1; i <= n; i++) {
        if (word[i][0] != start_ch) {
            continue;
        }
        memset(used, 0, sizeof(used));
        used[i] = 1;
        dfs(i, len_word[i]);
    }

    cout << ans << '\n';
    return 0;
}
