/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-02 10:58
 * update_at: 2026-11-02 10:58
 */
// brute-dfs-optimize.cpp：暴力 + 跳跃，比 brute.cpp 快很多。
//
// 关键观察：以 a[i] 开头的这一局，最左端那张点数 a[i] 的牌会一直留着。
// 设 j 是 a[i] 在序列中最后一次出现的位置，那么打出第 j 张牌时，
// 桌面上 a[i] 右侧的牌全部被收走，所以中间 i+1..j-1 这一段对最终桌面没有任何贡献，可以整段跳过。
// 之后序列里不再出现 a[i]，它永久留下，右侧的局面与「从 j+1 开始打一局」完全相同。
//
// 于是定义 dfs(i)：从位置 i 开始一局，把这一局最终留在桌面上的点数压进栈。
//   dfs(i):  st.push(a[i]);  if (last[a[i]] + 1 <= n) dfs(last[a[i]] + 1);
// 每局只沿着这条「跳转链」走到底，链长通常远小于 n，比逐张模拟省时间。
// 最坏情况（序列两两不同）链长仍是 O(n)，总 O(n^2)，所以仍然只适用于小数据。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 5;
int n, m;
int a[maxn];
int ans[maxn];

int last[maxn];  // last[v]：点数 v 在序列中最后一次出现的位置
int nxt[maxn];   // nxt[i]：dfs(i) 的下一站 = last[a[i]] + 1，0 表示没有下一站

stack<int> st;   // 当前这局留在桌面上的牌，栈底 = 桌面最左端

// 从位置 i 开始一局，沿跳转链走到底，把留下的点数压栈
void dfs(int i) {
    st.push(a[i]);            // 这一局最左端就是 a[i]，它会一直留下
    int j = nxt[i];           // i+1..j-1 整段被收走，直接从 j 继续
    if (j != 0) dfs(j);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        last[a[i]] = i;             // 从左到右扫，最后一次赋值就是最后一次出现
    }
    for (int i = 1; i <= n; ++i) {
        int j = last[a[i]] + 1;     // 下一局开始的位置
        nxt[i] = (j <= n ? j : 0);
    }

    for (int i = 1; i <= n; ++i) {  // 第 i 局：从 a[i] 开始
        while (!st.empty()) st.pop();   // 清空桌面
        dfs(i);
        while (!st.empty()) {           // 栈里就是本局结束时桌上的点数
            ++ans[st.top()];
            st.pop();
        }
    }

    for (int v = 1; v <= m; ++v) {
        cout << ans[v] << (v == m ? '\n' : ' ');
    }
    return 0;
}
