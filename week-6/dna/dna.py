import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    db_file = sys.argv[1]
    database = []
    with open(db_file, "r") as file:
        # Add dictionary of CSV vals to database
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    # Read DNA sequence file into a variable
    sequence_file = sys.argv[2]
    with open(sequence_file, "r") as file:
        sequence = file.read()

    # Find longest match of each STR in DNA sequence
    # Get STRs from first database entry, avoiding first column of "name"
    strs = list(database[0].keys())[1:]

    # Save dictionary with each STR as a key & the value set to the longest
    # match
    # Returns int so no parsing necessary
    longest_matches = {}
    for str in strs:
        match = int(longest_match(sequence, str))
        longest_matches[str] = match

    # Check database for matching profiles
    for data in database:
        name = data["name"]

        for str in strs:
            try:
                db_cnt = int(data[str])
            except ValueError:
                print("Error parsing dictionary ints")
                sys.exit(1)
            mtch_cnt = longest_matches[str]

            is_winner = db_cnt == mtch_cnt

            if not is_winner:
                break

        if is_winner:
            print(name)
            sys.exit(0)

    print("No match")
    sys.exit(1)

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
