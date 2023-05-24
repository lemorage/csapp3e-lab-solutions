CFLAGS = -Og
CC = gcc
ARCH := $(shell uname -m)

COMMON_TARGETS = is-little-endian \
		 combine-bytes \
		 replace-byte \
		 evaluate \
		 int-shifts-are-arithmetic \
		 srl-sra \
		 detect-ones \
		 bad-int-size-is-32 \
		 lower-one-mask \
		 rotate-left \
		 fits-bits\
		 xbyte\
		 copy-int\
		 saturating-add\
		 tsub-ok\
		 unsigned-high-prod\
		 calloc\
		 divide-power2\
		 mul3div4\
		 threefourths\
		 patterns


ifeq ($(ARCH), i686)
	ARCH_TARGET = show-bytes32
else
	ARCH_TARGET = show-bytes64
endif

all: $(COMMON_TARGETS) $(ARCH_TARGET)
	@echo "All targets built"

# 2.55 ~ 2.57
show-bytes32: show-bytes.c
	$(CC) $(CFLAGS) -m32 show-bytes.c -o show-bytes32

show-bytes64: show-bytes.c
	$(CC) $(CFLAGS) -m64 show-bytes.c -o show-bytes64

# 2.58
is-little-endian: is-little-endian.c
	$(CC) $(CFLAGS) is-little-endian.c -o is-little-endian

# 2.59
combine-bytes: combine-bytes.c
	$(CC) $(CFLAGS) combine-bytes.c -o combine-bytes

# 2.60
replace-byte: replace-byte.c
	$(CC) $(CFLAGS) replace-byte.c -o replace-byte

# 2.61
evaluate: evaluate.c
	$(CC) $(CFLAGS) evaluate.c -o evaluate

# 2.62
int-shifts-are-arithmetic: int-shifts-are-arithmetic.c
	$(CC) $(CFLAGS) int-shifts-are-arithmetic.c -o int-shifts-are-arithmetic

# 2.63
srl-sra: srl-sra.c
	$(CC) $(CFLAGS) srl-sra.c -o srl-sra

# 2.64 ~ 2.66
detect-ones: detect-ones.c
	$(CC) $(CFLAGS) detect-ones.c -o detect-ones

# 2.67
bad-int-size-is-32: bad-int-size-is-32.c
	$(CC) $(CFLAGS) bad-int-size-is-32.c -o bad-int-size-is-32

# 2.68
lower-one-mask: lower-one-mask.c
	$(CC) $(CFLAGS) lower-one-mask.c -o lower-one-mask

# 2.69
rotate-left: rotate-left.c
	$(CC) $(CFLAGS) rotate-left.c -o rotate-left

# 2.70
fits-bits: fits-bits.c
	$(CC) $(CFLAGS) fits-bits.c -o fits-bits

# 2.71
xbyte: xbyte.c
	$(CC) $(CFLAGS) xbyte.c -o xbyte

# 2.72
copy-int: copy-int.c
	$(CC) $(CFLAGS) copy-int.c -o copy-int

# 2.73
saturating-add: saturating-add.c
	$(CC) $(CFLAGS) saturating-add.c -o saturating-add

# 2.74
tsub-ok: tsub-ok.c
	$(CC) $(CFLAGS) tsub-ok.c -o tsub-ok

# 2.75
unsigned-high-prod: unsigned-high-prod.c
	$(CC) $(CFLAGS) unsigned-high-prod.c -o unsigned-high-prod

# 2.76
calloc: calloc.c
	$(CC) $(CFLAGS) calloc.c -o calloc
	
# 2.78
divide-power2: divide-power2.c
	$(CC) $(CFLAGS) divide-power2.c -o divide-power2

# 2.79
mul3div4: mul3div4.c
	$(CC) $(CFLAGS) mul3div4.c -o mul3div4

# 2.80
threefourths: threefourths.c
	$(CC) $(CFLAGS) threefourths.c -o threefourths

# 2.81
patterns: patterns.c
	$(CC) $(CFLAGS) patterns.c -o patterns

.PHONY: run
run: $(ARCH_TARGET) $(COMMON_TARGETS)
	for target in $^; do ./$$target; done

clean:
	rm -f *~ *.o $(COMMON_TARGETS) $(ARCH_TARGET)
	@echo "All targets cleaned"
