/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-29 20:15
 * update_at: 2026-10-05 02:53
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 505;
char seq1[maxn]; // 第一条 DNA 序列
char seq2[maxn]; // 第二条 DNA 序列
double threshold; // 判定相关的阈值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> threshold >> seq1 >> seq2;

    ll length = strlen(seq1);
    ll same = 0; // 相同碱基对的个数
    for (ll i = 0; i < length; i++) {
        if (seq1[i] == seq2[i]) {
            same++;
        }
    }

    // 相同碱基对比例与阈值比较，注意含等号
    double ratio = 1.0 * same / length;
    if (ratio >= threshold) {
        cout << "yes" << "\n";
    } else {
        cout << "no" << "\n";
    }

    return 0;
}
