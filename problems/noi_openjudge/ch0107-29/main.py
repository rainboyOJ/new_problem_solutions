isbn = input().strip()
digits = [character for character in isbn if character != "-"]
checksum = sum(int(digit) * weight for weight, digit in enumerate(digits[:9], 1)) % 11
expected = "X" if checksum == 10 else str(checksum)

if digits[9] == expected:
    print("Right")
else:
    print(isbn[:-1] + expected)
