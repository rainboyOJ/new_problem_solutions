source_base, source_number, target_base = input().split()
value = int(source_number, int(source_base))
digits = "0123456789ABCDEF"

if value == 0:
    print(0)
else:
    converted = []
    while value:
        value, remainder = divmod(value, int(target_base))
        converted.append(digits[remainder])
    print("".join(reversed(converted)))
