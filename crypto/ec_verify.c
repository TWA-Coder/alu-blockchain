#include "hblk_crypto.h"

/**
 * ec_verify - verifies the signature of a given set of bytes
 * @key: points to the EC_KEY structure containing the public key
 * @msg: points to the msglen characters to verify the signature of
 * @msglen: the length of msg
 * @sig: points to the signature to be checked
 *
 * Return: 1 if the signature is valid, and 0 otherwise
 */
int ec_verify(EC_KEY const *key, uint8_t const *msg,
		size_t msglen, sig_t const *sig)
{
	uint8_t digest[SHA256_DIGEST_LENGTH];

	if (!key || !msg || !sig)
		return (0);

	if (!sha256((int8_t const *)msg, msglen, digest))
		return (0);

	if (ECDSA_verify(0, digest, SHA256_DIGEST_LENGTH,
			 sig->sig, sig->len, (EC_KEY *)key) != 1)
		return (0);

	return (1);
}
