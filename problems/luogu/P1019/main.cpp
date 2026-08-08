#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
string word[MAXN];
int len_word[MAXN];
int best_overlap[MAXN][MAXN];  // i 接 j 时，最优的重叠长度
int used[MAXN];                // 每个单词最多使用两次
char start_ch;
int ans = 0;

// 判断 s 的后 k 个字符和 t 的前 k 个字符是否相同。
bool same_overlap(const string &s, const string &t, int k) {
    int len_s = (int)s.size();
    for (int i = 0; i < k; i++) {
        if (s[len_s - k + i] != t[i]) {
            return false;
        }
    }
    return true;
}

// 对于一对单词，只保留“最小的正重叠长度”。
// 因为重叠越小，当前增加的长度越大；
// 而后续转移只和“最后一个单词是谁”有关，和本次具体重叠了多少无关。
int get_best_overlap(int i, int j) {
    int limit = min(len_word[i], len_word[j]) - 1;
    for (int k = 1; k <= limit; k++) {
        if (same_overlap(word[i], word[j], k)) {
            return k;
        }
    }
    return 0;
}

void dfs(int last, int cur_len) {
    if (cur_len > ans) {
        ans = cur_len;
    }

    for (int nxt = 1; nxt <= n; nxt++) {
        if (used[nxt] >= 2) {
            continue;
        }
        if (best_overlap[last][nxt] == 0) {
            continue;
        }

        used[nxt]++;
        dfs(nxt, cur_len + len_word[nxt] - best_overlap[last][nxt]);
        used[nxt]--;
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

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            best_overlap[i][j] = get_best_overlap(i, j);
        }
    }

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
