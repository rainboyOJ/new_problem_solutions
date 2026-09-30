"""笨小猴：统计每个字母出现次数，判断 maxn-minn 是否为质数。"""

s = input().strip()
cnt = [s.count(c) for c in set(s)]
d = max(cnt) - min(cnt)


def is_prime(n: int) -> bool:
    return n >= 2 and all(n % i for i in range(2, int(n**0.5) + 1))


print("Lucky Word" if is_prime(d) else "No Answer")
print(d if is_prime(d) else 0)
