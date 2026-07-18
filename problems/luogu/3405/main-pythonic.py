import sys
from collections import Counter

def main():
    data = sys.stdin.buffer.read().split()
    seen = Counter()
    answer = 0

    for city, state in zip(data[1::2], data[2::2]):
        prefix = city[:2]
        if prefix == state:
            continue
        answer += seen[state, prefix]
        seen[prefix, state] += 1

    print(answer)

if __name__ == "__main__":
    main()
