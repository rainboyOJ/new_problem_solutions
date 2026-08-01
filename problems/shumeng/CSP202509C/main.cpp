/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 10:55
 */
#include <bits/stdc++.h>
using namespace std;

struct HuffmanNode {
    int left;
    int right;
    char value;
    bool leaf;
};

struct TableEntry {
    string key;
    string value;
};

vector<HuffmanNode> huffman;
string huffman_description;
int huffman_position;
vector<TableEntry> static_table;
deque<TableEntry> dynamic_table;
int dynamic_limit;

int build_huffman_tree() {
    HuffmanNode node;
    node.left = node.right = -1;
    node.value = 0;
    node.leaf = false;
    int id = (int)huffman.size();
    huffman.push_back(node);

    if (huffman_description[huffman_position] == '1') {
        huffman_position++;
        huffman[id].leaf = true;
        huffman[id].value = huffman_description[huffman_position++];
        return id;
    }

    huffman_position++;
    huffman[id].left = build_huffman_tree();
    huffman[id].right = build_huffman_tree();
    return id;
}

int hex_value(char value) {
    if (value >= '0' && value <= '9') return value - '0';
    if (value >= 'a' && value <= 'f') return value - 'a' + 10;
    return value - 'A' + 10;
}

string decode_huffman_string(const string &token) {
    vector<int> bytes;
    for (int i = 1; i < (int)token.size(); i += 2) {
        bytes.push_back(hex_value(token[i]) * 16 + hex_value(token[i + 1]));
    }
    int padding = bytes.back();
    bytes.pop_back();
    int total_bits = (int)bytes.size() * 8 - padding;
    string result;
    int current = 0;
    int root = 0;
    for (int bit = 0; bit < total_bits; bit++) {
        int byte_id = bit / 8;
        int offset = 7 - bit % 8;
        int direction = (bytes[byte_id] >> offset) & 1;
        if (direction == 0) current = huffman[current].left;
        else current = huffman[current].right;
        if (huffman[current].leaf) {
            result.push_back(huffman[current].value);
            current = root;
        }
    }
    return result;
}

string decode_string(const string &token) {
    if (token[0] != 'H') return token;
    if (token.size() >= 2 && token[1] == 'H') return token.substr(1);
    return decode_huffman_string(token);
}

TableEntry get_entry(int number) {
    if (number <= (int)static_table.size()) return static_table[number - 1];
    return dynamic_table[number - (int)static_table.size() - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int static_size;
    cin >> static_size >> dynamic_limit;
    vector<pair<string, string> > raw_static(static_size);
    for (int i = 0; i < static_size; i++) {
        cin >> raw_static[i].first >> raw_static[i].second;
    }
    cin >> huffman_description;
    huffman_position = 0;
    build_huffman_tree();

    static_table.resize(static_size);
    for (int i = 0; i < static_size; i++) {
        static_table[i].key = decode_string(raw_static[i].first);
        static_table[i].value = decode_string(raw_static[i].second);
    }

    int instruction_count;
    cin >> instruction_count;
    for (int instruction = 0; instruction < instruction_count; instruction++) {
        int operation, number;
        cin >> operation >> number;
        TableEntry entry;
        if (operation == 1) {
            entry = get_entry(number);
            cout << entry.key << ": " << entry.value << '\n';
            continue;
        }

        string raw_key;
        string raw_value;
        if (number == 0) {
            cin >> raw_key >> raw_value;
            entry.key = decode_string(raw_key);
        } else {
            cin >> raw_value;
            entry.key = get_entry(number).key;
        }
        entry.value = decode_string(raw_value);
        cout << entry.key << ": " << entry.value << '\n';

        if (operation == 2) {
            if ((int)dynamic_table.size() == dynamic_limit) dynamic_table.pop_back();
            dynamic_table.push_front(entry);
        }
    }
    return 0;
}
