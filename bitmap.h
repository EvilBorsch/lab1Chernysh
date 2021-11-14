typedef uint32_t bitmap_t;

#define RESERVE_BITS(n) (((n)+0x1f)>>5)
#define DW_INDEX(x) ((x)>>5)
#define BIT_INDEX(x) ((x)&0x1f)

#define getbit(array, index) (((array)[DW_INDEX(index)]>>BIT_INDEX(index))&1)
#define putbit(array, index, bit) \
    ((bit)&1 ?  ((array)[DW_INDEX(index)] |= 1<<BIT_INDEX(index)) \
             :  ((array)[DW_INDEX(index)] &= ~(1<<BIT_INDEX(index))) \
             , 0 \
    )