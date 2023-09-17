# 7.13 A
locations=$(whereis libc.a | awk -F: '{print $2}')

if [ -n "$locations" ]; then
    first_location=$(echo "$locations" | awk '{print $1}')
    num_files=$(ar -t "$first_location" | wc -l)
    echo "libc.a has $num_files files in $first_location."
else
    echo "libc.a not found."
fi

locations=$(whereis libm.a | awk -F: '{print $2}')

if [ -n "$locations" ]; then
    first_location=$(echo "$locations" | awk '{print $1}')
    num_files=$(ar -t "$first_location" | wc -l)
    echo "libm.a has $num_files files in $first_location."
else
    echo "libm.a not found."
fi

# 7.13 C
locations=$(whereis gcc | awk -F: '{print $2}')
first_location=$(echo "$locations" | awk '{print $1}')
ldd $first_location
