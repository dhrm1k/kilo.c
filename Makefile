# Target name
kilo: kilo.c
	gcc kilo.c -o kilo -Wall -Wextra -pedantic -std=c99

# Clean build artifacts
clean:
	rm -f kilo

