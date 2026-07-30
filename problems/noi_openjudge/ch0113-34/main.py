left, right, result = input().split()

for base in range(2, 17):
    try:
        if int(left, base) * int(right, base) == int(result, base):
            print(base)
            break
    except ValueError:
        continue
else:
    print(0)
