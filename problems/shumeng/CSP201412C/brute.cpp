/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:45
 */
// brute.cpp：小数据暴力解，枚举每个有效报价并重新统计买卖量。
#include <bits/stdc++.h>
using namespace std;

struct Order {
    string type;
    int price;
    long long amount;
    bool active;
};

int parse_price(const string &text) {
    int value = 0;
    for (int i = 0; i < (int)text.size(); i++) {
        if (text[i] != '.') value = value * 10 + text[i] - '0';
    }
    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Order> orders(1);
    vector<int> candidates;
    string operation;
    int line = 0;
    while (cin >> operation) {
        line++;
        if (operation == "cancel") {
            int index;
            cin >> index;
            orders[index].active = false;
            continue;
        }
        string price_text;
        long long amount;
        cin >> price_text >> amount;
        if ((int)orders.size() <= line) orders.resize(line + 1);
        orders[line] = {operation, parse_price(price_text), amount, true};
        candidates.push_back(line);
    }

    long long best_volume = -1;
    int best_price = 0;
    for (int i = 0; i < (int)candidates.size(); i++) {
        Order &candidate = orders[candidates[i]];
        if (!candidate.active) continue;
        long long buy_volume = 0;
        long long sell_volume = 0;
        for (int j = 1; j < (int)orders.size(); j++) {
            if (!orders[j].active) continue;
            if (orders[j].type == "buy" && orders[j].price >= candidate.price) {
                buy_volume += orders[j].amount;
            }
            if (orders[j].type == "sell" && orders[j].price <= candidate.price) {
                sell_volume += orders[j].amount;
            }
        }
        long long volume = min(buy_volume, sell_volume);
        if (volume > best_volume || (volume == best_volume && candidate.price > best_price)) {
            best_volume = volume;
            best_price = candidate.price;
        }
    }
    if (best_volume < 0) best_volume = 0;
    cout << best_price / 100 << '.' << setw(2) << setfill('0') << best_price % 100;
    cout << ' ' << best_volume << '\n';
    return 0;
}
