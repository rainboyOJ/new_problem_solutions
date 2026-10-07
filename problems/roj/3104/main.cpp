/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:57
 * update_at: 2026-10-06 18:57
 */

#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXP = 1005; // a_i 最大为 1000

int sg[MAXP]; // sg[p] 表示单堆 p 颗魔法珠的 SG 值

// 计算 sg[1..MAXP-1]，sg[1] = 0
void init_sg() {
    sg[1] = 0; // 1 没有真约数，无法操作，SG 为 0
    for (int p = 2; p < MAXP; ++p) {
        // 枚举 p 的全部真约数
        vector<int> divisors;
        for (int i = 1; i * i <= p; ++i) {
            if (p % i == 0) {
                if (i < p) divisors.push_back(i);
                int j = p / i;
                if (j != i && j < p) divisors.push_back(j);
            }
        }
        // nx = 全部真约数对应 SG 值的异或和
        int nx = 0;
        for (int d : divisors) nx ^= sg[d];
        // 收集每个后继局面的 SG 值：删掉真约数 e 后，剩余堆的异或和为 nx ^ sg[e]
        bool vis[128] = {false}; // SG 值很小，用数组做 mex 标记
        for (int e : divisors) vis[nx ^ sg[e]] = true;
        int mex = 0;
        while (vis[mex]) ++mex;
        sg[p] = mex;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init_sg();
    int n;
    while (cin >> n) {
        int xorsum = 0;
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            xorsum ^= sg[a];
        }
        cout << (xorsum ? "freda" : "rainbow") << '\n';
    }
    return 0;
}
