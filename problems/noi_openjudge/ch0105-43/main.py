number = int(input())
divisor = 2

while divisor * divisor <= number:
    if number % divisor == 0:
        print(number // divisor)
        break
    divisor += 1
