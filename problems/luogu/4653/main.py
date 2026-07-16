import sys


def scaled(token):
    whole, _, fraction = token.partition(b".")
    return int(whole) * 10000 + int((fraction + b"0000")[:4])


tokens = iter(sys.stdin.buffer.read().split())
n = int(next(tokens))
first, second = zip(*((scaled(next(tokens)), scaled(next(tokens))) for _ in range(n))) if n else ((), ())
first, second = sorted(first, reverse=True), sorted(second, reverse=True)
i = j = total_first = total_second = chosen = answer = 0

while i < n or j < n:
    if i < n and (j == n or total_first <= total_second):
        total_first += first[i]
        i += 1
    else:
        total_second += second[j]
        j += 1
    chosen += 1
    answer = max(answer, min(total_first, total_second) - chosen * 10000)

print(f"{answer // 10000}.{answer % 10000:04d}")
