/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-02 11:05
 * update_at: 2026-11-02 11:05
 */
// brute-dfs-optimize-0.cpp：暴力 + 跳跃（j 用 for 循环现找）。
//
// 关键观察：以 a[i] 开头的这一局，最左端那张点数 a[i] 的牌会一直留着。
// 打出 a[i] 最后一次出现的那张牌时，它右侧的牌全部被收走，
// 所以 i+1..j-1 这一段（j = a[i] 最后一次出现的位置）对最终桌面没有贡献，整段跳过。
// 之后不再出现 a[i]，它永久留下，右侧的局面就是「从 j+1 开始打一局」。
//
// 于是 dfs(i)：把 a[i] 压栈，再用 for 循环往后找最后一个相等的 a[j]，
// 然后 dfs(j+1)。比 brute.cpp 省掉了逐张牌的收牌模拟。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 5;
int n, m;
int a[maxn];
int ans[maxn];

stack<int> st;   // 当前这局留在桌面上的牌，栈底 = 桌面最左端

// 从位置 i 开始一局：a[i] 会一直留下，中间到它最后一次出现的位置全部跳过
void dfs(int i) {
    st.push(a[i]);                  // 本局最左端就是 a[i]

    int j = i;                      // 手动往后找 a[i] 最后一次出现的位置
    for (int t = i + 1; t <= n; ++t) {
        if (a[t] == a[i]) j = t;    // 一直更新，循环结束 j 就是最后一次出现
    }

    if (j + 1 <= n) dfs(j + 1);     // 中间 i+1..j-1 全被收走，从 j+1 继续
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    for (int i = 1; i <= n; ++i) {  // 第 i 局：从 a[i] 开始
        while (!st.empty()) st.pop();    // 清空桌面
        dfs(i);
        while (!st.empty()) {            // 栈里就是本局结束时桌上的点数
            ++ans[st.top()];
            st.pop();
        }
    }

    for (int v = 1; v <= m; ++v) {
        cout << ans[v] << (v == m ? '\n' : ' ');
    }
    return 0;
}
