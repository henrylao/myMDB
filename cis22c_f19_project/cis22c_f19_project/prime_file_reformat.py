rows = []
with open('primes2.txt', 'r') as infile:
    for line in infile:
        formatted = ','.join(line.split())
        rows.append(formatted)
        print(formatted)
with open('primes_cleaned.txt', 'w')   as outfile:
    for row in rows:
        outfile.write(row + "\n")
