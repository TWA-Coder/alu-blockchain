#include "hblk_crypto.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <openssl/pem.h>

/**
 * ec_load - loads an EC key pair from the disk.
 * @folder: the path to the folder from which to load the keys
 *
 * Return: pointer to the created EC key pair, or NULL upon failure
 */
EC_KEY *ec_load(char const *folder)
{
	char path[1024];
	FILE *fp_priv, *fp_pub;
	EC_KEY *key = NULL;

	if (!folder)
		return (NULL);

	snprintf(path, 1024, "%s/%s", folder, "key_pub.pem");
	fp_pub = fopen(path, "r");
	if (!fp_pub)
		return (NULL);

	snprintf(path, 1024, "%s/%s", folder, "key.pem");
	fp_priv = fopen(path, "r");
	if (!fp_priv)
	{
		fclose(fp_pub);
		return (NULL);
	}

	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (key)
	{
		if (!PEM_read_EC_PUBKEY(fp_pub, &key, NULL, NULL) ||
		    !PEM_read_ECPrivateKey(fp_priv, &key, NULL, NULL))
		{
			EC_KEY_free(key);
			key = NULL;
		}
	}

	fclose(fp_priv);
	fclose(fp_pub);

	return (key);
}
