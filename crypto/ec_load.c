#include "hblk_crypto.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <openssl/pem.h>

/**
 * ec_load - Loads an EC key pair from the disk
 * @folder: The path to the folder from which to load the keys
 *
 * Return: Pointer to EC key pair upon success, or NULL upon failure
 */
EC_KEY *ec_load(char const *folder)
{
	FILE *fp_pub, *fp_priv;
	char path_pub[1024];
	char path_priv[1024];
	EC_KEY *key = NULL;

	if (!folder)
		return (NULL);

	sprintf(path_pub, "%s/" PUB_FILENAME, folder);
	sprintf(path_priv, "%s/" PRI_FILENAME, folder);

	fp_pub = fopen(path_pub, "r");
	if (!fp_pub)
		return (NULL);

	if (!PEM_read_EC_PUBKEY(fp_pub, &key, NULL, NULL))
	{
		fclose(fp_pub);
		return (NULL);
	}
	fclose(fp_pub);

	fp_priv = fopen(path_priv, "r");
	if (!fp_priv)
	{
		EC_KEY_free(key);
		return (NULL);
	}

	if (!PEM_read_ECPrivateKey(fp_priv, &key, NULL, NULL))
	{
		fclose(fp_priv);
		EC_KEY_free(key);
		return (NULL);
	}
	fclose(fp_priv);

	return (key);
}
