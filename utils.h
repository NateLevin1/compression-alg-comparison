#include <stdio.h>
#include <ftw.h>
#include <unistd.h>

int rmrf(char *path);

void runTest(const char* name, const char* dataset, char* tempDir, void (*cb)(FILE*, FILE*));