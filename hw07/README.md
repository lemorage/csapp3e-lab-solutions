#### 7.6
| Symbol  | `swap.o` `.symtab` entry? | Symbol type | Module where defined | Section |
| :-----: | :-----------------------: | :---------: | :------------------: | :-----: |
|  `buf`  |            YES            |   extern    |        `m.o`         | `.data` |
| `bufp0` |            YES            |   global    |       `swap.o`       | `.data` |
| `bufp1` |            YES            |   global    |       `swap.o`       | `.bss`  |
| `swap`  |            YES            |   global    |       `swap.o`       | `.text` |
| `temp`  |            NO             |      —      |          —           |    —    |
| `incr`  |            YES            |   global    |          —           | `.text` |
| `count` |            NO             |      —      |          —           |    —    |

#### 7.7
```c
/* bar5.c */
double x;

void f()
{
    // x = -0.0 /* Delete this line */
}
```

#### 7.8
A.
(a) ERROR
(b) ERROR

B.
(a) REF(x.1) -> DEF(x.UNKNOWN)
(b) REF(x.2) -> DEF(x.UNKNOWN)

C.
(a) ERROR
(b) ERROR

#### 7.9

#### 7.10

#### 7.11

#### 7.12

#### 7.13