#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接按每个位置模拟。
// 0 表示老树，1 表示空地，2 表示树苗。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, n;
    cin >> L >> n;

    vector<int> state(L + 1, 0);
    int removed_saplings = 0;

    for (int i = 1; i <= n; i++) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 0) {
            for (int j = l; j <= r; j++) {
                if (state[j] == 2) {
                    removed_saplings++;
                }
                state[j] = 1;
            }
        } else {
            for (int j = l; j <= r; j++) {
                if (state[j] == 1) {
                    state[j] = 2;
                }
            }
        }
    }

    int final_saplings = 0;
    for (int i = 0; i <= L; i++) {
        if (state[i] == 2) {
            final_saplings++;
        }
    }

    cout << final_saplings << '\n' << removed_saplings << '\n';
    return 0;
}
