/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 09:55
 */
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const ull HASH_MULTIPLIER = 47055833459ULL;

struct DecodedCode {
    string name;
    ull number;
    bool explicit_code;
};

unordered_map<ull, ull> latest_hash_12;
unordered_map<ull, ull> latest_hash_25;

ull read_bits(const string &message, int start, int length) {
    ull value = 0;
    for (int i = start; i < start + length; i++) {
        value = (value << 1) | (ull)(message[i] - '0');
    }
    return value;
}

char full_digit_to_char(int digit) {
    if (digit == 0) return ' ';
    if (digit <= 10) return (char)('0' + digit - 1);
    if (digit <= 36) return (char)('A' + digit - 11);
    return '_';
}

int full_char_to_digit(char value) {
    if (value == ' ') return 0;
    if (value >= '0' && value <= '9') return value - '0' + 1;
    if (value >= 'A' && value <= 'Z') return value - 'A' + 11;
    return 37;
}

string decode_full_name(ull number) {
    string result(11, ' ');
    for (int i = 10; i >= 0; i--) {
        result[i] = full_digit_to_char((int)(number % 38));
        number /= 38;
    }
    while (!result.empty() && result.back() == ' ') result.pop_back();
    return result;
}

ull encode_full_name(const string &name) {
    ull number = 0;
    for (int i = 0; i < 11; i++) {
        int digit = 0;
        if (i < (int)name.size()) digit = full_char_to_digit(name[i]);
        number = number * 38 + digit;
    }
    return number;
}

char first_short_digit_to_char(int digit) {
    if (digit == 0) return ' ';
    if (digit <= 10) return (char)('0' + digit - 1);
    return (char)('A' + digit - 11);
}

char second_short_digit_to_char(int digit) {
    if (digit < 10) return (char)('0' + digit);
    return (char)('A' + digit - 10);
}

string decode_short_name(ull number) {
    ull base26_3 = 26ULL * 26 * 26;
    int first = (int)(number / (36ULL * 10 * base26_3));
    number %= 36ULL * 10 * base26_3;
    int second = (int)(number / (10ULL * base26_3));
    number %= 10ULL * base26_3;
    int third = (int)(number / base26_3);
    number %= base26_3;
    int fourth = (int)(number / (26ULL * 26));
    number %= 26ULL * 26;
    int fifth = (int)(number / 26);
    int sixth = (int)(number % 26);

    string result;
    if (first != 0) result.push_back(first_short_digit_to_char(first));
    result.push_back(second_short_digit_to_char(second));
    result.push_back((char)('0' + third));
    result.push_back((char)('A' + fourth));
    result.push_back((char)('A' + fifth));
    result.push_back((char)('A' + sixth));
    return result;
}

ull calculate_hash(ull number, int bits) {
    __uint128_t product = (__uint128_t)number * HASH_MULTIPLIER;
    ull mask = (1ULL << bits) - 1;
    return (ull)((product >> (64 - bits)) & mask);
}

bool find_by_hash(ull target, int bits, ull &number) {
    unordered_map<ull, ull> *table;
    if (bits == 12) table = &latest_hash_12;
    else table = &latest_hash_25;
    unordered_map<ull, ull>::iterator it = table->find(target);
    if (it == table->end()) return false;
    number = it->second;
    return true;
}

void remember_code(ull number) {
    latest_hash_12[calculate_hash(number, 12)] = number;
    latest_hash_25[calculate_hash(number, 25)] = number;
}

DecodedCode decode_simple_code(ull value) {
    DecodedCode result;
    if (value >= (1ULL << 25)) {
        result.name = decode_short_name(value - (1ULL << 25));
        result.number = encode_full_name(result.name);
        result.explicit_code = true;
        return result;
    }

    ull number = 0;
    result.explicit_code = false;
    if (find_by_hash(value, 25, number)) {
        result.name = "#" + decode_full_name(number);
        result.number = number;
    } else {
        result.name = "###";
        result.number = 0;
    }
    return result;
}

DecodedCode decode_hash_code(ull value) {
    DecodedCode result;
    result.explicit_code = false;
    ull number = 0;
    if (find_by_hash(value, 12, number)) {
        result.name = "#" + decode_full_name(number);
        result.number = number;
    } else {
        result.name = "###";
        result.number = 0;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    latest_hash_12.reserve(200005);
    latest_hash_25.reserve(200005);

    int n;
    cin >> n;
    while (n--) {
        string message;
        cin >> message;
        string receiver;
        string sender;

        if (message[0] == '0') {
            ull receiver_value = read_bits(message, 1, 28);
            ull sender_value = read_bits(message, 29, 28);
            ull location = read_bits(message, 57, 15);
            DecodedCode decoded_receiver = decode_simple_code(receiver_value);
            DecodedCode decoded_sender = decode_simple_code(sender_value);
            receiver = decoded_receiver.name;
            sender = decoded_sender.name;

            if (decoded_receiver.explicit_code) {
                remember_code(decoded_receiver.number);
            }
            if (decoded_sender.explicit_code) {
                remember_code(decoded_sender.number);
            }

            cout << receiver << ' ' << sender;
            if (location != 0) cout << ' ' << location;
            cout << '\n';
        } else {
            ull first_number = read_bits(message, 1, 58);
            ull second_hash = read_bits(message, 59, 12);
            int relation = (int)read_bits(message, 71, 1);
            DecodedCode decoded_second = decode_hash_code(second_hash);
            string first_name = decode_full_name(first_number);

            if (relation == 0) {
                receiver = decoded_second.name;
                sender = first_name;
            } else {
                receiver = first_name;
                sender = decoded_second.name;
            }

            remember_code(first_number);
            cout << receiver << ' ' << sender << '\n';
        }
    }

    return 0;
}
