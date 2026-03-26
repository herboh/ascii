# ascii

Tiny C program for when K&R makes you realize you should probably know what a byte looks like.

Give it text and it prints each byte as `symbol`, `value`, `hex`, and `binary`. Run it with no args and no stdin and it dumps ASCII `0-127`. Pipe in large files or sets of strings or characters and it will print a formatted table.

### To run:

```sh
gcc -O3 -march=native -Wall -Wextra -o char char.c
./char A
./char < war_and_peace.txt
./char
```

### Requirements:

C Compiler

### More

Blog post: [`Prehistoric Programming: War and Peace in 200ms`](https://chanfulmer.com/blog/ripping-through-text/)
