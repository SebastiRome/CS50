def card_sort(number):
    list = [int(x) for x in str(number)]
    if len(list) == 15:
        if list[0] == 3 and (list[1] == 4 or list[1] == 7):
            print("AMEX")
        else:
            print("INVALID")
    elif len(list) == 16:
        if list[0] == 5 and (list[1] == 1 or list[1] == 2 or list[1] == 3 or list[1] == 4 or list[1] == 5):
            print("MASTERCARD")
        elif list[0] == 4:
            print("VISA")
        else:
            print("INVALID")
    elif len(list) == 13:
        if list[0] == 4:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


def algorithm(number):
    total = 0
    list = [int(x) for x in str(number)]
    if (len(list) % 2) == 0:
        even = list[::2]
        odd = list[1::2]
        list_of_digits = []
        for number in even:
            if number > 4:
                list_of_digits.append(((number * 2) - 9))
            else:
                list_of_digits.append(number * 2)
        total = sum(odd + list_of_digits)
    elif (len(list) % 2) == 1:
        even = list[::2]
        odd = list[1::2]
        list_of_digits = []
        for number in odd:
            if number > 4:
                list_of_digits.append(((number * 2) - 9))
            else:
                list_of_digits.append(number * 2)
        total = sum(even + list_of_digits)
    if total % 10 == 0:
        return True
    else:
        return False


def credit():
    # while True:
    try:
        card_number = input("Card Number: ")
        if algorithm(card_number) == True:
            card_sort(card_number)
            # break
        else:
            print("INVALID")
    except ValueError:
        print("INVALID")


credit()
