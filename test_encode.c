#include <stdio.h>
#include "encode.h"
#include "decode.h"
#include "types.h"

int main(int argc, char *argv[])
{
    EncodeInfo encInfo;
    DecodeInfo decInfo;

    if (argc < 3)
    {
        printf("Usage:\n");
        printf("Encoding: %s -e <source.bmp> <secret.txt> [stego.bmp]\n", argv[0]);
        printf("Decoding: %s -d <stego.bmp> [output]\n", argv[0]);
        return 1;
    }

    if (check_operation_type(argv) == e_encode)
    {
        if (argc < 4)
        {
            printf("ERROR: Missing secret file\n");
            return 1;
        }

        if (read_and_validate_encode_args(argv, &encInfo) == e_failure)
        {
            printf("ERROR: Invalid encoding arguments\n");
            return 1;
        }

        if (do_encoding(&encInfo) == e_failure)
        {
            printf("ERROR: Encoding failed\n");
            return 1;
        }

        printf("INFO: Encoding completed successfully\n");
    }
    else if (check_operation_type(argv) == e_decode)
    {
        if (read_and_validate_decode_args(argv, &decInfo) == e_failure)
        {
            printf("ERROR: Invalid decoding arguments\n");
            return 1;
        }

        if (do_decoding(&decInfo) == e_failure)
        {
            printf("ERROR: Decoding failed\n");
            return 1;
        }

        printf("INFO: Decoding completed successfully\n");
    }
    else
    {
        printf("ERROR: Unsupported operation\n");
        return 1;
    }

    return 0;
}

