import sys
from itertools import islice


def main():
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    test_cases = int(next(it))
    out = []

    for _ in range(test_cases):
        n = int(next(it))
        # dict 保序去重；islice 避免切片复制整段 token 列表
        out.append(b" ".join(dict.fromkeys(islice(it, n))))

    sys.stdout.buffer.write(b"\n".join(out))
    sys.stdout.buffer.write(b"\n")


if __name__ == "__main__":
    main()
