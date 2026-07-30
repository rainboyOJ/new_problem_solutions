count = int(input())
numbers = list(map(int, input().split()))
maximum = max(numbers)
print(sum(number for number in numbers if number != maximum))
