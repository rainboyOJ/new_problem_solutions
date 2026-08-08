#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n;
int a[MAXN];
int suffix_min[MAXN];
long long suffix_sum[MAXN];

// 返回 true 表示 num1 / den1 > num2 / den2
bool greater_fraction(long long num1, long long den1, long long num2, long long den2) {
    return num1 * den2 > num2 * den1;
}

// 返回 true 表示 num1 / den1 == num2 / den2
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

    suffix_sum[n] = a[n];
    suffix_min[n] = a[n];
    for (int i = n - 1; i >= 1; i--) {
        suffix_sum[i] = suffix_sum[i + 1] + a[i];
        suffix_min[i] = min(suffix_min[i + 1], a[i]);
    }

    long long best_num = -1;
    long long best_den = 1;
    vector<int> answer;

    for (int start = 2; start <= n - 1; start++) {
        // 吃掉前 start-1 题后，剩下的是 [start, n]
        // 去掉这一段中的最小值，再对剩下的题求平均分。
        long long current_num = suffix_sum[start] - suffix_min[start];
        long long current_den = n - start;

        if (best_num == -1 || greater_fraction(current_num, current_den, best_num, best_den)) {
            best_num = current_num;
            best_den = current_den;
            answer.clear();
            answer.push_back(start - 1);
        } else if (equal_fraction(current_num, current_den, best_num, best_den)) {
            answer.push_back(start - 1);
        }
    }

    for (int i = 0; i < (int)answer.size(); i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
