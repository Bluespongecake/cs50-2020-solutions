from csv import reader, DictReader
from sys import argv


def main():
    if len(argv) < 3:
        print("Usage: dna.py <File:STR count> <File:DNA Seq>")
        exit()

    elif len(argv) > 3:
        print("Usage: dna.py <File:STR count> <File:DNA Seq>")
        exit()

    # read in a dna seqence from the file
    # store the dna seq in a string

    with open(argv[2]) as dnafile:
        dnaseq = dnafile.read()

    # make a dict to store the STR sequences
    STRs = {}

    # put the STR definitions from the database into a list
    with open(argv[1]) as countfile:
        people = reader(countfile)
        for row in people:
            dnaDefs = row
            
            # remove the first element, being 'name'
            dnaDefs.pop(0)
            break

    # put the STR defs into a dictionary where each gene is a key, and the number is the number of occurances
    for element in dnaDefs:
        STRs[element] = 69  # nice

    for key in STRs:
        maxocc = 0                                                              # maximum number of repeated occurances of STR
        occ = 0                                                                 # number of current occurances within the conditional loop below
        STRlen = len(key)
        # print(STRlen)
        for i in range(len(dnaseq)):                                            # loop through the length of the dna sequence
            # after having counted a sequence it skips the end to avoid counting again
            while occ > 0:
                occ -= 1
                continue
                
            # if the segment we are currently looking at (which is as long as the STR) is equal to the STR
            if dnaseq[i: i + STRlen] == key:
                # print(f"/{dnaseq[i: i + STRlen]}/    :    /{key}/ {i}")            #checking
                occ = 1
                
                # as long as each segment is equal to the STR, continue to add to the occ counter
                while dnaseq[i - STRlen: i] == dnaseq[i: i + (STRlen)]:
                    # print(f"/{dnaseq[i + ((occ - 1) * STRlen): i + ((occ) * STRlen)]}/    :    /{dnaseq[i + ((occ) * STRlen): i + ((occ + 1) * STRlen)]} {occ}/")
                    # print(f"{i}, {dnaseq[i: i + STRlen]} == {i + STRlen}, {dnaseq[i + STRlen: i + (2 * STRlen)]}")
                    occ += 1
                    i += STRlen
                    # print(f"{key} {occ}")

                if occ > maxocc:                                                # if we found a new longest seq, set it to maxocc
                    maxocc = occ
                 #   print(maxocc)

            STRs[key] = maxocc
    
    # print(dnaseq)
    # print(STRs)
    
    with open(argv[1], newline='') as peoplefile:
        people = DictReader(peoplefile)
        for person in people:
            match = 0
            
            for dna in STRs:
                if STRs[dna] == int(person[dna]):
                    match += 1
                    
                if match == len(STRs):
                    print(person['name'])
                    exit()
                    
        print("no match")


main()
