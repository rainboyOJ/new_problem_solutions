number_string = input().strip()
number = int(number_string)
length = len(number_string)
doubled = number_string + number_string

for multiplier in range(1, length + 1):
    product = str(number * multiplier).zfill(length)
    if len(product) != length or product not in doubled:
        print(0)
        break
else:
    print(1)
