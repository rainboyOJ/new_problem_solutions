// brute.cpp：按输入顺序逐个判断是否重复，再做朴素排序。
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;
vector<int> b;

void bubble_sort(vector<int> &v) {
    int sz = (int)v.size();
    for (int i = 0; i < sz; i++) {
        for (int j = 1; j < sz - i; j++) {
            if (v[j - 1] > v[j]) {
                swap(v[j - 1], v[j]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    for (int i = 0; i < (int)a.size(); i++) {
        bool ok = true;
        for (int j = 0; j < (int)b.size(); j++) {
            if (b[j] == a[i]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            b.push_back(a[i]);
        }
    }

    bubble_sort(b);

    cout << (int)b.size() << '\n';
    for (int i = 0; i < (int)b.size(); i++) {
        if (i) {
            cout << ' ';
        }
        cout << b[i];
    }
    cout << '\n';

    return 0;
}
