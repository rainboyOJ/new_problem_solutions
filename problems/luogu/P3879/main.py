import sys
from collections import defaultdict


def main():
    # 一次性读入所有输入，按空白字符分割
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    pos = 1
    articles = defaultdict(list)  # 倒排索引：单词 → 文章编号列表

    # 读入 n 篇文章
    for article_id in range(1, n + 1):
        word_count = int(data[pos])
        pos += 1
        # 每篇文章内用 set 去重，避免同一文章重复编号
        words = set(data[pos:pos + word_count])
        pos += word_count
        # 把当前文章编号加入每个单词的列表
        for word in words:
            articles[word].append(article_id)

    # 读入询问
    query_count = int(data[pos])
    pos += 1
    # 生成器依次处理每个询问：找到列表就直接输出，找不到就输出空串
    answer = (
        " ".join(map(str, articles[word]))
        for word in data[pos:pos + query_count]
    )
    print("\n".join(answer))


if __name__ == "__main__":
    main()
