#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n;
int a[MAXN];

bool greater_fraction(long long num1, long long den1, long long num2, long long den2) {
    return num1 * den2 > num2 * den1;
}

bool equal_fraction(long long num1, long long den1, long long num2, long long den2) {
    return num1 * den2 == num2 * den1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    long long best_num = -1;
    long long best_den = 1;
    vector<int> answer;

    for (int k = 1; k <= n - 2; k++) {
        long long sum = 0;
        int mn = 1000000000;

        // 直接暴力统计剩余题目的总分与最小值。
        for (int i = k + 1; i <= n; i++) {
            sum += a[i];
            mn = min(mn, a[i]);
        }

        long long current_num = sum - mn;
        long long current_den = n - k - 1;

        if (best_num == -1 || greater_fraction(current_num, current_den, best_num, best_den)) {
            best_num = current_num;
            best_den = current_den;
            answer.clear();
            answer.push_back(k);
        } else if (equal_fraction(current_num, current_den, best_num, best_den)) {
            answer.push_back(k);
        }
    }

    for (int i = 0; i < (int)answer.size(); i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
