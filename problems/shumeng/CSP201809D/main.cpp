/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:59
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
const int MAX_VALUE = 305;

int n;
int second_price[MAXN], first_price[MAXN];
signed char memo[MAXN][MAX_VALUE][MAX_VALUE];

bool possible(int position, int previous, int current) {
    if (position == n) {
        return (previous + current) / 2 == second_price[n];
    }
    signed char &result = memo[position][previous][current];
    if (result != -1) {
        return result;
    }

    int lower = 3 * second_price[position] - previous - current;
    for (int next = lower; next <= lower + 2; next++) {
        if (next >= 1 && next < MAX_VALUE && possible(position + 1, current, next)) {
            result = 1;
            return true;
        }
    }
    result = 0;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> second_price[i];
    }
    memset(memo, -1, sizeof(memo));

    bool found = false;
    for (int first = 1; first < MAX_VALUE && !found; first++) {
        for (int second = 1; second < MAX_VALUE; second++) {
            if ((first + second) / 2 != second_price[1]) {
                continue;
            }
            if (n == 2) {
                if ((first + second) / 2 == second_price[2]) {
                    first_price[1] = first;
                    first_price[2] = second;
                    found = true;
                    break;
                }
            } else if (possible(2, first, second)) {
                first_price[1] = first;
                first_price[2] = second;
                found = true;
                break;
            }
        }
    }

    for (int position = 2; position <= n - 1; position++) {
        int lower = 3 * second_price[position]
                - first_price[position - 1] - first_price[position];
        for (int next = lower; next <= lower + 2; next++) {
            if (next >= 1 && next < MAX_VALUE
                    && possible(position + 1, first_price[position], next)) {
                first_price[position + 1] = next;
                break;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << first_price[i];
    }
    cout << '\n';

    return 0;
}
