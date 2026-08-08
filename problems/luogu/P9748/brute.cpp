#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> apples;
    for (int i = 1; i <= n; ++i) {
        apples.push_back(i);
    }

    int day = 0;
    int removed_day = 0;
    while (!apples.empty()) {
        ++day;
        vector<int> next_apples;
        for (int i = 0; i < (int)apples.size(); ++i) {
            int pos = i + 1;
            if (pos % 3 == 1) {
                if (apples[i] == n) {
                    removed_day = day;
                }
            } else {
                next_apples.push_back(apples[i]);
            }
        }
        apples = next_apples;
    }

    cout << day << ' ' << removed_day << '\n';
    return 0;
}
