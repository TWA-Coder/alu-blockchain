#include "hblk_crypto.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <openssl/pem.h>

/**
 * ec_save - Saves an existing EC key pair on the disk
 * @key: Points to the EC key pair to be saved on disk
 * @folder: The path to the folder in which to save the keys
 *
 * Return: 1 upon success, 0 upon failure
 */
int ec_save(EC_KEY *key, char const *folder)
{
	FILE *fp_pub, *fp_priv;
	char path_pub[1024];
	char path_priv[1024];

	if (!key || !folder)
		return (0);

	mkdir(folder, 0755);

	sprintf(path_pub, "%s/key_pub.pem", folder);
	sprintf(path_priv, "%s/key.pem", folder);

	fp_pub = fopen(path_pub, "w");
	if (!fp_pub)
		return (0);

	if (!PEM_write_EC_PUBKEY(fp_pub, key))
	{
		fclose(fp_pub);
		return (0);
	}
	fclose(fp_pub);

	fp_priv = fopen(path_priv, "w");
	if (!fp_priv)
		return (0);

	if (!PEM_write_ECPrivateKey(fp_priv, key, NULL, NULL, 0, NULL, NULL))
	{
		fclose(fp_priv);
		return (0);
	}
	fclose(fp_priv);

	return (1);
}
