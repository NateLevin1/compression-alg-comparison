#include "lzlib.h"
#include <algorithm>
#include <lzlib.h>

struct LZ_Encoder *encoder = nullptr;

// https://www.nongnu.org/lzip/manual/lzlib_manual.html#File-compression
int lzlib_compress(FILE *const infile, FILE *const outfile)
{
    if (encoder == nullptr)
    {
        encoder = LZ_compress_open(8e+6, 36, 1e+15);
        if (LZ_compress_errno(encoder) != LZ_ok)
        {
            LZ_compress_close(encoder);
            encoder = nullptr;
            return -1;
        }
    }

    LZ_compress_restart_member(encoder, 1e+15);

    int buffer_size = 16384;

    uint8_t buffer[buffer_size];
    int e = 0;
    while (true)
    {
        e++;
        int len, ret;
        int size = std::min(buffer_size, LZ_compress_write_size(encoder));
        if (size > 0)
        {
            len = fread(buffer, 1, size, infile);
            ret = LZ_compress_write(encoder, buffer, len);
            if (ret < 0 || ferror(infile))
                break;
            if (feof(infile))
                LZ_compress_finish(encoder);
        }
        ret = LZ_compress_read(encoder, buffer, buffer_size);
        if (ret < 0)
            break;
        len = fwrite(buffer, 1, ret, outfile);
        if (len < ret)
            break;
        if (LZ_compress_finished(encoder) == 1) {
            return 0;
        }
    }
    return 1;
}