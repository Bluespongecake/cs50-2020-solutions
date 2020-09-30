import sys
from sys import argv
from cs50 import SQL


def main():
    if len(argv) != 2:
        sys.exit("Usage: roster.py house")
    
    # make the house lowercase
    houseq = argv[1].lower()
    
    # ensure that house exists
    houses = ["slytherin", "gryffindor", "ravenclaw", "hufflepuff"]
    
    if houseq not in houses:
        sys.exit("not a valid house")
        
    database = SQL("sqlite:///students.db")
    
    # read data into memory from database
    pupils = database.execute("SELECT * FROM students WHERE lower(house) = (?) ORDER BY last", houseq)
    
    # this might be a workaround or spaghetti code but hey, it works!
    # if there is no middle name, then dont print it, otherwise print everything
    for pupil in pupils:
        if pupil['middle'] == None:
            print(f"{pupil['first']} {pupil['last']}, born {pupil['birth']}")
        else:
            print(f"{pupil['first']} {pupil['middle']} {pupil['last']}, born {pupil['birth']}")


main()
