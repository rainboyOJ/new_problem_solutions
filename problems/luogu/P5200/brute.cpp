#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据直接模拟。
// 每次把队首奶牛插入到当前序列中合适的位置，直到整个序列有序。

bool is_sorted_vec(const vector<int> &a) {
    int m = (int) a.size();
    for (int i = 0; i + 1 < m; i++) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }
    return true;
}

int suffix_start(const vector<int> &a) {
    int n = (int) a.size();
    int start = n - 1;
    while (start > 0 && a[start - 1] < a[start]) {
        start--;
    }
    return start;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> answer;

    while (!is_sorted_vec(a)) {
        int start = suffix_start(a);
        int x = a[0];
        a.erase(a.begin());

        // 删除队首后，前面仍然保留 start-1 头未处理奶牛。
        // 再把 x 插到后缀有序段里第一个 >= x 的位置前面。
        int pos = start - 1;
        while (pos < (int) a.size() && a[pos] < x) {
            pos++;
        }

        answer.push_back(pos);
        a.insert(a.begin() + pos, x);
    }

    cout << answer.size() << '\n';
    for (int i = 0; i < (int) answer.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';

    return 0;
}
