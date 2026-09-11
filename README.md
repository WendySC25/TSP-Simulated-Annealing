# Simulated Annealing for the Traveling Salesman Problem 

Build and compile:

```
cmake -B build && cmake --build build
```

Compile:
```
cmake --build build
```

Run test:
```
ctest --test-dir build
```

Run:
```
./build/main $(cat args150.in)
```

Or:

```
./build/main -db [sql_path] -instance [input_path] -seed 9695 -targetP 0.9 -epsilonP 0.00001 -initialT 8 -tempSample 5000 -coolingFactor 0.97 -epsilon 0.00001 -batchSize 5000 -maxAttempts 150
```

