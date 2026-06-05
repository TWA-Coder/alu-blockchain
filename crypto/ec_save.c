#include "hblk_crypto.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <openssl/pem.h>

/**
 * ec_save - saves an existing EC key pair on the disk.
 * @key: points to the EC key pair to be saved on disk
 * @folder: the path to the folder in which to save the keys
 *
 * Return: 1 upon success or 0 upon failure
 */
int ec_save(EC_KEY *key, char const *folder)
{
	char path[1024];
	FILE *fp_priv, *fp_pub;
	int ret = 0;

	if (!key || !folder)
		return (0);

	mkdir(folder, 0755);

	snprintf(path, 1024, "%s/%s", folder, "key.pem");
	fp_priv = fopen(path, "w");
	if (!fp_priv)
		return (0);

	snprintf(path, 1024, "%s/%s", folder, "key_pub.pem");
	fp_pub = fopen(path, "w");
	if (!fp_pub)
	{
		fclose(fp_priv);
		return (0);
	}

	if (PEM_write_ECPrivateKey(fp_priv, key, NULL, NULL, 0, NULL, NULL) &&
	    PEM_write_EC_PUBKEY(fp_pub, key))
		ret = 1;

	fclose(fp_priv);
	fclose(fp_pub);

	return (ret);
}
