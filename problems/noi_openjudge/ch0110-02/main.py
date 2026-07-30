input()
odd_numbers = [number for number in map(int, input().split()) if number % 2 == 1]

print(",".join(map(str, sorted(odd_numbers))))
