#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举所有人的座位排列，只适合 n<=5 的小数据验证。

int count_harmony(const vector<int> &seat_person, int n) {
    int row_of_person[12];
    for (int seat = 0; seat < 2 * n; seat++) {
        int person = seat_person[seat];
        row_of_person[person] = seat / 2;
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (row_of_person[2 * i] == row_of_person[2 * i + 1]) {
            cnt++;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> persons;
        for (int i = 0; i < 2 * n; i++) {
            persons.push_back(i);
        }
        long long answer = 0;
        do {
            if (count_harmony(persons, n) == k) {
                answer++;
            }
        } while (next_permutation(persons.begin(), persons.end()));
        cout << answer % 998244353 << '\n';
    }

    return 0;
}
