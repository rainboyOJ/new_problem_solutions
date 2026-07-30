number = input().strip()

while len(number) > 1:
    number = str(sum(map(int, number)))

print(number)
