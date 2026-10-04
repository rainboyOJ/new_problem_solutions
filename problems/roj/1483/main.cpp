/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:50
 * update_at: 2026-10-05 03:50
 */
// roj 1483 最短母串（HNOI 2006）：状压 DP，状态记录「已用串集合 + 结尾串」。
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

const int MAXN = 12;
const int MAXMASK = 1 << MAXN; // n 最大 12，掩码总数 4096

int n;               // 去重并删掉被包含串之后，真正参与 DP 的串数
string str_list[MAXN]; // str_list[i] 表示第 i 个串（下标从 0 开始）

// tail_add[i][j] = 把 str_list[j] 接到 str_list[i] 后面时还需要补写的尾巴，
// 也就是 str_list[j] 去掉与 str_list[i] 后缀重合的最长前缀后剩下的部分。
string tail_add[MAXN][MAXN];

// dp[mask][j] = 已经包含 mask 中所有串、且以 str_list[j] 结尾的最短母串，
// 长度相同时保留字典序更小的那个；has_dp 标记该状态是否已经求出。
string dp[MAXMASK][MAXN];
bool has_dp[MAXMASK][MAXN];

// 比较两个母串的优劣：先比长度，长度相等再比字典序。
bool better(const string &a, const string &b) {
    if (a.size() != b.size()) {
        return a.size() < b.size();
    }
    return a < b;
}

// 求把 t 接到 s 后面需要补写的尾巴：先找最大的重合长度 k，
// 使 s 的后 k 个字符等于 t 的前 k 个字符，这段被吃掉，只写 t[k:]。
string get_tail(const string &s, const string &t) {
    ll limit = s.size() < t.size() ? s.size() : t.size();
    for (ll k = limit; k >= 1; k--) {
        if (s.compare(s.size() - k, k, t, 0, k) == 0) {
            return t.substr(k);
        }
    }
    return t;
}

// 读入并预处理：重复串只留一个，被别的串完全包含的串直接删掉
// （母串含住了大串就自动含住了它，留着只会白白增加状态）。
void read_input() {
    ll total;
    cin >> total;

    string raw_list[MAXN];
    int raw_cnt = 0;
    for (ll i = 0; i < total; i++) {
        string s;
        cin >> s;
        bool repeated = false;
        for (int j = 0; j < raw_cnt; j++) {
            if (raw_list[j] == s) {
                repeated = true;
                break;
            }
        }
        if (!repeated) {
            raw_list[raw_cnt] = s;
            raw_cnt++;
        }
    }

    for (int i = 0; i < raw_cnt; i++) {
        bool contained = false;
        for (int j = 0; j < raw_cnt; j++) {
            if (i == j) {
                continue;
            }
            if (raw_list[j].find(raw_list[i]) != string::npos) {
                contained = true;
                break;
            }
        }
        if (!contained) {
            str_list[n] = raw_list[i];
            n++;
        }
    }
}

void solve() {
    read_input();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tail_add[i][j] = get_tail(str_list[i], str_list[j]);
        }
    }

    // 单串自己就是一个起点状态。
    for (int i = 0; i < n; i++) {
        int mask = 1 << i;
        dp[mask][i] = str_list[i];
        has_dp[mask][i] = true;
    }

    // 按掩码从小到大递推：接上新串后掩码只会变大，所以顺序枚举即可。
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int j = 0; j < n; j++) {
            if (!has_dp[mask][j]) {
                continue;
            }
            for (int k = 0; k < n; k++) {
                if ((mask >> k) & 1) {
                    continue;
                }
                int next_mask = mask | (1 << k);
                string cand = dp[mask][j] + tail_add[j][k];
                if (!has_dp[next_mask][k] || better(cand, dp[next_mask][k])) {
                    dp[next_mask][k] = cand;
                    has_dp[next_mask][k] = true;
                }
            }
        }
    }

    int full = (1 << n) - 1;
    int best_end = -1;
    for (int j = 0; j < n; j++) {
        if (!has_dp[full][j]) {
            continue;
        }
        if (best_end == -1 || better(dp[full][j], dp[full][best_end])) {
            best_end = j;
        }
    }
    cout << dp[full][best_end] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
