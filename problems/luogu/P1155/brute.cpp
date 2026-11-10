/**
 * Problem: luogu P1155 - [NOIP 2008 提高组] 双栈排序 (Brute Force DFS)
 * Author: rainboy
 * Date: 2026-11-11 00:25
 * Description: DFS 回溯搜索字典序最小解
 */
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int n;
int a[1005];
string best_ops = "";
bool found = false;

void dfs(int idx, stack<int> s1, stack<int> s2, int cur, string ops) {
    if (found) return;

    if (cur > n) {
        best_ops = ops;
        found = true;
        return;
    }

    // 优先尝试 a: push s1
    if (idx <= n) {
        if (s1.empty() || s1.top() > a[idx]) {
            stack<int> ns1 = s1;
            ns1.push(a[idx]);
            dfs(idx + 1, ns1, s2, cur, ops + "a");
            if (found) return;
        }
    }

    // 尝试 b: pop s1
    if (!s1.empty() && s1.top() == cur) {
        stack<int> ns1 = s1;
        ns1.pop();
        dfs(idx, ns1, s2, cur + 1, ops + "b");
        if (found) return;
    }

    // 尝试 c: push s2
    if (idx <= n) {
        if (s2.empty() || s2.top() > a[idx]) {
            stack<int> ns2 = s2;
            ns2.push(a[idx]);
            dfs(idx + 1, s1, ns2, cur, ops + "c");
            if (found) return;
        }
    }

    // 尝试 d: pop s2
    if (!s2.empty() && s2.top() == cur) {
        stack<int> ns2 = s2;
        ns2.pop();
        dfs(idx, s1, ns2, cur + 1, ops + "d");
        if (found) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    stack<int> s1, s2;
    dfs(1, s1, s2, 1, "");

    if (!found) {
        cout << 0 << "\n";
    } else {
        for (size_t i = 0; i < best_ops.size(); ++i) {
            cout << best_ops[i] << (i + 1 == best_ops.size() ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
