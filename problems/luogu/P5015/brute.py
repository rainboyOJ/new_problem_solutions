import sys


title = sys.stdin.readline().rstrip("\n")
answer = 0
for ch in title:
    if ch != " ":
        answer += 1
print(answer)
