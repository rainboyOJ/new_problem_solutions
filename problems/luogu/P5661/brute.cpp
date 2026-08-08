#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;

struct Ticket {
    int price;
    int time;
    bool used;
};

int n;
int typ, price, tim;
long long ans;
vector<Ticket> tickets;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> typ >> price >> tim;

        if (typ == 0) {
            ans += price;
            tickets.push_back({price, tim, false});
            continue;
        }

        int choose = -1;
        for (int j = 0; j < (int) tickets.size(); j++) {
            if (tickets[j].used) {
                continue;
            }
            if (tim - tickets[j].time > 45) {
                continue;
            }
            if (tickets[j].price < price) {
                continue;
            }
            choose = j;
            break;
        }

        if (choose == -1) {
            ans += price;
        } else {
            tickets[choose].used = true;
        }
    }

    cout << ans << '\n';
    return 0;
}
