/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-10 21:42
 * update_at: 2026-07-10 21:42
 */
#include <bits/stdc++.h>
using namespace std;

struct Rest {
    string city;
    int score, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<Rest> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].city >> a[i].score;
        a[i].id = i + 1;
    }

    sort(a.begin(), a.end(), [](const Rest &x, const Rest &y) {
        if (x.city != y.city) return x.city < y.city;
        return x.score > y.score;
    });

    for (auto &r : a) cout << r.id << '\n';

    return 0;
}
