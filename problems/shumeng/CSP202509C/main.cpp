/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 19:23
 */
#include <bits/stdc++.h>
using namespace std;

// Huffman 树节点：用数组下标代替指针，left/right 为子节点下标，-1 表示无子节点
struct HuffmanNode {
    int left;
    int right;
    char value;   // 叶子节点存储的字符
    bool leaf;    // 是否为叶子节点
};

// 表格中的一条键值对条目
struct TableEntry {
    string key;
    string value;
};

vector<HuffmanNode> huffman;      // Huffman 树，下标 0 为根节点
string tree_desc;                 // Huffman 树的先序描述串：0 内部节点，1 叶子+字符
int pos;                          // 递归解析描述串时当前读取到的位置
vector<TableEntry> static_table;  // 静态表，按输入顺序保存
deque<TableEntry> dynamic_table;  // 动态表，队首为最新插入的条目
int dynamic_limit;                // 动态表容量上限

// 按先序恢复 Huffman 树：读到 '1' 表示叶子并跟一个字符，读到 '0' 则递归左右子树
int build_huffman_tree() {
    HuffmanNode node;
    node.left = node.right = -1;
    node.value = 0;
    node.leaf = false;
    int id = (int)huffman.size();
    huffman.push_back(node);

    if (tree_desc[pos] == '1') {
        pos++;
        huffman[id].leaf = true;
        huffman[id].value = tree_desc[pos++];
        return id;
    }

    pos++;
    huffman[id].left = build_huffman_tree();
    huffman[id].right = build_huffman_tree();
    return id;
}

// 把十六进制字符转换成数值 0..15
int hex_value(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    return ch - 'A' + 10;
}

// 解码 Huffman 编码串：token 形如 'H' + 偶数个十六进制字符。
// 最后一个字节表示末尾补 0 的个数 p，其余字节高位在前，逐位从根节点走到叶子还原字符串
string decode_huffman_string(const string &token) {
    vector<int> bytes;
    for (int i = 1; i < (int)token.size(); i += 2) {
        bytes.push_back(hex_value(token[i]) * 16 + hex_value(token[i + 1]));
    }
    int padding = bytes.back();             // 最后一字节是补 0 个数
    bytes.pop_back();
    int total_bits = (int)bytes.size() * 8 - padding; // 去掉补 0 后的有效位数

    string result;
    int current = 0;                        // 当前所在节点，0 为根
    for (int bit = 0; bit < total_bits; bit++) {
        int byte_id = bit / 8;
        int offset = 7 - bit % 8;           // 每个字节高位在前
        int direction = (bytes[byte_id] >> offset) & 1; // 0 走左子树，1 走右子树
        if (direction == 0) current = huffman[current].left;
        else current = huffman[current].right;
        if (huffman[current].leaf) {        // 到叶子得到一个字符，回到根继续
            result.push_back(huffman[current].value);
            current = 0;
        }
    }
    return result;
}

// 解码一个字符串：非 'H' 开头原样输出；'HH' 开头去掉一个 H；其余按 Huffman 解码
string decode_string(const string &token) {
    if (token[0] != 'H') return token;
    if (token.size() >= 2 && token[1] == 'H') return token.substr(1);
    return decode_huffman_string(token);
}

// 根据全局编号取条目：编号不超过静态表大小取静态表，否则换算成动态表下标
TableEntry get_entry(int number) {
    if (number <= (int)static_table.size()) return static_table[number - 1];
    return dynamic_table[number - (int)static_table.size() - 1];
}

// 插入动态表：新条目放队首，达到容量上限时先淘汰最旧的队尾条目
void insert_dynamic_table(const TableEntry &entry) {
    if ((int)dynamic_table.size() == dynamic_limit) dynamic_table.pop_back();
    dynamic_table.push_front(entry);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int static_size;
    cin >> static_size >> dynamic_limit;

    // 读入静态表原始字符串（其中可能包含 Huffman 编码）
    vector<pair<string, string> > raw_static(static_size);
    for (int i = 0; i < static_size; i++) {
        cin >> raw_static[i].first >> raw_static[i].second;
    }

    // 读入描述串并恢复 Huffman 树
    cin >> tree_desc;
    pos = 0;
    build_huffman_tree();

    // 解码静态表的每个条目
    static_table.resize(static_size);
    for (int i = 0; i < static_size; i++) {
        static_table[i].key = decode_string(raw_static[i].first);
        static_table[i].value = decode_string(raw_static[i].second);
    }

    // 按顺序处理每条指令
    int instruction_count;
    cin >> instruction_count;
    for (int instruction = 0; instruction < instruction_count; instruction++) {
        int operation, number;
        cin >> operation >> number;
        TableEntry entry;

        if (operation == 1) { // 表格引用：直接输出对应编号的条目
            entry = get_entry(number);
            cout << entry.key << ": " << entry.value << '\n';
            continue;
        }

        // 字面量指令：编号为 0 时字段名由输入给出，否则借用表格条目的字段名
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

        // 字面量并索引：输出后插入动态表，供后续指令引用
        if (operation == 2) insert_dynamic_table(entry);
    }

    return 0;
}