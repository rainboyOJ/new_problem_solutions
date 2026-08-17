/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
int code[MAXN][15]; // code[i][k] 仓库 i 的第 k 维位置编码

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int k = 0; k < m; k++) cin >> code[i][k];
    }

    // 对每个仓库，按编号递增的顺序找第一个满足条件的上级
    for (int i = 1; i <= n; i++) {
        int parent = 0;
        for (int j = 1; j <= n; j++) {
            if (i == j) continue; // 不能是自己
            bool greater = true;
            // 每一维都必须严格大于
            for (int k = 0; k < m; k++) {
                if (code[j][k] <= code[i][k]) {
                    greater = false;
                    break;
                }
            }
            if (greater) {
                parent = j;
                break; // 编号最小且可行，直接停止
            }
        }
        cout << parent << '\n';
    }

    return 0;
}