/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:58
 */
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
        if (text[i] != '.') {
            value = value * 10 + text[i] - '0';
        }
    }
    return value;
}

void erase_order(const Order &order, map<int, pair<long long, long long> > &book,
                 long long &total_buy, long long &total_sell) {
    if (order.type == "buy") {
        book[order.price].first -= order.amount;
        total_buy -= order.amount;
    } else {
        book[order.price].second -= order.amount;
        total_sell -= order.amount;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Order> orders(1);
    map<int, pair<long long, long long> > book;
    long long total_buy = 0;
    long long total_sell = 0;
    string operation;
    int line = 0;
    while (cin >> operation) {
        line++;
        if (operation == "cancel") {
            int index;
            cin >> index;
            if (orders[index].active) {
                erase_order(orders[index], book, total_buy, total_sell);
                orders[index].active = false;
            }
            continue;
        }

        string price_text;
        long long amount;
        cin >> price_text >> amount;
        Order order;
        order.type = operation;
        order.price = parse_price(price_text);
        order.amount = amount;
        order.active = true;
        if ((int)orders.size() <= line) {
            orders.resize(line + 1);
        }
        orders[line] = order;
        if (operation == "buy") {
            book[order.price].first += amount;
            total_buy += amount;
        } else {
            book[order.price].second += amount;
            total_sell += amount;
        }
    }

    long long best_volume = -1;
    int best_price = 0;
    long long buy_volume = total_buy;
    long long sell_volume = 0;
    for (map<int, pair<long long, long long> >::iterator it = book.begin(); it != book.end(); ++it) {
        if (it->second.first == 0 && it->second.second == 0) {
            continue;
        }
        sell_volume += it->second.second;
        long long volume = min(buy_volume, sell_volume);
        if (volume >= best_volume) {
            best_volume = volume;
            best_price = it->first;
        }
        buy_volume -= it->second.first;
    }

    if (best_volume < 0) {
        best_volume = 0;
    }
    cout << best_price / 100 << '.' << setw(2) << setfill('0') << best_price % 100;
    cout << ' ' << best_volume << '\n';
    return 0;
}
