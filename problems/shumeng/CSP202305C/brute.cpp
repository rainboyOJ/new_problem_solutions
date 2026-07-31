/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 21:30
 */
// brute.cpp：小数据暴力解，顺序解析元素并逐字节展开回溯引用。
#include <bits/stdc++.h>
using namespace std;

int hex_value(char ch) {
    if ('0' <= ch && ch <= '9') return ch - '0';
    return ch - 'a' + 10;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int compressed_size;
    cin >> compressed_size;
    string encoded, line;
    for (int i = 0; i < (compressed_size + 7) / 8; i++) {
        cin >> line;
        encoded += line;
    }

    vector<unsigned char> data(compressed_size);
    for (int i = 0; i < compressed_size; i++) {
        data[i] = (hex_value(encoded[2 * i]) << 4) | hex_value(encoded[2 * i + 1]);
    }

    int position = 0;
    int original_size = 0;
    int shift = 0;
    while (true) {
        int byte = data[position++];
        original_size |= (byte & 127) << shift;
        if ((byte & 128) == 0) break;
        shift += 7;
    }

    vector<unsigned char> output;
    output.reserve(original_size);
    while ((int)output.size() < original_size) {
        int first = data[position++];
        int type = first & 3;
        if (type == 0) {
            int length_code = first >> 2;
            int length = length_code + 1;
            if (length_code >= 60) {
                int extra = length_code - 59;
                int encoded_length = 0;
                for (int i = 0; i < extra; i++) {
                    encoded_length |= data[position++] << (8 * i);
                }
                length = encoded_length + 1;
            }
            while (length--) output.push_back(data[position++]);
        } else if (type == 1) {
            int length = ((first >> 2) & 7) + 4;
            int offset = ((first >> 5) << 8) | data[position++];
            int start = (int)output.size() - offset;
            for (int i = 0; i < length; i++) output.push_back(output[start + i % offset]);
        } else {
            int length = (first >> 2) + 1;
            int offset = data[position] | (data[position + 1] << 8);
            position += 2;
            int start = (int)output.size() - offset;
            for (int i = 0; i < length; i++) output.push_back(output[start + i % offset]);
        }
    }

    cout << hex << setfill('0');
    for (int i = 0; i < original_size; i++) {
        cout << setw(2) << (int)output[i];
        if ((i + 1) % 8 == 0) cout << '\n';
    }
    if (original_size % 8 != 0) cout << '\n';

    return 0;
}
