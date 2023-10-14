#### 10.6
It will print out "fd2 = 4".

*Process:*
Unix processes begin life with open descriptors assigned to stdin (descriptor 0), stdout (descriptor 1), and stderr (descriptor 2). The `open` function always returns the lowest unopened descriptor, so the first call to `open` returns descriptor 3. The second call to `open` returns descriptor 4. The call to the close function frees up descriptor 4. The final call to open returns descriptor 4 again, and thus the output of the program is fd2 = 4.

#### 10.7

#### 10.8

#### 10.9

#### 10.10

