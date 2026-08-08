// brute.cpp：按题意直接模拟去重，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        vector<int> kept;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;

            bool exist = false;
            for (int j = 0; j < (int) kept.size(); j++) {
                if (kept[j] == x) {
                    exist = true;
                    break;
                }
            }
            if (!exist) {
                kept.push_back(x);
            }
        }

        for (int i = 0; i < (int) kept.size(); i++) {
            if (i) {
                cout << ' ';
            }
            cout << kept[i];
        }
        cout << '\n';
    }

    return 0;
}
