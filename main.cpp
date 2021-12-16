#include <iostream>
#include <fstream>
#include <zlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "algorithms/zlib.h"
#include "algorithms/bzip2.h"
#include "algorithms/lzlib.h"
#include "utils.h"

int main() {
    int ret = 0;

    const char* dataset = "datasets/website.tar";

    std::cout << "Program Started." << std::endl;

    std::string templ = "__test-XXXXXX";
    char* tempDir = mkdtemp((char*)templ.c_str());

    runTest("CONTROL", dataset, tempDir, [](FILE* inputFile, FILE* outputFile) {
        int c = fgetc(inputFile);
        while (c != EOF)
        {
            fputc(c, outputFile);
            c = fgetc(inputFile);
        }
    });

    runTest("ZLIB_DEFLATE", dataset, tempDir, [](FILE* inputFile, FILE* outputFile) {
        zlib_deflate(inputFile, outputFile);
    });

    runTest("BZIP2_COMPRESS", dataset, tempDir, [](FILE* inputFile, FILE* outputFile) {
        bz2lib_compress(inputFile, outputFile);
    });

    runTest("LZLIB_COMPRESS", dataset, tempDir, [](FILE* inputFile, FILE* outputFile) {
        lzlib_compress(inputFile, outputFile);
    });
    
    rmrf(tempDir);

    std::cout << "\nProgram Ended" << std::endl;
    return ret;
}