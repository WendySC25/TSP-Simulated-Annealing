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
./build/tsp_runner $(cat data/args/x.in)
```

The program supports 3 execution modes:

1. **`single`**: Runs one experiment using the exact hyperparameters provided via CLI flags (or defaults if omitted).
2. **`seeds`**: Runs *N* experiments using the same hyperparameters provided via CLI flags (or defaults if omitted) but different random seeds. Requires the `-nRuns` flag.
3. **`random`**: Runs *N* experiments with randomly generated hyperparameters for exploration. Requires the `-nRuns` flag.

| Flag | Description | Default Value |
|------|-------------|---------------|
| `-db` | **[Required]** Path to the SQLite database. | - |
| `-instance` | **[Required]** Path to the `.tsp` instance file. | - |
| `-mode` | Execution mode (`single`, `seeds`, `random`). | `single` |
| `-out` | Path to save the CSV report. | `./data/output/exp.csv` |
| `-nRuns` | Number of executions (used with `seeds` or `random`). | `1` |
| `-seed` | RNG seed for reproducibility. | `9695` |
| `-targetP` | Target acceptance probability for initial temperature. | `0.95` |
| `-epsilonP` | Tolerance for the initial temperature search. | `0.00001` |
| `-initialT` | Starting temperature. | `8.0` |
| `-tempSample` | Sample size for temperature initialization. | `5000` |
| `-batchSize` | Number of iterations per temperature level. | `5000` |
| `-maxAttempts` | Maximum temperature drops without improvement. This number is multiply by maxAttempts x maxAttempts x2| `150` |
| `-coolingFactor`| Multiplier for the cooling schedule. | `0.97` |
| `-epsilon` | Minimum temperature threshold to stop execution. | `0.00001` |

