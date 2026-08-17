/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

int compressed_size;                 // 压缩数据的字节数 s
string encoded;                      // 拼接后的十六进制字符串
vector<unsigned char> bytes;          // 解码后的压缩数据字节
vector<unsigned char> output;        // 解压输出的原始数据字节
int original_size;                   // 导引域解析出的原始数据长度

// 十六进制字符转成数值 0..15
int hex_value(char ch) {
    if ('0' <= ch && ch <= '9') return ch - '0';
    return ch - 'a' + 10;
}

// 解析导引域：小端序 7 位分组，最高位为 1 表示后面还有字节。
// 通过引用回传解析结束后的位置，供数据域继续读取。
int parse_original_size(int &position) {
    int size = 0;
    int shift = 0;
    while (true) {
        int byte = bytes[position++];
        size |= (byte & 127) << shift; // 低 7 位是当前长度部分
        if ((byte & 128) == 0) break;  // 最高位为 0 表示导引域结束
        shift += 7;
    }
    return size;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> compressed_size;
    string line;
    for (int i = 0; i < (compressed_size + 7) / 8; i++) {
        cin >> line;
        encoded += line;
    }

    // 每两个十六进制字符还原成一个字节
    bytes.resize(compressed_size);
    for (int i = 0; i < compressed_size; i++) {
        bytes[i] = (hex_value(encoded[2 * i]) << 4) | hex_value(encoded[2 * i + 1]);
    }

    int position = 0; // 压缩数据的读取位置，先解析导引域，再继续解析数据域
    original_size = parse_original_size(position);
    output.reserve(original_size);

    // 逐个元素解析，直到输出长度达到原始长度
    while ((int)output.size() < original_size) {
        int first = bytes[position++];
        int type = first & 3; // 最低两位决定元素类型

        if (type == 0) {
            // 字面量：高 6 位给出 l-1；为 60..63 时再读 1..4 个字节的小端长度
            int length_code = first >> 2;
            int length;
            if (length_code < 60) {
                length = length_code + 1;
            } else {
                int extra = length_code - 59;
                int encoded_length = 0;
                for (int i = 0; i < extra; i++) {
                    encoded_length |= bytes[position++] << (8 * i);
                }
                length = encoded_length + 1;
            }
            // 直接复制接下来的 length 个字节
            for (int i = 0; i < length; i++) output.push_back(bytes[position++]);
        } else if (type == 1) {
            // 回溯引用：长度 4..11，偏移占 11 位（首字节高 3 位 + 后 1 字节低 8 位）
            int length = ((first >> 2) & 7) + 4;
            int offset = ((first >> 5) << 8) | bytes[position++];
            // 逐字节从 output.size()-offset 处复制，天然支持 o < l 的重叠情况
            for (int i = 0; i < length; i++) output.push_back(output[output.size() - offset]);
        } else {
            // 回溯引用：长度 1..64，偏移为后两个小端字节
            int length = (first >> 2) + 1;
            int offset = bytes[position] | (bytes[position + 1] << 8);
            position += 2;
            int start = (int)output.size() - offset;
            // 重叠时按周期重复复制 offset 个字节
            for (int i = 0; i < length; i++) output.push_back(output[start + i % offset]);
        }
    }

    // 输出解压结果，每行 8 个字节，十六进制小写
    cout << hex << setfill('0');
    for (int i = 0; i < original_size; i++) {
        cout << setw(2) << (int)output[i];
        if ((i + 1) % 8 == 0) cout << '\n';
    }
    if (original_size % 8 != 0) cout << '\n';

    return 0;
}