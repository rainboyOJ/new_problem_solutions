n = int(input())

factorial = 1
answer = 0

for x in range(1, n + 1):
    factorial *= x
    answer += factorial

print(answer, end="")
