# TODO
from csv import reader, DictReader
import sys
from sys import argv
from cs50 import SQL


def main():
    
    # check to ensure that the correct command has been issued (2 args and file is csv)
    if len(argv) < 2:
        sys.exit("Usage: import.py <file>")

    elif len(argv) > 2:
        sys.exit("Usage: import.py <file>")
    
    CSVFILE = argv[1]
    
    if not (CSVFILE.endswith(".csv")):
        sys.exit("file must be .csv")
    
    # ignore this. I was trying to use some fancy functions that would work exactly the same way
    # the database to write to later
    # database = "students.db"
    # dat = sqlite3.connect(database)
    
    # cursor for the database so I can navigate it if needs be
    # cursor = dat.cursor()
    
    database = SQL("sqlite:///students.db")
    
    # open the CSV file with all info on students, and copy all info into a list called 'students'
    with open(CSVFILE) as CSVfile:
        students = reader(CSVfile)
        for row in students: 
            if row[0] == 'name':
                continue                    # skip the first line because we don't want the titles
            
            # divide up the name into first, middle and last, using a space as the divider
            name = row[0].split()
            
            # if the student has 3 names, then put in NULL for the middle name
            if len(name) < 3:
                database.execute("INSERT INTO students(first, last, house, birth) VALUES(?, ?, ?, ?)", 
                                 name[0], name[1], row[1], row[2])

            else:
                database.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", 
                                 name[0], name[1], name[2], row[1], row[2])
            
            # print(row);


main()
