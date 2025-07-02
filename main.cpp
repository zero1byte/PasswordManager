#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <iostream>

void handleErrors() {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
}

int main() {
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();

    // Create context for key generation
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx)
        handleErrors();

    if (EVP_PKEY_keygen_init(ctx) <= 0)
        handleErrors();

    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0)
        handleErrors();

    EVP_PKEY* pkey = nullptr;
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0)
        handleErrors();

    // Write private key
    BIO* bio_private = BIO_new(BIO_s_mem());
    if (!PEM_write_bio_PrivateKey(bio_private, pkey, NULL, NULL, 0, NULL, NULL))
        handleErrors();

    char* private_key_cstr;
    long priv_len = BIO_get_mem_data(bio_private, &private_key_cstr);
    std::cout << "Private Key:\n" << std::string(private_key_cstr, priv_len) << std::endl;

    // Write public key
    BIO* bio_public = BIO_new(BIO_s_mem());
    if (!PEM_write_bio_PUBKEY(bio_public, pkey))
        handleErrors();

    char* public_key_cstr;
    long pub_len = BIO_get_mem_data(bio_public, &public_key_cstr);
    std::cout << "Public Key:\n" << std::string(public_key_cstr, pub_len) << std::endl;

    // Cleanup
    BIO_free_all(bio_private);
    BIO_free_all(bio_public);
    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);
    EVP_cleanup();
    ERR_free_strings();

    return 0;
}
