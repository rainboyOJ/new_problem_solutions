from itertools import pairwise

n = int(input())
s = input().strip()


def count_vk(text: str) -> int:
    return sum(a + b == "VK" for a, b in pairwise(text))


answer = count_vk(s)
for i, ch in enumerate(s):
    flipped = s[:i] + ("K" if ch == "V" else "V") + s[i + 1 :]
    answer = max(answer, count_vk(flipped))
print(answer)
