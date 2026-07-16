import sys
from collections import defaultdict


def main():
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    pos = 1
    articles = defaultdict(list)

    for article_id in range(1, n + 1):
        word_count = int(data[pos])
        pos += 1
        words = set(data[pos:pos + word_count])
        pos += word_count
        for word in words:
            articles[word].append(article_id)

    query_count = int(data[pos])
    pos += 1
    answer = (
        " ".join(map(str, articles[word]))
        for word in data[pos:pos + query_count]
    )
    print("\n".join(answer))


if __name__ == "__main__":
    main()
