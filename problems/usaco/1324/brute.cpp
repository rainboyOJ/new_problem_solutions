/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:31
 * update_at: 2026-07-11 16:35
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int T;
int n, comma_cnt, period_cnt;
int noun_cnt, trans_cnt, intrans_cnt, conj_cnt;
vector<string> nouns;
vector<string> trans_verbs;
vector<string> intrans_verbs;
vector<string> conjs;

string take_word(vector<string> &words) {
    string res = words.back();
    words.pop_back();
    return res;
}

void construct_output(int best_words, int best_type1, int best_type2, int best_combine, int best_extra) {
    cout << best_words << '\n';
    if (best_words == 0) {
        cout << '\n';
        return;
    }

    vector<string> basic_sentences;
    for (int i = 1; i <= best_type1; i++) {
        basic_sentences.push_back(take_word(nouns) + " " + take_word(intrans_verbs));
    }
    for (int i = 1; i <= best_type2; i++) {
        basic_sentences.push_back(take_word(nouns) + " " + take_word(trans_verbs) + " " + take_word(nouns));
    }

    if (best_extra > 0) {
        int last = (int)basic_sentences.size() - 1;
        for (int i = 1; i <= best_extra; i++) {
            basic_sentences[last] += ", " + take_word(nouns);
        }
    }

    vector<string> final_sentences;
    int idx = 0;
    for (int i = 1; i <= best_combine; i++) {
        final_sentences.push_back(basic_sentences[idx] + " " + take_word(conjs) + " " + basic_sentences[idx + 1] + ".");
        idx += 2;
    }
    while (idx < (int)basic_sentences.size()) {
        final_sentences.push_back(basic_sentences[idx] + ".");
        idx++;
    }

    for (int i = 0; i < (int)final_sentences.size(); i++) {
        if (i > 0) cout << ' ';
        cout << final_sentences[i];
    }
    cout << '\n';
}

void solve_one() {
    int best_words = 0;
    int best_type1 = 0;
    int best_type2 = 0;
    int best_combine = 0;
    int best_extra = 0;

    // 小数据暴力：枚举一类句、二类句、连接词和额外名词数量。
    for (int type1 = 0; type1 <= intrans_cnt; type1++) {
        for (int type2 = 0; type2 <= trans_cnt; type2++) {
            for (int combine = 0; combine <= conj_cnt; combine++) {
                for (int extra = 0; extra <= comma_cnt; extra++) {
                    if (type1 + 2 * type2 + extra > noun_cnt) continue;
                    if (extra > 0 && type2 == 0) continue;

                    int sentence_cnt = type1 + type2;
                    if (combine > sentence_cnt / 2) continue;
                    if (sentence_cnt - combine > period_cnt) continue;

                    int words = 2 * type1 + 3 * type2 + combine + extra;
                    if (best_words < words) {
                        best_words = words;
                        best_type1 = type1;
                        best_type2 = type2;
                        best_combine = combine;
                        best_extra = extra;
                    }
                }
            }
        }
    }

    construct_output(best_words, best_type1, best_type2, best_combine, best_extra);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> comma_cnt >> period_cnt;
        noun_cnt = trans_cnt = intrans_cnt = conj_cnt = 0;
        nouns.clear();
        trans_verbs.clear();
        intrans_verbs.clear();
        conjs.clear();
        for (int i = 1; i <= n; i++) {
            string word, type;
            cin >> word >> type;
            if (type == "noun") {
                noun_cnt++;
                nouns.push_back(word);
            } else if (type == "transitive-verb") {
                trans_cnt++;
                trans_verbs.push_back(word);
            } else if (type == "intransitive-verb") {
                intrans_cnt++;
                intrans_verbs.push_back(word);
            } else {
                conj_cnt++;
                conjs.push_back(word);
            }
        }

        solve_one();
    }

    return 0;
}
