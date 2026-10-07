/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:20
 * update_at: 2026-10-04 22:20
 */
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

const int LIM = 200; // 题面数据范围 2 ≤ N,M ≤ 200

int sg[LIM + 1][LIM + 1]; // sg[i][j]：i×j 的纸只保留安全剪法时的 SG 值
bool used[LIM * 2 + 5];   // mex 临时标记数组，范围够放所有异或值

// 按面积从小到大递推 SG 表；只保留剪开后两边长宽都 ≥2 的安全剪法
void build_sg() {
    for (int i = 2; i <= LIM; ++i) {
        for (int j = 2; j <= LIM; ++j) {
            // 枚举横向安全剪法：上、下两块高度都 ≥2
            for (int a = 2; a <= i - a; ++a) {
                used[sg[a][j] ^ sg[i - a][j]] = true;
            }
            // 枚举纵向安全剪法：左、右两块宽度都 ≥2
            for (int b = 2; b <= j - b; ++b) {
                used[sg[i][b] ^ sg[i][j - b]] = true;
            }
            // mex：不在 used 中的最小非负整数
            int g = 0;
            while (used[g]) ++g;
            sg[i][j] = g;
            // 清理本次用过的标记，只清实际用到的范围
            for (int a = 2; a <= i - a; ++a) used[sg[a][j] ^ sg[i - a][j]] = false;
            for (int b = 2; b <= j - b; ++b) used[sg[i][b] ^ sg[i][j - b]] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_sg();

    ll n, m;
    while (cin >> n >> m) {
        cout << (sg[n][m] ? "WIN" : "LOSE") << '\n';
    }
    return 0;
}
