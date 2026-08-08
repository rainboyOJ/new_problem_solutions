n = int(input())

answer = 0
for x in range(1, n + 1):
    factorial = 1
    for v in range(1, x + 1):
        factorial *= v
    answer += factorial

print(answer, end="")
