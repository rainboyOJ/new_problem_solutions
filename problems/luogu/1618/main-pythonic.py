a, b, c = map(int, input().split())

answers = []

if a != 0:
    left = (100 + a - 1) // a
    right = 999 // c

    for times in range(left, right + 1):
        x = a * times
        y = b * times
        z = c * times
        digits = f"{x}{y}{z}"
        if len(digits) == 9 and set(digits) == set("123456789"):
            answers.append((x, y, z))

if answers:
    for answer in answers:
        print(*answer)
else:
    print("No!!!")
