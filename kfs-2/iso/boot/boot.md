notes

taille kernel.bin

bytes=$(stat -c '%s' kernel.bin) && awk -v b="$bytes" 'BEGIN {printf "kernel.bin %d %.6f MiB\n", b, b/1024/1024}' 
