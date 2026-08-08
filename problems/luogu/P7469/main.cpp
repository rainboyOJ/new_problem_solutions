#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;

int n;
string s, t;

int nxt_pos[MAXN][26]; // nxt_pos[i][c] 表示在 s 中位置 i 之后，第一个字符 c 出现的位置
int max_len[MAXN];     // max_len[i] 表示后缀 t[i..n] 的最长前缀，有多长能作为 s 的子序列
int lcp[MAXN][MAXN];   // lcp[i][j] 表示后缀 t[i..n] 和 t[j..n] 的最长公共前缀长度
int sa[MAXN];          // 按字典序排序后的后缀起点

// 比较两个后缀 t[x..n] 和 t[y..n] 的字典序。
bool suffix_less(int x, int y) {
    if (x == y) {
        return false;
    }
    int same = lcp[x][y];
    int len_x = n - x + 1;
    int len_y = n - y + 1;
    if (same == len_x || same == len_y) {
        return len_x < len_y;
    }
    return t[x + same] < t[y + same];
}

// 构造 s 的子序列自动机。
void build_next_position() {
    for (int c = 0; c < 26; c++) {
        nxt_pos[n][c] = n + 1;
        nxt_pos[n + 1][c] = n + 1;
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int c = 0; c < 26; c++) {
            nxt_pos[i][c] = nxt_pos[i + 1][c];
        }
        nxt_pos[i][s[i + 1] - 'a'] = i + 1;
    }
}

// 计算每个起点 i 能向右延伸多长，仍然可以作为 s 的子序列。
void build_max_len() {
    for (int i = 1; i <= n; i++) {
        int pos = 0;
        int len = 0;
        for (int j = i; j <= n; j++) {
            pos = nxt_pos[pos][t[j] - 'a'];
            if (pos == n + 1) {
                break;
            }
            len++;
        }
        max_len[i] = len;
    }
}

// 预处理任意两个后缀的 LCP。
void build_lcp() {
    for (int i = n; i >= 1; i--) {
        for (int j = n; j >= 1; j--) {
            if (t[i] == t[j]) {
                lcp[i][j] = lcp[i + 1][j + 1] + 1;
            }
            else {
                lcp[i][j] = 0;
            }
        }
    }
}

long long solve() {
    build_next_position();
    build_max_len();
    build_lcp();

    for (int i = 1; i <= n; i++) {
        sa[i] = i;
    }
    sort(sa + 1, sa + n + 1, suffix_less);

    long long answer = 0;
    for (int i = 1; i <= n; i++) {
        int cur = sa[i];
        int cover = 0;
        for (int j = 1; j < i; j++) {
            int pre = sa[j];
            int same = lcp[cur][pre];
            if (same > max_len[pre]) {
                same = max_len[pre];
            }
            if (same > cover) {
                cover = same;
            }
        }
        if (max_len[cur] > cover) {
            answer += max_len[cur] - cover;
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s >> t;
    s = " " + s;
    t = " " + t;

    cout << solve() << '\n';

    return 0;
}
