#include "hblk_crypto.h"
#include <string.h>
#include <openssl/ecdsa.h>
#include <openssl/sha.h>

/**
 * ec_sign - Signs a given set of bytes, using a given EC_KEY private key
 * @key: Points to the EC_KEY structure containing the private key
 * @msg: Points to the msglen characters to be signed
 * @msglen: The length of the message to be signed
 * @sig: Holds the address at which to store the signature
 *
 * Return: Pointer to the signature buffer upon success, NULL upon failure
 */
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
		size_t msglen, sig_t *sig)
{
	unsigned char dgst[SHA256_DIGEST_LENGTH];
	unsigned int siglen = 0;

	if (!key || !msg || !msglen || !sig)
		return (NULL);

	memset(sig->sig, 0, SIG_MAX_LEN);
	sig->len = 0;

	if (!SHA256(msg, msglen, dgst))
		return (NULL);

	if (ECDSA_sign(0, dgst, SHA256_DIGEST_LENGTH,
		       sig->sig, &siglen, (EC_KEY *)key) != 1)
	{
		return (NULL);
	}

	sig->len = (uint8_t)siglen;

	return (sig->sig);
}
