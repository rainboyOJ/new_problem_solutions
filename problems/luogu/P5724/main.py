n = int(input())
numbers = list(map(int, input().split()))

answer = max(numbers) - min(numbers)

print(answer)
