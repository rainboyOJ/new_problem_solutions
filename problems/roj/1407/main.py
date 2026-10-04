"""笨小猴：统计每个字母出现次数，判断 maxn-minn 是否为质数。"""

import sys

data = iter(sys.stdin.buffer.read().split())  # 输入只有一个 token，顺序消费即可
s = next(data).decode()                       # 待统计的单词，按空白切分后顺带去掉换行
cnt = [s.count(c) for c in set(s)]
d = max(cnt) - min(cnt)


def is_prime(n: int) -> bool:
    return n >= 2 and all(n % i for i in range(2, int(n**0.5) + 1))


print("Lucky Word" if is_prime(d) else "No Answer")
print(d if is_prime(d) else 0)
