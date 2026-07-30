count, target = map(int, input().split())
numbers = map(int, input().split())
print(sum(number == target for number in numbers))
