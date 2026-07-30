count = int(input())
numbers = list(map(int, input().split()))
longest = current = 1
for index in range(1, count):
    current = current + 1 if numbers[index] == numbers[index - 1] else 1
    longest = max(longest, current)
print(longest)
