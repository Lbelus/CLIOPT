#include <cli_cgetopt.h>
#include <string.h>

void set_bitmap(bmp_t* bmp)
{
    for (int index = 0; index < BITMAP_SIZE; index++)
    {
        bmp[index].data =  0x00;
    }
}


void set_bit(bmp_t* bmp, int index, int value)
{
    if (value)
    {
        bmp->data |= (1 << index);
    }
    else
    {
        bmp->data &= ~(1 << index);
    }
}

void set_in_bmp(bmp_t* bmp, unsigned int index, int value)
{
    unsigned int bmp_index = index / 8;
    unsigned int bit_index = index % 8;

    set_bit(&bmp[bmp_index], bit_index, value);
}

int get_bit(bmp_t bmp, unsigned int index)
{
    return (bmp.data >> index) & 1;
}

int is_flag_active(my_getopt_t* getopt_ptr, unsigned char ch)
{
    unsigned int index = (unsigned int)ch;
    unsigned int byte_index = index / 8;
    unsigned int bit_index = index % 8;
    int result = get_bit(getopt_ptr->bmp[byte_index], bit_index);
    return result;
}

void flag_state(char opt, my_getopt_t *getopt_ptr, char** argv)
{
    switch (opt)
    {
        case ':':
            strcpy(getopt_ptr->str_arr[getopt_ptr->str_pos], argv[getopt_ptr->index]); // _my_strcpy: asm is still causing some issues :/
            getopt_ptr->str_pos += 1;
            getopt_ptr->index += 1;
            break;
        default:
            set_in_bmp(getopt_ptr->bmp, (unsigned int)opt, true);
    }
}
