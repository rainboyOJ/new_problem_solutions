count = int(input())
numbers = list(map(int, input().split()))
target = int(input())
print(numbers.index(target) + 1 if target in numbers else -1)
