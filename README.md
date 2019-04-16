# Floyd-Warshall Shortest Path 

A program that calculates shortest paths on input graphs using the Floyd-Warshall algorithm. The program is implemented as a serial version and a parallel version

Author: Utsav Sethi

## Usage

### Building
`make clean all` builds all binaries (i.e. serial, parallel, unit test, and performance tests)

### Executing the program 

Serial version:  `./fw_serial [INPUT_FILE]`
Parallel version: `./fw_parallel [NUM_THREADS] [INPUT_FILE]`

Note: input file is assumed to be a correctly formatted well-formed graph (i.e. no negataive cycles).

Output graph with shortest paths is written to `output.txt`

### Running tests

Unit/functional tests can be run with `./fw_test`

Performance tests can be run with `./fw_performance_test`

