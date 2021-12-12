# compression-alg-comparison

Benchmark of popular compression algorithms (Zlib/Gzip, Lzip, Bzip2, and Brotli)

## Compilation & Execution

The following command will compile the program:

```bash
g++ $(find . -type f -iregex ".*\.cpp") -o main -lz -std=c++0x
```

Once you have compiled it, run with:

```bash
./main
```
