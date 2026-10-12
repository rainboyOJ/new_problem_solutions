/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:38
 * update_at: 2026-10-12 14:55
 */
// main.cpp：排序 + 相邻 LCP 计数求单词查找树结点数（不建树）。
//
// 最少结点数 = 去重后的不同前缀个数（含根）。字典序排序后，
// 第 i 个单词与前面所有单词 LCP 的最大值就是它与前一单词的 LCP，
// 所以它新贡献的结点数 = 长度 - 与前一单词的最长公共前缀，重复单词贡献 0。

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

const int maxn = 20005; // 文件总长 32K，每个单词至少 1 字母 + 换行，单词数不超过 2 万

string word[maxn]; // 所有单词，读入后整体排序
ll cnt;            // 单词个数

// 读入全部单词：每行一个，按空白切分
void read_words() {
    while (cin >> word[cnt]) {
        cnt++;
    }
}

// a、b 的最长公共前缀长度：逐位比较，遇到第一个不同的字母就停
ll lcp(const string &a, const string &b) {
    ll la = a.size(); // 长度声明成 ll，就不用再做强制转换
    ll lb = b.size();
    ll i = 0;
    while (i < la && i < lb && a[i] == b[i]) {
        i++;
    }
    return i;
}

// 排序后统计结点数：1 + Σ(单词长度 - 与前一单词的 LCP)，1 是根结点
ll count_nodes() {
    sort(word, word + cnt);
    ll ans = 1 + word[0].size(); // 第一个单词贡献它的全部前缀
    for (ll i = 1; i < cnt; i++) {
        ll len = word[i].size();
        ans += len - lcp(word[i], word[i - 1]); // 重复单词 LCP 等于长度，贡献 0
    }
    return ans;
}

void solve() {
    read_words();
    cout << count_nodes() << endl;
}

int main() {
    solve();
    return 0;
}
