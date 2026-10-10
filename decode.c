#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "types.h"
#include "common.h"

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    if (strstr(argv[2], ".bmp") == NULL)
    {
        return e_failure;
    }

    decInfo->stego_image_fname = argv[2];

    if (argv[3] != NULL)
    {
        decInfo->output_fname = argv[3];
    }
    else
    {
        decInfo->output_fname = "output";
    }
    return e_success;
}

Status open_decode_files(DecodeInfo *decInfo)
{
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "rb");

    if (decInfo->fptr_stego_image == NULL)
    {
        return e_failure;
    }
    return e_success;
}

Status do_decoding(DecodeInfo *decInfo)
{
    if (open_decode_files(decInfo) == e_failure)
    {
        return e_failure;
    }
    fseek(decInfo->fptr_stego_image, 54, SEEK_SET);

    if (decode_magic_string(MAGIC_STRING, decInfo) == e_failure)
    {
        return e_failure;
    }

    if (decode_secret_file_extn(decInfo) == e_failure)
    {
        return e_failure;
    }

    if (decode_secret_file_size(decInfo) == e_failure)
    {
        return e_failure;
    }

    if (decode_secret_file_data(decInfo) == e_failure)
    {
        return e_failure;
    }
    return e_success;
}

Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo)
{
    char decoded_data[20];
    decode_data_from_image(decoded_data, strlen(magic_string), decInfo->fptr_stego_image, NULL);
    decoded_data[strlen(magic_string)] = '\0';
    if (strcmp(decoded_data, magic_string) == 0)
    {
        return e_success;
    }
    return e_failure;
}

Status decode_secret_file_extn(DecodeInfo *decInfo)
{
    char decoded_extn[10];
    if (decode_data_from_image(decoded_extn, 4, decInfo->fptr_stego_image, NULL) == e_failure)
    {
        return e_failure;
    }
    decoded_extn[4] = '\0';
    strcpy(decInfo->extn_secret_file, decoded_extn);
    return e_success;
}

Status decode_secret_file_size(DecodeInfo *decInfo)
{
    char image_buffer[8];
    long file_size = 0;

    for (size_t i = 0; i < sizeof(long); i++)
    {
        fread(image_buffer, 8, 1, decInfo->fptr_stego_image);

        decode_byte_from_lsb((char *)&file_size + i, image_buffer);
    }

    decInfo->size_secret_file = file_size;

    return e_success;
}

Status decode_secret_file_data(DecodeInfo *decInfo)
{
    char data;
    decInfo->fptr_output = fopen(decInfo->output_fname, "wb");
    if (decInfo->fptr_output == NULL)
    {
        return e_failure;
    }
    for (long i = 0; i < decInfo->size_secret_file; i++)
    {
        if (decode_data_from_image(&data, 1, decInfo->fptr_stego_image, decInfo->fptr_output) == e_failure)
        {
            return e_failure;
        }
    }
    fclose(decInfo->fptr_output);
    return e_success;
}

Status decode_data_from_image(char *data, int size, FILE *fptr_stego_image, FILE *fptr_output)
{
    char image_buffer[8];
    for (int i = 0; i < size; i++)
    {
        fread(image_buffer, 8, 1, fptr_stego_image);

        decode_byte_from_lsb(&data[i], image_buffer);

        if (fptr_output != NULL)
        {
            fwrite(&data[i], 1, 1, fptr_output);
        }
    }
    return e_success;
}

Status decode_byte_from_lsb(char *data, char *image_buffer)
{
    *data = 0;

    for (int i = 0; i < 8; i++)
    {
        *data = (*data << 1) | (image_buffer[i] & 1);
    }

    return e_success;
}
