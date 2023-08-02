#### 6.22
Given:
- BPT (bits per track) = x * 2πr (circumference of the innermost track)
- TC (track count) = (1 - x) * 2πr (circumference of the outermost track)
- BC (bit count) = BPT * TC (total bits on the disk)

We want to find the value of x that maximizes BC.

Substitute BPT and TC into BC:
BC = (x * 2πr) * ((1 - x) * 2πr)

Expand and simplify the equation:
BC = 4π^2 * x * (1 - x) * r^2

Now, we have a quadratic equation in terms of x. To find the maximum value of BC, we need to find the vertex of this quadratic equation. The x-coordinate of the vertex can be found using the formula x = -b / 2a, where a = 4π^2 * r^2 and b = -4π^2 * r^2.

x = -(-4π^2 * r^2) / (2 * 4π^2 * r^2)\
x = 1/2

The value of x that maximizes BC is 1/2. Therefore, when the radius of the hole is half the radius of the platter (x * r = 1/2 * r), the capacity of the disk is maximized.

#### 6.23
Given parameters:
- Rotational rate: 12,000 RPM (Revolutions Per Minute)
- Tavg seek: 3 ms (Average Seek Time)
- Average number of sectors/track: 500

1. Rotational Latency:
T<sub>avg rotation</sub> = 1/2 * T<sub>max rotation</sub>\
T<sub>avg rotation</sub> = 1/2 * (60 seconds / 12,000 RPM) * 1000 ms/sec\
T<sub>avg rotation</sub> ≈ 2.5 ms

2. Transfer Time:
T<sub>avg transfer</sub> = (60 seconds / 12,000 RPM) * (1 / 500 sectors/track) * 1000 ms/sec\
T<sub>avg transfer</sub> ≈ 0.01 ms

3. Average Access Time:
T<sub>access</sub> = T<sub>avg seek</sub> + T<sub>avg rotation</sub> + T<sub>avg transfer</sub>\
T<sub>access</sub> = 3 ms + 2.5 ms + 0.01 ms ≈ 5.51 ms


So, the average time to access a sector on the disk is approximately 5.51 milliseconds (ms).

#### 6.24
First we need to determine a few basic properties of the file and the disk. The file consists of 20,000 512-byte logical blocks. For the disk, T<sub>avg seek</sub> = 8 ms, T<sub>max rotation</sub> = 3.34 ms, and T<sub>avg rotation</sub> = 1.67 ms.
<br/>

A. Best case: In the optimal case, the blocks are mapped to contiguous sectors, on the same cylinder, that can be read one after the other without moving the head. Once the head is positioned over the first sector it takes two full rotations (5,000 sectors per rotation) of the disk to read all 10,000 blocks. So the total time to read the file is T<sub>avg seek</sub> + T<sub>avg rotation</sub> + 2 × T<sub>max rotation</sub> = 8 + 1.67 + 6.68 = 16.35 ms.
<br/>

B. Random case: In this case, where blocks are mapped randomly to sectors, reading each of the 10,000 blocks requires T<sub>avg seek</sub> + T<sub>avg rotation</sub> ms, so the total time to read the file is (T<sub>avg seek</sub> + T<sub>avg rotation</sub>) × 10,000 = 96,700 ms (96.7 seconds!).

#### 6.25
| Cache |  m   |   C   |  B   |  E   |  S   |  t   |  s   |  b   |
| :---: | :--: | :---: | :--: | :--: | :--: | :--: | :--: | :--: |
|  1.   |  32  | 1,024 |  4   |  4   |  64  |  24  |  6   |  2   |
|  2.   |  32  | 1,024 |  4   | 256  |  1   |  30  |  0   |  2   |
|  3.   |  32  | 1,024 |  8   |  1   | 128  |  22  |  7   |  3   |
|  4.   |  32  | 1,024 |  8   | 128  |  1   |  29  |  0   |  3   |
|  5.   |  32  | 1,024 |  32  |  1   |  32  |  22  |  5   |  5   |
|  6.   |  32  | 1,024 |  32  |  4   |  8   |  24  |  3   |  5   |

#### 6.26
| Cache |  m   |   C   |  B   |  E   |  S   |  t   |  s   |  b   |
| :---: | :--: | :---: | :--: | :--: | :--: | :--: | :--: | :--: |
|  1.   |  32  | 2,048 |  8   |  1   | 256  |  21  |  8   |  3   |
|  2.   |  32  | 2,048 |  4   |  4   | 128  |  23  |  7   |  2   |
|  3.   |  32  | 1,024 |  2   |  8   |  64  |  25  |  6   |  1   |
|  4.   |  32  | 1,024 |  32  |  2   |  16  |  23  |  4   |  5   |

#### 6.27

#### 6.28

#### 6.29

#### 6.30

#### 6.31

#### 6.32

#### 6.33

#### 6.34

#### 6.35

#### 6.36

#### 6.37

#### 6.38

#### 6.39

#### 6.40

#### 6.41

#### 6.42

#### 6.43

#### 6.44

#### 6.45

#### 6.46
