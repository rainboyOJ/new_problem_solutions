/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 23:41
 */
#include <bits/stdc++.h>
using namespace std;

struct Token {
    string text;
};

struct Occurrence {
    int token;
    int word;
    int previous;
    int next;
    bool alive;
};

struct PairInfo {
    long long weight;
    int version;
    set<int> positions;

    PairInfo() : weight(0), version(0) {}
};

struct HeapEntry {
    unsigned long long key;
    long long weight;
    int version;
};

vector<Token> token_table;
vector<Occurrence> occurrence;
vector<long long> word_frequency;
unordered_map<unsigned long long, PairInfo> pair_info;

unsigned long long make_key(int left, int right) {
    return (unsigned long long)(unsigned int)left << 32 | (unsigned int)right;
}

int key_left(unsigned long long key) {
    return (int)(key >> 32);
}

int key_right(unsigned long long key) {
    return (int)(key & 0xffffffffu);
}

int compare_concatenation(int first_left, int first_right, int second_left, int second_right) {
    const string &first_left_text = token_table[first_left].text;
    const string &first_right_text = token_table[first_right].text;
    const string &second_left_text = token_table[second_left].text;
    const string &second_right_text = token_table[second_right].text;
    size_t first_length = first_left_text.size() + first_right_text.size();
    size_t second_length = second_left_text.size() + second_right_text.size();
    size_t common_length = min(first_length, second_length);
    for (size_t i = 0; i < common_length; i++) {
        char first_char = i < first_left_text.size() ? first_left_text[i] : first_right_text[i - first_left_text.size()];
        char second_char = i < second_left_text.size() ? second_left_text[i] : second_right_text[i - second_left_text.size()];
        if (first_char < second_char) return -1;
        if (first_char > second_char) return 1;
    }
    if (first_length < second_length) return -1;
    if (first_length > second_length) return 1;
    return 0;
}

bool better_entry(const HeapEntry &first, const HeapEntry &second) {
    if (first.weight != second.weight) return first.weight > second.weight;
    int first_left = key_left(first.key);
    int first_right = key_right(first.key);
    int second_left = key_left(second.key);
    int second_right = key_right(second.key);
    size_t first_length = token_table[first_left].text.size() + token_table[first_right].text.size();
    size_t second_length = token_table[second_left].text.size() + token_table[second_right].text.size();
    if (first_length != second_length) return first_length < second_length;
    if (token_table[first_left].text.size() != token_table[second_left].text.size()) {
        return token_table[first_left].text.size() < token_table[second_left].text.size();
    }
    int text_compare = compare_concatenation(first_left, first_right, second_left, second_right);
    if (text_compare != 0) return text_compare < 0;
    return first.key < second.key;
}

struct HeapCompare {
    bool operator()(const HeapEntry &first, const HeapEntry &second) const {
        return better_entry(second, first);
    }
};

priority_queue<HeapEntry, vector<HeapEntry>, HeapCompare> heap;

void push_current_pair(unsigned long long key) {
    PairInfo &info = pair_info[key];
    if (info.positions.empty()) return;
    heap.push({key, info.weight, info.version});
}

void add_edge(int left) {
    if (left == 0 || !occurrence[left].alive || occurrence[left].next == 0) return;
    int right = occurrence[left].next;
    unsigned long long key = make_key(occurrence[left].token, occurrence[right].token);
    PairInfo &info = pair_info[key];
    info.weight += word_frequency[occurrence[left].word];
    info.positions.insert(left);
    info.version++;
    heap.push({key, info.weight, info.version});
}

void remove_edge(int left) {
    if (left == 0 || !occurrence[left].alive || occurrence[left].next == 0) return;
    int right = occurrence[left].next;
    unsigned long long key = make_key(occurrence[left].token, occurrence[right].token);
    unordered_map<unsigned long long, PairInfo>::iterator iterator = pair_info.find(key);
    if (iterator == pair_info.end()) return;
    PairInfo &info = iterator->second;
    info.weight -= word_frequency[occurrence[left].word];
    info.positions.erase(left);
    info.version++;
    push_current_pair(key);
}

void merge_occurrence(int left, int first_token, int second_token, int merged_token) {
    int right = occurrence[left].next;
    if (right == 0 || !occurrence[left].alive || !occurrence[right].alive) return;
    if (occurrence[left].token != first_token || occurrence[right].token != second_token) return;

    int previous = occurrence[left].previous;
    int next = occurrence[right].next;
    remove_edge(previous);
    remove_edge(left);
    remove_edge(right);

    occurrence[left].token = merged_token;
    occurrence[left].next = next;
    if (next != 0) occurrence[next].previous = left;
    occurrence[right].alive = false;
    occurrence[right].previous = 0;
    occurrence[right].next = 0;

    add_edge(previous);
    add_edge(left);
}

void merge_pair(int first_token, int second_token) {
    unsigned long long key = make_key(first_token, second_token);
    PairInfo &info = pair_info[key];
    vector<int> positions(info.positions.begin(), info.positions.end());
    string merged_text = token_table[first_token].text + token_table[second_token].text;
    int merged_token = (int)token_table.size();
    token_table.push_back({merged_text});
    for (int i = 0; i < (int)positions.size(); i++) {
        merge_occurrence(positions[i], first_token, second_token, merged_token);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, vocabulary_size;
    cin >> n >> vocabulary_size;
    vector<string> words(n);
    word_frequency.resize(n);
    bool exists[26] = {};
    for (int i = 0; i < n; i++) {
        cin >> words[i] >> word_frequency[i];
        for (int j = 0; j < (int)words[i].size(); j++) exists[words[i][j] - 'a'] = true;
    }

    int letter_token[26];
    for (int i = 0; i < 26; i++) letter_token[i] = -1;
    for (int i = 0; i < 26; i++) {
        if (exists[i]) {
            letter_token[i] = (int)token_table.size();
            token_table.push_back({string(1, (char)('a' + i))});
        }
    }

    occurrence.push_back({0, 0, 0, 0, false});
    for (int i = 0; i < n; i++) {
        int previous = 0;
        for (int j = 0; j < (int)words[i].size(); j++) {
            int node = (int)occurrence.size();
            occurrence.push_back({letter_token[words[i][j] - 'a'], i, previous, 0, true});
            if (previous != 0) occurrence[previous].next = node;
            previous = node;
        }
    }
    for (int i = 1; i < (int)occurrence.size(); i++) add_edge(i);

    while ((int)token_table.size() < vocabulary_size) {
        while (!heap.empty()) {
            HeapEntry top = heap.top();
            unordered_map<unsigned long long, PairInfo>::iterator iterator = pair_info.find(top.key);
            if (iterator != pair_info.end() && iterator->second.version == top.version
                    && iterator->second.weight == top.weight && !iterator->second.positions.empty()) break;
            heap.pop();
        }
        if (heap.empty()) break;
        HeapEntry top = heap.top();
        heap.pop();
        merge_pair(key_left(top.key), key_right(top.key));
    }

    int output_count = min(vocabulary_size, (int)token_table.size());
    for (int i = 0; i < output_count; i++) cout << token_table[i].text << '\n';
    return 0;
}
