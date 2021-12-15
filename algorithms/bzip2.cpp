#include "bzip2.h"
#include <bzlib.h>

void bz2lib_compress(FILE* source, FILE* dest) {
    BZFILE* b;
    int bufSize = 4;
    char buf[bufSize];
    int bzerror;

    b = BZ2_bzWriteOpen(&bzerror, dest, 9, 0, 0);
    if (bzerror != BZ_OK) {
        BZ2_bzWriteClose(&bzerror, b, 0, nullptr, nullptr);
        fprintf(stderr, "Error opening bz file");
        return;
    }

    while (fread(buf, 1, bufSize, source) == bufSize) {
        /* get data to write into buf, and set bufSize appropriately */
        BZ2_bzWrite(&bzerror, b, buf, bufSize);
        if (bzerror == BZ_IO_ERROR) {
            BZ2_bzWriteClose(&bzerror, b, 0, nullptr, nullptr);
            fprintf(stderr, "Error writing to bz file");
            return;
        }
    }

    BZ2_bzWriteClose(&bzerror, b, 0, nullptr, nullptr);
    if (bzerror == BZ_IO_ERROR) {
        fprintf(stderr, "Error closing bz file");
        return;
    }
}