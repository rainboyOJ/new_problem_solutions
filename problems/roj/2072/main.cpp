/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:20
 * update_at: 2026-10-06 11:21
 */
// main.cpp：roj 2072 字母游戏。
// 先用 26 位掩码淘汰含卡片外字母的单词，再用 26 维用量向量精筛，
// 最后在少量候选上枚举单字与词对，取最高分并输出全部并列方案。
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXW = 40005;

// 字母分值表，下标 = 字母 - 'a'
const int SCORE[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};

struct Item {
    string word;
    ll score;
    int usage[26]; // 该单词在 26 个字母上各用了几个
};

string cards;       // 手上的卡片串
string words[MAXW]; // 读入的字典单词
int word_cnt;

Item playing[MAXW]; // 通过粗筛与精筛的候选单词
int playing_cnt;

int card_usage[26]; // 卡片的 26 维用量
int card_mask;      // 卡片出现过的字母位掩码

// 单词里出现过哪些字母：第 i 位为 1 表示字母 'a' + i 出现过。
int word_mask(const string &w) {
    int m = 0;
    for (ll i = 0; i < (ll)w.size(); i++) {
        m |= (1 << (w[i] - 'a'));
    }
    return m;
}

// 单词得分 = 每个字母分值之和。
ll word_score(const string &w) {
    ll s = 0;
    for (ll i = 0; i < (ll)w.size(); i++) {
        s += SCORE[w[i] - 'a'];
    }
    return s;
}

// 统计卡片的字母掩码与 26 维用量（卡片可能有重复字母）。
void build_card() {
    for (ll i = 0; i < (ll)cards.size(); i++) {
        int idx = cards[i] - 'a';
        card_usage[idx]++;
        card_mask |= (1 << idx);
    }
}

void read_input() {
    // 标准输入第一段是卡片串，之后是字典单词，以 "." 结束；
    // 若只给了卡片，则按题面去读同目录的 lgame.dict。
    if (!(cin >> cards)) return;
    string w;
    while (cin >> w) {
        if (w == ".") break;
        words[++word_cnt] = w;
    }
    if (word_cnt == 0) {
        ifstream fin("lgame.dict");
        while (fin >> w) {
            if (w == ".") break;
            words[++word_cnt] = w;
        }
    }
}

void solve() {
    build_card();

    for (int i = 1; i <= word_cnt; i++) {
        string w = words[i];
        if (word_mask(w) & ~card_mask) continue; // 含卡片外的字母，直接淘汰

        Item cur;
        cur.word = w;
        cur.score = word_score(w);
        for (int t = 0; t < 26; t++) cur.usage[t] = 0;
        for (ll j = 0; j < (ll)w.size(); j++) cur.usage[w[j] - 'a']++;

        bool enough = true; // 精筛：逐个字母比较卡片用量，掩码挡不住重复字母
        for (int t = 0; t < 26; t++) {
            if (cur.usage[t] > card_usage[t]) {
                enough = false;
                break;
            }
        }
        if (enough) playing[++playing_cnt] = cur;
    }

    ll best = 0; // 先取单字基线
    for (int i = 1; i <= playing_cnt; i++) {
        if (playing[i].score > best) best = playing[i].score;
    }
    vector<string> winners;
    for (int i = 1; i <= playing_cnt; i++) {
        if (playing[i].score == best) winners.push_back(playing[i].word);
    }

    // 词对枚举：下标 i <= j，同一单词可重复使用，也避免同一对换序重复
    for (int i = 1; i <= playing_cnt; i++) {
        for (int j = i; j <= playing_cnt; j++) {
            ll sum = playing[i].score + playing[j].score;
            if (sum < best) continue; // 追不平当前最高分，不必再比用量

            bool enough = true;
            for (int t = 0; t < 26; t++) {
                if (playing[i].usage[t] + playing[j].usage[t] > card_usage[t]) {
                    enough = false;
                    break;
                }
            }
            if (!enough) continue;

            if (sum > best) { // 刷新纪录：清空旧答案
                best = sum;
                winners.clear();
            }
            winners.push_back(playing[i].word + " " + playing[j].word);
        }
    }

    sort(winners.begin(), winners.end());
    cout << best << "\n";
    for (ll i = 0; i < (ll)winners.size(); i++) {
        cout << winners[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
