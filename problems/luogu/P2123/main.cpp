#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20005;

struct Person {
    long long left_num;
    long long right_num;
};

int n;
Person people[MAXN];

bool cmp_person(const Person &x, const Person &y) {
    bool x_front = x.left_num <= x.right_num;
    bool y_front = y.left_num <= y.right_num;
    if (x_front != y_front) {
        return x_front > y_front;
    }
    if (x_front) {
        return x.left_num < y.left_num;
    }
    return x.right_num > y.right_num;
}

void solve_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> people[i].left_num >> people[i].right_num;
    }

    sort(people + 1, people + n + 1, cmp_person);

    long long prefix_left = 0;
    long long last_reward = 0;
    for (int i = 1; i <= n; i++) {
        prefix_left += people[i].left_num;
        last_reward = max(last_reward, prefix_left) + people[i].right_num;
    }

    cout << last_reward << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_case();
    }

    return 0;
}
