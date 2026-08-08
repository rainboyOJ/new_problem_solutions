// brute.cpp：直接枚举谁来主持，再暴力判断他是不是所有参与者的祖先。
// 这个做法最贴近题意，但每次查询都要逐个试人，只适合小数据。
#include <bits/stdc++.h>
using namespace std;

int n, q;
vector<int> parent_arr;

bool is_ancestor(int anc, int u) {
    while (true) {
        if (u == anc) {
            return true;
        }
        if (u == 0) {
            break;
        }
        u = parent_arr[u];
    }
    return anc == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    parent_arr.assign(n, 0);

    for (int i = 1; i < n; i++) {
        cin >> parent_arr[i];
    }

    cin >> q;
    while (q--) {
        int m;
        cin >> m;

        vector<int> people(m);
        for (int i = 0; i < m; i++) {
            cin >> people[i];
        }

        int answer = 0;
        for (int cand = 0; cand < n; cand++) {
            bool ok = true;
            for (int i = 0; i < m; i++) {
                if (!is_ancestor(cand, people[i])) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                answer = max(answer, cand);
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
