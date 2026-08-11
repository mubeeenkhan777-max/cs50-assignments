import csv
import sys


def main():

    # Check command-line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read database
    with open(sys.argv[1], newline="") as file:
        reader = csv.DictReader(file)
        database = list(reader)
        strs = reader.fieldnames[1:]

    # Read DNA sequence
    with open(sys.argv[2]) as file:
        sequence = file.read().strip()

    # Find longest run for each STR
    counts = {}

    for str_name in strs:
        counts[str_name] = longest_match(sequence, str_name)

    # Compare DNA counts with each person
    for person in database:
        match = True

        for str_name in strs:
            if int(person[str_name]) != counts[str_name]:
                match = False
                break

        if match:
            print(person["name"])
            return

    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    longest_run = 0
    sequence_length = len(sequence)
    subsequence_length = len(subsequence)

    for i in range(sequence_length):
        count = 0

        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length

            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        longest_run = max(longest_run, count)

    return longest_run


if __name__ == "__main__":
    main()
