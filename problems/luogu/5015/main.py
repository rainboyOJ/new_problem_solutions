import sys


title = sys.stdin.readline().rstrip("\n")
answer = sum(1 for ch in title if ch != " ")
print(answer)
