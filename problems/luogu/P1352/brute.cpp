#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据枚举每个员工是否参加，检查上下级冲突。

const int MAXN = 25;

int n;
int happy[MAXN];
int child_node[MAXN], parent_node[MAXN];
int choose_flag[MAXN];
int answer;

void dfs_enum(int pos) {
    if (pos == n + 1) {
        for (int i = 1; i < n; i++) {
            if (choose_flag[child_node[i]] && choose_flag[parent_node[i]]) {
                return;
            }
        }

        int sum = 0;
        for (int i = 1; i <= n; i++) {
            if (choose_flag[i]) {
                sum += happy[i];
            }
        }
        answer = max(answer, sum);
        return;
    }

    choose_flag[pos] = 0;
    dfs_enum(pos + 1);
    choose_flag[pos] = 1;
    dfs_enum(pos + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> happy[i];
    }
    for (int i = 1; i < n; i++) {
        cin >> child_node[i] >> parent_node[i];
    }

    answer = 0;
    dfs_enum(1);
    cout << answer << '\n';

    return 0;
}
