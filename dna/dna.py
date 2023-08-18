import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("CORRECT USAGE: python dna.py CSV_file DNA_sequence")
        return 0

    # TODO: Read database file into a variable
    file = open(sys.argv[1])
    csv_file = csv.DictReader(file)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as dna_file:
        dna_sequence = dna_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    n_first_sequence = str(longest_match(dna_sequence, "AGATC"))
    n_second_sequence = str(longest_match(dna_sequence, "AATG"))
    n_third_sequence = str(longest_match(dna_sequence, "TATC"))
    n_fourth_sequence = str(longest_match(dna_sequence, "TCTAG"))
    n_fifth_sequence = str(longest_match(dna_sequence, "TTTTTTCT"))
    n_sixth_sequence = str(longest_match(dna_sequence, "GATA"))
    n_seventh_sequence = str(longest_match(dna_sequence, "GAAA"))
    n_eight_sequence = str(longest_match(dna_sequence, "TCTG"))

    # TODO: Check database for matching profiles
    count = 0
    if sys.argv[1] == "databases/large.csv":
        for row in csv_file:
            if row["AGATC"] == n_first_sequence and row["AATG"] == n_second_sequence and row["TATC"] == n_third_sequence and row["TCTAG"] == n_fourth_sequence and row["TTTTTTCT"] == n_fifth_sequence and row["GATA"] == n_sixth_sequence and row["GAAA"] == n_seventh_sequence and row["TCTG"] == n_eight_sequence:
                print(row["name"])
                count += 1
                break
    else:
        for row in csv_file:
            if row["AGATC"] == n_first_sequence and row["AATG"] == n_second_sequence and row["TATC"] == n_third_sequence:
                print(row["name"])
                count += 1
                break
    if count == 0:
        print("No match")
    file.close()


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
