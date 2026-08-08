n = int(input())
s = input().strip()

answer = []
for ch in s:
    offset = (ord(ch) - ord("a") + n) % 26
    answer.append(chr(ord("a") + offset))

print("".join(answer))
