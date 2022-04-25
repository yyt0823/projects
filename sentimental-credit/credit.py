# TODO
import cs50
import math


def main():
    number = cs50.get_int("Number: ")
    if checksum(number):
        company(number)
    else:
        print("INVALID")


def checksum(number):
    sum = 0
    for i in range(2, 17, 2):
        current = number % 10**i // 10**(i - 1) * 2
        if current >= 10:
            current = (current % 10) + (current // 10)
        sum += current
    for i in range(1, 17, 2):
        original = number % 10**i // 10**(i - 1)
        sum += original
    if sum % 10 == 0:
        return True
    else:
        return False


def company(cardnum):
    if (cardnum >= 340000000000000 and cardnum < 350000000000000) or (cardnum >= 370000000000000 and cardnum < 380000000000000):
        print("AMEX")
    elif cardnum >= 5100000000000000 and cardnum < 5600000000000000:
        print("MASTERCARD")
    elif ((cardnum >= 4000000000000 and cardnum < 5000000000000) or (cardnum >= 4000000000000000 and cardnum < 5000000000000000)):
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()