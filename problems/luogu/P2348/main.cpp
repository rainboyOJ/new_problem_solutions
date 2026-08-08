#include <bits/stdc++.h>
using namespace std;

const int MAXK = 100000 + 5;

struct Card {
    string suit_point;
    string kind;
};

int n, k, m, p;
Card a[MAXK], b[MAXK];

void shuffle_once() {
    int half = k / 2;
    int pos = 0;

    // 新牌堆按“后半张、前半张”交错放入。
    for (int i = 1; i <= half; i++) {
        b[++pos] = a[half + i];
        b[++pos] = a[i];
    }

    if (k % 2 == 1) {
        b[++pos] = a[k];
    }

    for (int i = 1; i <= k; i++) {
        a[i] = b[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> m >> p;
    for (int i = 1; i <= k; i++) {
        cin >> a[i].suit_point >> a[i].kind;
    }

    if (k < 4 * n) {
        cout << "Error:cards not enough\n";
        return 0;
    }

    for (int i = 1; i <= m; i++) {
        shuffle_once();
    }

    int need = 0;
    for (int i = p; i <= k && need < 4; i += n) {
        cout << a[i].suit_point << ' ' << a[i].kind << '\n';
        need++;
    }

    return 0;
}
