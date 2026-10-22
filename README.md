# BoxesAndPrisoners

C++ simulation of the **100 prisoners riddle** as presented by Veritasium: shuffle the slips into 100 boxes, let each prisoner follow the loop strategy, and count how often everyone survives (theory says about 31%, versus essentially 0% for random guessing).

| | |
|---|---|
| Language | C++ (Windows: uses `BCryptGenRandom` for shuffling) |
| Build | Visual Studio, `BoxesAndPrisoners.sln` |
| Status | Finished (2022-06, touched 2025-06) |
| License | Unlicense |

## Files

| Path | What |
|---|---|
| `BoxesAndPrisoners.cpp` | Whole program: random fill, prisoner strategies, tally |
| `BoxesAndPrisoners.sln`, `.vcxproj*` | Visual Studio project |

## Run

Open the solution in Visual Studio, build (x64, Release) and run. The program prints the survival results. It is Windows-only because of the BCrypt call; swap `genCryptRandom()` for `std::random_device` to build elsewhere.
