/**
 * Problem: luogu P1155 - [NOIP 2008 提高组] 双栈排序
 * Author: rainboy
 * Date: 2026-11-11 00:25
 * Description: 后缀最值互斥建图 + 二分图判定与染色 + 贪心排序操作序列
 */
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 1005;

int n;
int a[MAXN];
int suf[MAXN];
vector<int> g[MAXN];
bool vis[MAXN];
int col[MAXN];
char ans_ops[MAXN * 4];
int tot = 0;

void dfs(int u, int c) {
    vis[u] = true;
    col[u] = c;
    for (int v : g[u]) {
        if (vis[v]) {
            if (col[v] == col[u]) {
                cout << 0 << "\n";
                exit(0);
            }
        } else {
            dfs(v, c ^ 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // 后缀最小值
    int min_val = a[n];
    for (int i = n - 1; i > 1; --i) {
        for (int j = i - 1; j >= 1; --j) {
            if (a[j] < a[i] && min_val < a[j]) {
                g[a[j]].push_back(a[i]);
                g[a[i]].push_back(a[j]);
            }
        }
        min_val = min(min_val, a[i]);
    }

    // 二分图染色
    for (int i = 1; i <= n; ++i) {
        if (!vis[a[i]]) {
            dfs(a[i], 0);
        }
    }

    // 双栈模拟
    stack<int> s1, s2;
    int expected = 1;

    for (int i = 1; i <= n; ++i) {
        if (col[a[i]] == 0) {
            ans_ops[++tot] = 'a';
            s1.push(a[i]);
        } else {
            ans_ops[++tot] = 'c';
            s2.push(a[i]);
        }

        while ((!s1.empty() && s1.top() == expected) || (!s2.empty() && s2.top() == expected)) {
            if (!s1.empty() && s1.top() == expected) {
                ans_ops[++tot] = 'b';
                s1.pop();
                expected++;
            } else {
                ans_ops[++tot] = 'd';
                s2.pop();
                expected++;
            }
        }
    }

    // 局部操作交换优化字典序：若出现 'c' 后面紧跟 'b'，或 'd' 后面紧跟 'a'，由于两者操作的栈互不干扰且元素不同，可交换以获得更小字典序
    for (int i = tot - 1; i >= 1; --i) {
        for (int j = i; j < tot; ++j) {
            if ((ans_ops[j] == 'c' && ans_ops[j + 1] == 'b') || (ans_ops[j] == 'd' && ans_ops[j + 1] == 'a')) {
                swap(ans_ops[j], ans_ops[j + 1]);
            } else {
                break;
            }
        }
    }

    for (int i = 1; i <= tot; ++i) {
        cout << ans_ops[i] << (i == tot ? "" : " ");
    }
    cout << "\n";

    return 0;
}
