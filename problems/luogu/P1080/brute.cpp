// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

struct Person {
    long long left_num;
    long long right_num;
};

int n;
Person king, people[MAXN];
int order_id[MAXN];

__int128 calc_order() {
    __int128 product = king.left_num;
    __int128 worst = 0;

    for (int i = 0; i < n; i++) {
        int id = order_id[i];
        worst = max(worst, product / people[id].right_num);
        product *= people[id].left_num;
    }

    return worst;
}

void print_int128(__int128 x) {
    if (x == 0) {
        cout << 0 << '\n';
        return;
    }
    string s;
    while (x > 0) {
        s.push_back((char)('0' + x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> king.left_num >> king.right_num;
    for (int i = 0; i < n; i++) {
        cin >> people[i].left_num >> people[i].right_num;
        order_id[i] = i;
    }

    __int128 ans = -1;
    do {
        __int128 now = calc_order();
        if (ans == -1 || now < ans) {
            ans = now;
        }
    } while (next_permutation(order_id, order_id + n));

    print_int128(ans);
    return 0;
}
