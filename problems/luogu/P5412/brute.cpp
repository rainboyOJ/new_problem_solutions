// brute.cpp：直接分成男女两组，再用朴素排序把两组身高从小到大排好。
#include <bits/stdc++.h>
using namespace std;

int T, n;
int sex_[2005];

int parse_height(const string &s) {
    int value = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '.') {
            continue;
        }
        value = value * 10 + (s[i] - '0');
    }
    return value;
}

void bubble_sort(vector<int> &a) {
    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 1; j < (int)a.size() - i; j++) {
            if (a[j - 1] > a[j]) {
                swap(a[j - 1], a[j]);
            }
        }
    }
}

void print_line(const vector<int> &a) {
    for (int i = 0; i < (int)a.size(); i++) {
        if (i) {
            cout << ' ';
        }
        cout << a[i] / 10 << '.' << a[i] % 10;
    }
    cout << '\n';
}

void solve_one_case() {
    vector<int> girls, boys;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> sex_[i];
    }

    for (int i = 1; i <= n; i++) {
        string s;
        int h;
        cin >> s;
        h = parse_height(s);
        if (sex_[i] == 0) {
            girls.push_back(h);
        }
        else {
            boys.push_back(h);
        }
    }

    bubble_sort(girls);
    bubble_sort(boys);

    print_line(girls);
    print_line(boys);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        solve_one_case();
    }

    return 0;
}
