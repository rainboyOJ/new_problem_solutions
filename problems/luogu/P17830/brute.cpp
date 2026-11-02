/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-11-02 09:20
 */
// brute.cpp：照题面直接模拟每一局。
// 桌面用 stack<int> 表示：栈底是桌面最左端，栈顶是桌面最右端。
// in_stack[v] 这个桶表示「点数 v 是否在桌上」，用来判断要不要收牌。
// 每局 O(n)，总 O(n^2)，只适用于小数据。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 5;
int n, m;
int a[maxn];
int ans[maxn];

bool in_stack[maxn];  // in_stack[v]：点数 v 是否在桌上（任意时刻每种点数至多一张）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    stack<int> st;                        // 桌面上的牌，栈顶 = 最右端

    for (int i = 1; i <= n; ++i) {        // 第 i 局：依次打出 a[i..n]
        // 每局开始桌面是空的：上一局结束时已经弹出所有牌并把 in_stack 清回 false

        for (int j = i; j <= n; ++j) {
            int k = a[j];
            if (in_stack[k]) {
                // 桌面上有点数 k：从最右端一直弹，直到把 k 也弹掉（含 k 及其右侧全部收走）
                while (true) {
                    int t = st.top();
                    st.pop();
                    in_stack[t] = false;
                    if (t == k) break;
                }
            }
            // 新打出的这张牌放到最右端
            st.push(k);
            in_stack[k] = true;
        }

        // 本局结束：栈里剩下的就是留在桌面上的牌，逐个计入答案，顺便清空栈
        while (!st.empty()) {
            ++ans[st.top()];
            in_stack[st.top()] = false;
            st.pop();
        }
    }

    for (int v = 1; v <= m; ++v) {
        cout << ans[v] << (v == m ? '\n' : ' ');
    }
    return 0;
}
