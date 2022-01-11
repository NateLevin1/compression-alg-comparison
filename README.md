# compression-alg-comparison

Benchmark of popular compression algorithms (Zlib/Gzip, Lzip, Bzip2, and Brotli)

## Compilation & Execution

The following command will compile the program:

```bash
g++ $(find . -type f -iregex ".*\.cpp") -o main -lz -lbz2 -llz -std=c++0x
```

Once you have compiled it, run with:

```bash
./main
```

**Alternatively,** you can run `./runtest` to compile and run the program 5 times automatically.

### Compilation Issues

This program depends on 3 libraries to be compiled.

1. https://www.zlib.net
2. https://www.sourceware.org/bzip2/
3. https://www.nongnu.org/lzip/lzlib.html

If you are on MacOS you only need to install the third one.
