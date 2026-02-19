def main():
    card = int(input("Number: "))

    sum_digits = 0
    digit_count = 0
    temp = card

    while temp > 0:
        digit = temp % 10

        if digit_count % 2 == 1:
            prod = digit * 2
            sum_digits += (prod // 10) + (prod % 10)
        else:
            sum_digits += digit

        temp //= 10
        digit_count += 1

    valid = (sum_digits % 10 == 0)

    start = card
    while start >= 100:
        start //= 10

    first = start // 10
    first_two = start

    if valid:
        if digit_count == 15 and (first_two == 34 or first_two == 37):
            print("AMEX")
        elif digit_count == 16 and (51 <= first_two <= 55):
            print("MASTERCARD")
        elif (digit_count == 13 or digit_count == 16) and first == 4:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")

main()