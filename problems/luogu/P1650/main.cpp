#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;

int n;
int tian[MAXN], king[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> tian[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> king[i];
    }

    sort(tian + 1, tian + n + 1);
    sort(king + 1, king + n + 1);

    int tl = 1, tr = n;
    int kl = 1, kr = n;
    int score = 0;

    while (tl <= tr) {
        if (tian[tr] > king[kr]) {
            score += 200;
            tr--;
            kr--;
        }
        else if (tian[tl] > king[kl]) {
            score += 200;
            tl++;
            kl++;
        }
        else {
            if (tian[tl] < king[kr]) {
                score -= 200;
            }
            tl++;
            kr--;
        }
    }

    cout << score << '\n';
    return 0;
}
