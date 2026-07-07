#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n;
int a[MAXN]; // 导弹高度序列

int longest_non_increasing() {
    vector<int> tail;
    for (int i = 1; i <= n; i++) {
        int x = -a[i];
        vector<int>::iterator it = upper_bound(tail.begin(), tail.end(), x);
        if (it == tail.end()) {
            tail.push_back(x);
        } else {
            *it = x;
        }
    }
    return (int)tail.size();
}

int longest_increasing() {
    vector<int> tail;
    for (int i = 1; i <= n; i++) {
        int x = a[i];
        vector<int>::iterator it = lower_bound(tail.begin(), tail.end(), x);
        if (it == tail.end()) {
            tail.push_back(x);
        } else {
            *it = x;
        }
    }
    return (int)tail.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> a[n + 1]) {
        n++;
    }

    cout << longest_non_increasing() << '\n';
    cout << longest_increasing() << '\n';
    return 0;
}
