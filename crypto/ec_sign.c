#include "hblk_crypto.h"

/**
 * ec_sign - signs a given set of bytes, using a given EC_KEY private key
 * @key: points to the EC_KEY structure containing the private key
 * @msg: points to the msglen characters to be signed
 * @msglen: length of the message
 * @sig: holds the address at which to store the signature
 *
 * Return: pointer to the signature buffer upon success, NULL on failure
 */
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
		size_t msglen, sig_t *sig)
{
	uint8_t digest[SHA256_DIGEST_LENGTH];
	unsigned int siglen = 0;

	if (!key || !msg || !sig)
		return (NULL);

	if (!sha256((int8_t const *)msg, msglen, digest))
		return (NULL);

	if (!ECDSA_sign(0, digest, SHA256_DIGEST_LENGTH,
			sig->sig, &siglen, (EC_KEY *)key))
		return (NULL);

	sig->len = (uint8_t)siglen;
	return (sig->sig);
}
