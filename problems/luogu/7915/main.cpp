// main.cpp：固定第一个选择后，把剩余序列分成两段，贪心构造字典序最小方案。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n;
int a[MAXN];
int first_pos[MAXN], second_pos[MAXN];

bool same_pos_invalid(int x, int y) {
    return x == y;
}

bool build_answer(bool choose_left_first, string &answer) {
    int total = 2 * n;
    int first_value;
    int match_pos;
    char first_op, last_op;
    int l1, r1, l2, r2;

    if (choose_left_first) {
        first_value = a[1];
        match_pos = (first_pos[first_value] == 1) ? second_pos[first_value] : first_pos[first_value];
        first_op = 'L';
        last_op = 'L';
        l1 = 2;
        r1 = match_pos - 1;
        l2 = match_pos + 1;
        r2 = total;
    } else {
        first_value = a[total];
        match_pos = (first_pos[first_value] == total) ? second_pos[first_value] : first_pos[first_value];
        first_op = 'R';
        // 最后只剩一个元素时，L/R 都能取走；为了字典序取 L。
        last_op = 'L';
        l1 = 1;
        r1 = match_pos - 1;
        l2 = match_pos + 1;
        r2 = total - 1;
    }

    string left_ops, right_ops;
    left_ops.push_back(first_op);

    for (int step = 1; step <= n - 1; step++) {
        bool done = false;

        if (l1 <= r1) {
            if (l1 < r1 && a[l1] == a[r1]) {
                left_ops.push_back('L');
                right_ops.push_back('L');
                l1++;
                r1--;
                done = true;
            } else if (l2 <= r2 && a[l1] == a[l2]) {
                left_ops.push_back('L');
                right_ops.push_back('R');
                l1++;
                l2++;
                done = true;
            }
        }

        if (!done && l2 <= r2) {
            if (l1 <= r1 && a[r2] == a[r1]) {
                left_ops.push_back('R');
                right_ops.push_back('L');
                r2--;
                r1--;
                done = true;
            } else if (l2 < r2 && a[r2] == a[l2]) {
                left_ops.push_back('R');
                right_ops.push_back('R');
                r2--;
                l2++;
                done = true;
            }
        }

        if (!done) {
            return false;
        }
    }

    if (l1 <= r1 || l2 <= r2) {
        return false;
    }

    answer = left_ops;
    for (int i = (int)right_ops.size() - 1; i >= 0; i--) {
        answer.push_back(right_ops[i]);
    }
    answer.push_back(last_op);
    return true;
}

void solve_one() {
    cin >> n;
    int total = 2 * n;
    for (int i = 1; i <= n; i++) {
        first_pos[i] = second_pos[i] = 0;
    }

    for (int i = 1; i <= total; i++) {
        cin >> a[i];
        if (first_pos[a[i]] == 0) {
            first_pos[a[i]] = i;
        } else {
            second_pos[a[i]] = i;
        }
    }

    string answer;
    if (build_answer(true, answer)) {
        cout << answer << '\n';
        return;
    }
    if (build_answer(false, answer)) {
        cout << answer << '\n';
        return;
    }
    cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
