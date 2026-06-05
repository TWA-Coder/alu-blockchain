# Blockchain Cryptography

This project represents the cryptographic core of a Blockchain implementation. It relies on OpenSSL to provide hashing and elliptic curve operations.

## Environment
* **OS:** Ubuntu 14.04 LTS
* **Compiler:** `gcc 4.8.4`
* **Flags:** `-Wall -Werror -Wextra -pedantic` and linker flags `-lssl -lcrypto`

## Structure
* `crypto/hblk_crypto.h`: A central include-guarded header file containing all the function prototypes.
* `crypto/sha256.c`: Implements `sha256()`, a function that computes the hash of a sequence of bytes without allocating dynamic memory.

More functionality for elliptic curve operations will be added as the project progresses.