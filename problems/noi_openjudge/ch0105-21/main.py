number = int(input())

while number != 1:
    if number % 2:
        next_number = number * 3 + 1
        print(f"{number}*3+1={next_number}")
    else:
        next_number = number // 2
        print(f"{number}/2={next_number}")
    number = next_number

print("End")
