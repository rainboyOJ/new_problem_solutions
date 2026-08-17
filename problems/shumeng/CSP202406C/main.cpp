/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

// 词表：token_table[i].text 是编号 i 的词汇（初始为单字母）
struct Token {
    string text;
};

// 链表节点：每个节点是某个单词序列中的一个词汇，节点下标即节点编号
struct Occurrence {
    int token;     // 该节点当前的词汇编号
    int word;      // 该节点属于第几个单词（用于加权频率）
    int previous;  // 前驱节点，0 表示链表头
    int next;      // 后继节点，0 表示链表尾
    bool alive;    // 节点是否仍存活（被合并后置为 false）
};

// 一对相邻词汇 (左词汇, 右词汇) 的统计信息
struct PairInfo {
    long long weight;  // 按单词频率加权的出现次数
    int version;       // 版本号，用于惰性删除过期的堆条目
    set<int> positions; // 该词汇对出现的所有边位置（左节点编号）
    PairInfo() : weight(0), version(0) {}
};

// 优先队列中的条目
struct HeapEntry {
    unsigned long long key; // 编码了 (左词汇, 右词汇) 的 64 位键
    long long weight;
    int version;
};

vector<Token> token_table;      // 词表，下标即词汇编号
vector<Occurrence> occurrence;  // 全部单词的词汇序列链表节点，下标 0 为哑节点
vector<long long> word_frequency; // 每个单词的出现频率
unordered_map<unsigned long long, PairInfo> pair_info; // 词汇对 -> 统计信息

// 把 (left, right) 两个词汇编号打包成一个 64 位键
unsigned long long make_key(int left, int right) {
    return (unsigned long long)(unsigned int)left << 32 | (unsigned int)right;
}

// 从键中解出左词汇编号
int key_left(unsigned long long key) {
    return (int)(key >> 32);
}

// 从键中解出右词汇编号
int key_right(unsigned long long key) {
    return (int)(key & 0xffffffffu);
}

// 比较两个词汇拼接串 (a1+a2) 与 (b1+b2) 的字典序：返回 -1/0/1
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

// 判断 first 是否比 second 更优（更大的权重更优，其次按题目规则比较拼接串）
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

// 把 better_entry 转成优先队列的小于号（greater 优先弹出）
struct HeapCompare {
    bool operator()(const HeapEntry &first, const HeapEntry &second) const {
        return better_entry(second, first);
    }
};

priority_queue<HeapEntry, vector<HeapEntry>, HeapCompare> heap; // 惰性删除堆

// 若词汇对 key 还有存活边，就把当前版本压入堆
void push_current_pair(unsigned long long key) {
    PairInfo &info = pair_info[key];
    if (info.positions.empty()) return;
    heap.push({key, info.weight, info.version});
}

// 添加边：左节点 left 与其后继构成一个新的相邻词汇对
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

// 删除边：左节点 left 与其后继的相邻词汇对不再存在
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

// 在链表位置 left 处执行一次合并：把 (first_token, second_token) 替换成 merged_token
void merge_occurrence(int left, int first_token, int second_token, int merged_token) {
    int right = occurrence[left].next;
    if (right == 0 || !occurrence[left].alive || !occurrence[right].alive) return;
    if (occurrence[left].token != first_token || occurrence[right].token != second_token) return;

    int previous = occurrence[left].previous;
    int next = occurrence[right].next;
    // 合并会改变左右两侧的相邻关系，先把相关边删掉
    remove_edge(previous);
    remove_edge(left);
    remove_edge(right);

    // 左节点保留为合并后的词汇，右节点作废
    occurrence[left].token = merged_token;
    occurrence[left].next = next;
    if (next != 0) occurrence[next].previous = left;
    occurrence[right].alive = false;
    occurrence[right].previous = 0;
    occurrence[right].next = 0;

    // 重新建立合并点两侧的相邻边
    add_edge(previous);
    add_edge(left);
}

// 合并词汇对 (first_token, second_token)：所有出现位置一起合并，生成新词汇
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

    // 初始词表：出现过的字母各占一个词汇编号
    int letter_token[26];
    for (int i = 0; i < 26; i++) letter_token[i] = -1;
    for (int i = 0; i < 26; i++) {
        if (exists[i]) {
            letter_token[i] = (int)token_table.size();
            token_table.push_back({string(1, (char)('a' + i))});
        }
    }

    // 把每个单词串成双向链表，节点下标 0 为链表头哨兵
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

    // 反复合并当前最优词汇对，直到词表达到目标大小
    while ((int)token_table.size() < vocabulary_size) {
        // 弹出所有过期的堆条目
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