#include <bits/stdc++.h>
using namespace std;

bool seen[256][256]; // seen[suit][rank] 表示这种花色和点数的牌是否已经出现

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int distinct_count = 0;
    for (int i = 1; i <= n; i++) {
        string card;
        cin >> card;
        char suit = card[0];
        char rank = card[1];
        if (!seen[(int)suit][(int)rank]) {
            seen[(int)suit][(int)rank] = true;
            distinct_count++;
        }
    }

    cout << 52 - distinct_count << '\n';
    return 0;
}
