/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，每轮重新扫描全部序列统计词汇对，只适合小数据验证合并规则。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, vocabulary_size;
    cin >> n >> vocabulary_size;
    vector<string> words(n);
    vector<long long> frequency(n);
    bool exists[26] = {};
    for (int i = 0; i < n; i++) {
        cin >> words[i] >> frequency[i];
        for (int j = 0; j < (int)words[i].size(); j++) exists[words[i][j] - 'a'] = true;
    }

    // 初始词表：出现过的字母各占一个编号
    vector<string> vocabulary;
    int letter_token[26];
    for (int i = 0; i < 26; i++) letter_token[i] = -1;
    for (int i = 0; i < 26; i++) {
        if (exists[i]) {
            letter_token[i] = (int)vocabulary.size();
            vocabulary.push_back(string(1, (char)('a' + i)));
        }
    }

    // 把每个单词转成词汇编号序列
    vector<vector<int> > sequences(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)words[i].size(); j++) {
            sequences[i].push_back(letter_token[words[i][j] - 'a']);
        }
    }

    while ((int)vocabulary.size() < vocabulary_size) {
        // 每轮重新统计全部相邻词汇对的加权出现次数
        map<pair<int, int>, long long> count;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j + 1 < (int)sequences[i].size(); j++) {
                count[make_pair(sequences[i][j], sequences[i][j + 1])] += frequency[i];
            }
        }
        if (count.empty()) break;

        // 选出最优词汇对：权重最大，同权重按题目规则比较拼接串
        pair<int, int> best_pair = count.begin()->first;
        long long best_weight = count.begin()->second;
        for (map<pair<int, int>, long long>::iterator iterator = count.begin(); iterator != count.end(); ++iterator) {
            pair<int, int> candidate = iterator->first;
            long long candidate_weight = iterator->second;
            bool better = false;
            if (candidate_weight != best_weight) {
                better = candidate_weight > best_weight;
            } else {
                size_t candidate_length = vocabulary[candidate.first].size() + vocabulary[candidate.second].size();
                size_t best_length = vocabulary[best_pair.first].size() + vocabulary[best_pair.second].size();
                if (candidate_length != best_length) {
                    better = candidate_length < best_length;
                } else if (vocabulary[candidate.first].size() != vocabulary[best_pair.first].size()) {
                    better = vocabulary[candidate.first].size() < vocabulary[best_pair.first].size();
                } else {
                    string candidate_text = vocabulary[candidate.first] + vocabulary[candidate.second];
                    string best_text = vocabulary[best_pair.first] + vocabulary[best_pair.second];
                    if (candidate_text != best_text) {
                        better = candidate_text < best_text;
                    } else {
                        better = candidate < best_pair;
                    }
                }
            }
            if (better) {
                best_pair = candidate;
                best_weight = candidate_weight;
            }
        }

        // 生成新词汇，并把所有序列中的该相邻对替换成新词汇
        int merged_token = (int)vocabulary.size();
        vocabulary.push_back(vocabulary[best_pair.first] + vocabulary[best_pair.second]);
        for (int i = 0; i < n; i++) {
            vector<int> next_sequence;
            for (int j = 0; j < (int)sequences[i].size();) {
                if (j + 1 < (int)sequences[i].size() && sequences[i][j] == best_pair.first
                        && sequences[i][j + 1] == best_pair.second) {
                    next_sequence.push_back(merged_token);
                    j += 2;
                } else {
                    next_sequence.push_back(sequences[i][j]);
                    j++;
                }
            }
            sequences[i].swap(next_sequence);
        }
    }

    int output_count = min(vocabulary_size, (int)vocabulary.size());
    for (int i = 0; i < output_count; i++) cout << vocabulary[i] << '\n';
    return 0;
}