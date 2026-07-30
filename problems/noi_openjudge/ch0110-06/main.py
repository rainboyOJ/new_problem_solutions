numbers = list(map(int, input().split()))
odds = sorted((number for number in numbers if number % 2 == 1), reverse=True)
evens = sorted(number for number in numbers if number % 2 == 0)

print(*odds, *evens)
