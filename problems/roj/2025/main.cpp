/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:46
 * update_at: 2026-10-06 09:46
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 70;

int n, b, d;
int code[MAXN];      // 已选编码
int cnt;             // 已选个数

// 计算 x 与 y 的海明距离（不同二进制位的个数）
int hamming_dist(int x, int y) {
    int t = x ^ y;
    int res = 0;
    while (t) {
        res += t & 1;
        t >>= 1;
    }
    return res;
}

// 判断 x 与已选所有编码的海明距离是否都 >= d
bool valid(int x) {
    for (int i = 0; i < cnt; ++i) {
        if (hamming_dist(x, code[i]) < d)
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> b >> d)) return 0;

    int space = 1 << b;   // 编码取值范围 [0, 2^b)
    code[0] = 0;          // 最优解首项必为 0
    cnt = 1;

    for (int i = 1; i < n; ++i) {
        int nxt = -1;
        for (int x = code[cnt - 1] + 1; x < space; ++x) {
            if (valid(x)) {
                nxt = x;
                break;
            }
        }
        if (nxt == -1) break; // 空间不够，能选几个算几个
        code[cnt++] = nxt;
    }

    for (int i = 0; i < cnt; ++i) {
        if (i > 0 && i % 10 != 0) cout << ' ';
        cout << code[i];
        if ((i + 1) % 10 == 0) cout << '\n';
    }
    if (cnt % 10 != 0) cout << '\n';

    return 0;
}
