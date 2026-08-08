#include <bits/stdc++.h>
using namespace std;

struct Card {
    string suit_point;
    string kind;
};

int n, k, m, p;
vector<Card> deck;

vector<Card> shuffle_once(const vector<Card> &cur) {
    int len = (int) cur.size();
    int half = len / 2;
    vector<Card> nxt;

    // 朴素做法：直接按题目给出的顺序重新构造一副新牌。
    for (int i = 0; i < half; i++) {
        nxt.push_back(cur[half + i]);
        nxt.push_back(cur[i]);
    }

    if (len % 2 == 1) {
        nxt.push_back(cur[len - 1]);
    }

    return nxt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> m >> p;
    deck.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> deck[i].suit_point >> deck[i].kind;
    }

    if (k < 4 * n) {
        cout << "Error:cards not enough\n";
        return 0;
    }

    for (int i = 1; i <= m; i++) {
        deck = shuffle_once(deck);
    }

    for (int i = p - 1, cnt = 0; i < k && cnt < 4; i += n, cnt++) {
        cout << deck[i].suit_point << ' ' << deck[i].kind << '\n';
    }

    return 0;
}
