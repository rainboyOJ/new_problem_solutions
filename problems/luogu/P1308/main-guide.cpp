/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:18
 * update_at: 2026-08-14 15:18
 */
/* P1308 统计单词数：整行读入，转成小写后按空格切出单词，完整匹配才计数。 */

#include <iostream>
#include <string>

// 大写字母转小写，其他字符原样返回
char to_lower_char(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return char(ch - 'A' + 'a');
    }
    return ch;
}

// 判断 article[left..right-1] 这一段与 word 是否完全相同
bool is_same_word(const std::string& article, int left, int right,
                  const std::string& word) {
    if (right - left != (int)word.size()) {
        return false;
    }
    for (int k = 0; k < right - left; k += 1) {
        if (article[left + k] != word[k]) {
            return false;
        }
    }
    return true;
}

int main() {
    std::string word;
    std::string article;
    std::getline(std::cin, word);    // 文章里有空格，必须整行读取
    std::getline(std::cin, article);

    // 两个字符串都转成小写，匹配时不区分大小写
    for (int i = 0; i < (int)word.size(); i += 1) {
        word[i] = to_lower_char(word[i]);
    }
    for (int i = 0; i < (int)article.size(); i += 1) {
        article[i] = to_lower_char(article[i]);
    }

    int match_count = 0;
    int first_pos = -1;  // -1 表示还没有出现过

    // 逐个切出文章中以空格分隔的单词，left..right-1 是当前单词
    int i = 0;
    int length = (int)article.size();
    while (i < length) {
        while (i < length && article[i] == ' ') {
            i += 1;  // 跳过单词前的空格
        }
        if (i >= length) {
            break;  // 后面已经没有单词
        }

        int left = i;  // 单词起始位置，位置从 0 开始
        while (i < length && article[i] != ' ') {
            i += 1;
        }
        int right = i;

        if (is_same_word(article, left, right, word)) {
            match_count += 1;
            if (first_pos == -1) {
                first_pos = left;
            }
        }
    }

    if (match_count == 0) {
        std::cout << -1 << '\n';
    } else {
        std::cout << match_count << ' ' << first_pos << '\n';
    }

    return 0;
}
