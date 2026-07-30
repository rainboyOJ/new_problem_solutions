count = int(input())
numbers = map(str, input().split())

answer = 0
for number in numbers:
    digits = list(map(int, number))
    answer += digits[3] > sum(digits[:3])

print(answer)
