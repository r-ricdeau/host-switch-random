# host-switch-random
Generation of a random host-switch graph with given N (the number of hosts), M (the number of switches), and R (the number of switch ports)

## Graph file format
* The first line describes the following three parameters: n (the number of hosts), m (the number of switches), and r (the number ports of each switch, namely radix).
* The hosts must be integers 0, 1, 2, ..., n - 2, n - 1. The switches must be integers n, n + 1, n + 2, ..., n + m - 2, n + m - 1.
* From the second line, an edge list format follows the first line.
* For example, see "random.txt".

## Compilation
```
$ make
```

## Execution
```
$ ./random-gen N M R > output_file
h-ASPL
h-diameter
```
### Example
```
$ ./h-aspl 1024 100 24 > random.txt
4.096732
5
```
This will generate "random.txt".

