/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:32
 * update_at: 2026-10-06 09:32
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int cap[3]; // 三个桶的容量 A, B, C
bool vis[21][21][21]; // 状态 (a,b,c) 是否已访问

// 从 src 倒向 dst，返回新状态 (na, nb, nc)
void pour(int a, int b, int c, int src, int dst, int &na, int &nb, int &nc) {
    int milk[3] = {a, b, c};
    int volume = min(milk[src], cap[dst] - milk[dst]);
    milk[src] -= volume;
    milk[dst] += volume;
    na = milk[0]; nb = milk[1]; nc = milk[2];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> cap[0] >> cap[1] >> cap[2];

    // 用栈做 DFS，初始状态 (0, 0, C)
    int sa = 0, sb = 0, sc = cap[2];
    vis[sa][sb][sc] = true;

    // 用简单数组模拟栈，最多 441 个状态
    int stk[441][3];
    int top = 0;
    stk[top][0] = sa; stk[top][1] = sb; stk[top][2] = sc;
    top++;

    while (top > 0) {
        top--;
        int a = stk[top][0], b = stk[top][1], c = stk[top][2];
        // 6 种倒法：src != dst
        for (int src = 0; src < 3; src++) {
            for (int dst = 0; dst < 3; dst++) {
                if (src == dst) continue;
                int na, nb, nc;
                pour(a, b, c, src, dst, na, nb, nc);
                if (!vis[na][nb][nc]) {
                    vis[na][nb][nc] = true;
                    stk[top][0] = na; stk[top][1] = nb; stk[top][2] = nc;
                    top++;
                }
            }
        }
    }

    // 收集 A 为空时 C 的所有可能值，升序输出
    vector<int> ans;
    for (int c = 0; c <= cap[2]; c++) {
        for (int b = 0; b <= cap[1]; b++) {
            if (vis[0][b][c]) {
                ans.push_back(c);
                break; // 同一 c 只需一个 b 满足即可
            }
        }
    }

    for (size_t i = 0; i < ans.size(); i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
