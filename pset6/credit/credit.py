from cs50 import get_int


def main():
    cardnum = get_int("Number:")
    
    luhnval = 0
    cardlen = len(str(cardnum))
    
    # get the first and second digits of the card
    a = get_dig(cardnum, cardlen - 1)
    b = get_dig(cardnum, cardlen - 2)
    
    # implement Luhn's Algorithm
    for i in range(0, cardlen + 1):
        if (cardlen - i) % 2 == 1:
            if ((2 * get_dig(cardnum, (cardlen - i))) > 9):
                luhnval += 1
            luhnval += (2 * get_dig(cardnum, (cardlen - i))) % 10
        else:
            luhnval += get_dig(cardnum, (cardlen - i))

    valid = False
    if luhnval % 10 == 0:
        valid = True
        
    # determine what type of card it is  
    if valid:
        if cardlen == 15 and (a == 3 and (b == 4) or (b == 7)):
            print("AMEX")
        elif ((cardlen == 13) or cardlen == 16) and a == 4:
            print("VISA")
        elif (cardlen == 16) and a == 5 and (b > 0 and b < 6):
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")
            
# gets a single digit from a number.


def get_dig(number, n):
    return (number // 10**n) % 10


main()
