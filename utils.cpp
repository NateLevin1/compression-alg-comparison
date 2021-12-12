#include <stdio.h>
#include <ftw.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <zlib.h>
#include <stdio.h>
#include <sys/stat.h>

void runTest(const char* name, const char* dataset, char* tempDir, void (*cb)(FILE*, FILE*)) {
    char outputLoc[100];
    strcpy(outputLoc, tempDir);
    strcat(outputLoc, "/");
    strcat(outputLoc, name);

    FILE* outputFile = fopen(outputLoc, "wb");
    FILE* inputFile = fopen(dataset, "r");
    
    // * COMPRESSION RATIO TEST
    struct stat beforeStats;
    stat(dataset, &beforeStats);
    unsigned long inputSize = beforeStats.st_size;
    
    // only run once
    cb(inputFile, outputFile);

    fclose(outputFile);

    // must do this after closing the file
    struct stat afterStats;
    stat(outputLoc, &afterStats);
    unsigned long afterSize = afterStats.st_size;

    double percentSaved = 1 - (afterSize / ((double)inputSize));

    // * TIME TEST
    unsigned long beforeTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    for(int i = 0; i < 10000; i++) {
        outputFile = fopen(outputLoc, "wb");
        cb(inputFile, outputFile);
        fclose(outputFile);
    }

    unsigned long afterTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    unsigned long totalTestTime = afterTime-beforeTime;

    fclose(inputFile);

    printf("\n%s TEST\n--------------------------------\nTime Taken: %lums.\nCompression ratio = %i%% (input=%lu, after=%lu)\n", name, totalTestTime, (int)(percentSaved*100), inputSize, afterSize);
}

int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    int rv = remove(fpath);

    if (rv)
        perror(fpath);

    return rv;
}

int rmrf(char *path)
{
    return nftw(path, unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
}