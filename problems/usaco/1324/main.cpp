/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:31
 * update_at: 2026-07-11 16:35
 */
#include <bits/stdc++.h>
using namespace std;

vector<string> nouns;
vector<string> trans_verbs;
vector<string> intrans_verbs;
vector<string> conjs;

int T;
int n, comma_cnt, period_cnt;

string take_word(vector<string> &words) {
    string res = words.back();
    words.pop_back();
    return res;
}

void solve_one() {
    cin >> n >> comma_cnt >> period_cnt;

    nouns.clear();
    trans_verbs.clear();
    intrans_verbs.clear();
    conjs.clear();

    for (int i = 1; i <= n; i++) {
        string word, type;
        cin >> word >> type;
        if (type == "noun") {
            nouns.push_back(word);
        } else if (type == "transitive-verb") {
            trans_verbs.push_back(word);
        } else if (type == "intransitive-verb") {
            intrans_verbs.push_back(word);
        } else {
            conjs.push_back(word);
        }
    }

    int noun_total = (int)nouns.size();
    int trans_total = (int)trans_verbs.size();
    int intrans_total = (int)intrans_verbs.size();
    int conj_total = (int)conjs.size();

    int best_words = 0;
    int best_type1 = 0;
    int best_type2 = 0;
    int best_combine = 0;
    int best_extra = 0;

    for (int type1 = 0; type1 <= intrans_total; type1++) {
        for (int type2 = 0; type2 <= trans_total; type2++) {
            int used_nouns = type1 + 2 * type2;
            if (used_nouns > noun_total) continue;

            int sentence_cnt = type1 + type2;
            int combine = min(conj_total, sentence_cnt / 2);
            int need_period = sentence_cnt - combine;
            if (need_period > period_cnt) continue;

            int extra = 0;
            if (type2 > 0) {
                extra = min(comma_cnt, noun_total - used_nouns);
            }

            int words = 2 * type1 + 3 * type2 + combine + extra;
            if (words > best_words) {
                best_words = words;
                best_type1 = type1;
                best_type2 = type2;
                best_combine = combine;
                best_extra = extra;
            }
        }
    }

    cout << best_words << '\n';
    if (best_words == 0) {
        cout << '\n';
        return;
    }

    vector<string> basic_sentences;

    for (int i = 1; i <= best_type1; i++) {
        string sentence = take_word(nouns) + " " + take_word(intrans_verbs);
        basic_sentences.push_back(sentence);
    }

    for (int i = 1; i <= best_type2; i++) {
        string sentence = take_word(nouns) + " " + take_word(trans_verbs) + " " + take_word(nouns);
        basic_sentences.push_back(sentence);
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
        string sentence = basic_sentences[idx] + " " + take_word(conjs) + " " + basic_sentences[idx + 1] + ".";
        final_sentences.push_back(sentence);
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
