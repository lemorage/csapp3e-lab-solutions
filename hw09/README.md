#### 9.11
A.

|  0   |  0   |  0   |  0   |  1   |  0   |  0   |  1   |  1   |  1   |  1   |  1   |  0   |  0   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|  13  |  12  |  11  |  10  |  9   |  8   |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |

B.

|     Parameter     | Value |
| :---------------: | :---: |
|        VPN        | 0x09  |
|     TLB index     | 0x01  |
|      TLB tag      | 0x02  |
|  TLB hit? (Y/N)   |   N   |
| Page fault? (Y/N) |   N   |
|        PPN        |  17   |

C.
PPN = 0x11, PPO = 0x3C
|  0   |  1   |  0   |  0   |  0   |  1   |  1   |  1   |  1   |  1   |  0   |  0   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|  11  |  10  |  9   |  8   |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |

D.
|      Parameter      | Value |
| :-----------------: | :---: |
|     Byte offset     | 0x00  |
|     Cache index     | 0x0f  |
|      Cache tag      | 0x11  |
|  Cache hit? (Y/N)   |   N   |
| Cache byte returned |   N   |

#### 9.12
A.

|  0   |  0   |  0   |  0   |  1   |  1   |  1   |  0   |  1   |  0   |  1   |  0   |  0   |  1   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|  13  |  12  |  11  |  10  |  9   |  8   |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |

B.

|     Parameter     | Value |
| :---------------: | :---: |
|        VPN        |  0xE  |
|     TLB index     | 0x02  |
|      TLB tag      | 0x03  |
|  TLB hit? (Y/N)   |   N   |
| Page fault? (Y/N) |   N   |
|        PPN        |   —   |

C.
PPN = 0x11, PPO = 0x29
|  0   |  1   |  0   |  0   |  0   |  1   |  1   |  0   |  1   |  0   |  0   |  1   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|  11  |  10  |  9   |  8   |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |

D.
|      Parameter      | Value |
| :-----------------: | :---: |
|     Byte offset     | 0x01  |
|     Cache index     | 0x0a  |
|      Cache tag      | 0x11  |
|  Cache hit? (Y/N)   |   N   |
| Cache byte returned |   N   |

#### 9.13
A.

|  0   |  0   |  0   |  0   |  0   |  0   |  0   |  1   |  0   |  0   |  0   |  0   |  0   |  0   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|  13  |  12  |  11  |  10  |  9   |  8   |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |

B.

|     Parameter     | Value |
| :---------------: | :---: |
|        VPN        | 0x01  |
|     TLB index     | 0x01  |
|      TLB tag      | 0x00  |
|  TLB hit? (Y/N)   |   N   |
| Page fault? (Y/N) |   Y   |
|        PPN        |   —   |


#### 9.14
Run the command `gcc change-hello.c -o change`

#### 9.15
As said before, the general approach for determining the block size is to round the sum of the requested payload and the header size to the nearest multiple of the alignment requirement.
|   Request    | Block size (decimal bytes) | Block header (hex) |
| :----------: | :------------------------: | :----------------: |
| `malloc(4)`  |             8              |        0x9         |
| `malloc(7)`  |             16             |        0x11        |
| `malloc(19)` |             24             |        0x19        |
| `malloc(22)` |             32             |        0x21        |


#### 9.16
As mentioned before, the minimum block size is the maximum of the minimum allocated block size and the minimum free block size.
|  Alignment  |    Allocated block    |    Free block     | Minimum block size (bytes) |
| :---------: | :-------------------: | :---------------: | :------------------------: |
| Single word |   Header and footer   | Header and footer |             12             |
| Single word | Header, but no footer | Header and footer |             8              |
| Double word |   Header and footer   | Header and footer |             16             |
| Double word | Header, but no footer | Header and footer |             8              |

#### 9.17
```c
static void *find_fit(size_t asize)
{
    /* Next fit search */
    char *oldrover = rover;

    /* Search from the rover to the end of list */
    for ( ; GET_SIZE(HDRP(rover)) > 0; rover = NEXT_BLKP(rover))
        if (!GET_ALLOC(HDRP(rover)) && (asize <= GET_SIZE(HDRP(rover))))
            return rover;

    /* search from start of list to old rover */
    for (rover = heap_listp; rover < oldrover; rover = NEXT_BLKP(rover))
        if (!GET_ALLOC(HDRP(rover)) && (asize <= GET_SIZE(HDRP(rover))))
            return rover;

    return NULL;  /* no fit found */
}
```

#### 9.18
```c
/* ... [rest of the code remains unchanged] ... */

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(HDRP(bp))) 
#define PREV_BLKP(bp)  ((char *)(bp) - (GET_ALLOC(HDRP(bp)) ? GET_SIZE(HDRP(bp)) : (GET_SIZE(HDRP(bp)) + GET_SIZE((char *)(bp) - WSIZE))))

/* ... [rest of the code remains unchanged] ... */

/* 
 * place - Place block of asize bytes at start of free block bp 
 *         and split if remainder would be at least minimum block size
 */
static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));   

    if ((csize - asize) >= (2*DSIZE)) { 
        PUT(HDRP(bp), PACK(asize, 1)); // Set header for allocated block
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0)); // Set header for free block
        PUT(FTRP(bp), PACK(csize-asize, 0)); // Set footer for free block
    }
    else { 
        PUT(HDRP(bp), PACK(csize, 1)); // Set header for allocated block
    }
}

/* 
 * coalesce - Boundary tag coalescing. Return ptr to coalesced block
 */
static void *coalesce(void *bp) 
{
    size_t prev_alloc = GET_ALLOC(HDRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) {            /* Case 1: Both previous and next blocks are allocated */
        return bp;
    }

    else if (prev_alloc && !next_alloc) {      /* Case 2: Previous block is allocated, next block is free */
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    }

    else if (!prev_alloc && next_alloc) {      /* Case 3: Previous block is free, next block is allocated */
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    else {                                     /* Case 4: Both previous and next blocks are free */
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    return bp;
}
/* ... [rest of the code remains unchanged] ... */
```

The main changes are in the `place` and `coalesce` functions. In the `place` function, when allocating a block, we only set the header. If there's a remainder that can be split into a new free block, we set both the header and the footer for the free block. In the `coalesce` function, we've adjusted the logic to account for the fact that allocated blocks don't have footers.

#### 9.19
1.\
(a) In a buddy system, up to 50% of the space can be wasted due to internal fragmentation. 
- **True**: In the worst case, if you need just one byte more than half of a buddy block, you'll have to allocate the entire block, wasting almost half of it.

2.\
(d) Using the first-fit algorithm on a free list that is ordered according to increasing block sizes is equivalent to using the best-fit algorithm.
- **True**: If the list is ordered by increasing block sizes, the first block that fits the request in a first-fit search will also be the best fit.

3.\
(b) They treat everything that looks like a pointer as a pointer.
- **True**: Conservative garbage collectors don't have exact knowledge of where all pointers are, so they treat any value that could be a pointer as a pointer to avoid accidentally collecting live data.

<br/>

So, the true statements for each group are:
1. (a)
2. (d)
3. (b)

#### 9.20
```cmd
$ gcc benchmark.c mymemory.c -o benchmark
$ ./benchmark
Standard malloc/free: 0.051027 seconds
Custom mymalloc/myfree: 4.081688 seconds
```
