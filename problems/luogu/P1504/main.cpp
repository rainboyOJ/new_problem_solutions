#include <bits/stdc++.h>
using namespace std;

const int MAX_SUM = 10000 + 5;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> cnt(MAX_SUM, 0);
    int answer = 0;

    for (int i = 0; i < n; i++) {
        int x, sum = 0;
        while (cin >> x && x != -1) {
            sum += x;
            if (sum < MAX_SUM) {
                cnt[sum]++;
            }
        }
    }

    // 0 高度总是可行的；从高到低找第一个所有城堡都能达到的高度。
    for (int h = MAX_SUM - 1; h >= 1; h--) {
        if (cnt[h] == n) {
            answer = h;
            break;
        }
    }

    cout << answer << '\n';

    return 0;
}
