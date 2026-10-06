/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:09
 * update_at: 2026-10-06 12:09
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
using namespace std;

typedef long long ll;

const int MAXN = 25;

int n;                  // 单词数
string word[MAXN];      // word[i]：第 i 个单词（下标从 0 开始）
int len[MAXN];          // len[i]：第 i 个单词的长度
char head_char;         // 龙开头的字母
int overlap[MAXN][MAXN]; // overlap[i][j]：词 j 接在词 i 后的最小合法重叠长度，-1 表示接不上
ll pow3[MAXN];          // pow3[i] = 3^i，用来把各词用量编码进一个整数
map<ll, ll> memo;       // memo[last * pow3[n] + code]：还能追加的最大字符数

// 计算 a 后接 b 的最小合法重叠长度；k 只试到 min(len)-1，自动排除整词包含
int min_overlap(const string &a, int len_a, const string &b, int len_b) {
    int lim = min(len_a, len_b);
    for (int k = 1; k < lim; k++) {
        if (a.compare(len_a - k, k, b, 0, k) == 0) {
            return k; // 找到最小可行重叠，重叠部分在龙里只计一次
        }
    }
    return -1; // 不允许零重叠直接拼接
}

// 词 last 收尾、各词已用次数由 code 的三进制位表示时，还能追加的最大字符数
ll dfs(int last, ll code) {
    ll key = last * pow3[n] + code;
    map<ll, ll>::iterator it = memo.find(key);
    if (it != memo.end()) {
        return it->second; // 相同状态只算一次
    }

    ll best = 0;
    for (int j = 0; j < n; j++) {
        if (overlap[last][j] < 0) {
            continue; // 这两词接不上
        }
        ll digit = (code / pow3[j]) % 3;
        if (digit == 2) {
            continue; // 每个单词最多出现两次
        }
        ll next_code = code + pow3[j]; // 第 j 个词多用一个
        ll gain = len[j] - overlap[last][j];
        best = max(best, gain + dfs(j, next_code));
    }

    memo[key] = best;
    return best;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> word[i];
        len[i] = word[i].size();
    }
    cin >> head_char;

    pow3[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow3[i] = pow3[i - 1] * 3;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            overlap[i][j] = min_overlap(word[i], len[i], word[j], len[j]);
        }
    }

    // 龙头：任一以 head_char 开头的词做第一个词，整词长度都计入
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (word[i][0] != head_char) {
            continue;
        }
        ll code = pow3[i]; // 第 i 个词用了一次
        ans = max(ans, len[i] + dfs(i, code));
    }

    cout << ans << endl;
    return 0;
}
