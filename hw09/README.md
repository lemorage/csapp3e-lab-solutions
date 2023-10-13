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

#### 9.18

#### 9.19

#### 9.20

