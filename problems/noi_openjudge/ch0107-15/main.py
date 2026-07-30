count = int(input())

for _ in range(count):
    name = input().strip()
    print(name[0].upper() + name[1:].lower())
