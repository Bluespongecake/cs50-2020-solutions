from cs50 import get_string


def main():
    
    # first get the text to be graded
    text = get_string("Text: \n")
    
    # the data we need to calculate    
    letters = 0
    words = 1
    sentances = 0
    length = 0
    
    for i in text:
        length += 1

    # count the number of ascii letters in the text
    for i in text:
        if ((ord(i) > 64 and ord(i) < 123) and ord(i) != 96):
            letters += 1
    
    for i in range(length):
        
        # count the number of spaces that are preceded by a letter, i.e words

        if (ord(text[i]) == 32):
            words += 1
        
        # count the number sentances by detecting full stops
        
        if (text[i] == '.' or text[i] == '!' or text[i] == '?'):
            sentances += 1
    
    L = (letters / words) * 100
    S = (sentances / words) * 100
    
    index = 0.0588 * L - 0.296 * S - 15.8
    index = round(index, 0)
    index = int(index)
    if (index < 1):
        print("Before Grade 1")
    elif (index >= 16):
        print("Grade 16+")
    else:
        print(f"Grade: {index}")
    
    
main()
