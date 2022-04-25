import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        exit(1)
    # TODO: Read database file into a variable
    list = []
    sequence = []
    str_match = {}
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        str = reader.fieldnames[1:]
        for row in reader:
            list.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        sequence = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    for subsequence in str:
        str_match[subsequence] = longest_match(sequence, subsequence)

    # TODO: Check database for matching profiles
    result = "No match"
    for people in range(len(list)):
        if str_match.items() <= list[people].items():
            result = (list[people]["name"])
    print(result)
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
    return str(longest_run)


main()
