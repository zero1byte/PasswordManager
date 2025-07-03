// 1. Generate Key pair of Public and Private key of RSA
using namespace std;

#include <string.h>
#include <iostream>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/err.h>

// check with macro that Is there already included or not
#include "../constants.cpp"
#include "files.cpp"

class keys
{

public:
    keys()
    {
        cout << "Keys Operations" << endl;
    }

    void handleErrors()
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    // generate public-private key pair and store in file
    bool rsa_key_pair()
    {
        ERR_load_crypto_strings();
        OpenSSL_add_all_algorithms();

        // Create context for key generation
        EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
        if (!ctx)
            handleErrors();

        if (EVP_PKEY_keygen_init(ctx) <= 0)
            handleErrors();

        if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0)
            handleErrors();

        EVP_PKEY *pkey = nullptr;
        if (EVP_PKEY_keygen(ctx, &pkey) <= 0)
            handleErrors();

        // Write private key
        BIO *bio_private = BIO_new(BIO_s_mem());
        if (!PEM_write_bio_PrivateKey(bio_private, pkey, NULL, NULL, 0, NULL, NULL))
            handleErrors();

        char *private_key_cstr;
        long priv_len = BIO_get_mem_data(bio_private, &private_key_cstr);

        // insert private key into file
        // if not then create private file to store key
        filesManagement file(DATA_FOLDER);
        file.create_file(PRIVATE_KEY_FILE_NAME);

        // get file path and store private key
        string path = DATA_FOLDER;
        path.append("/");
        path.append(string(PRIVATE_KEY_FILE_NAME));
        ofstream Keyfile(path);
        Keyfile << std::string(private_key_cstr, priv_len) << std::endl;
        Keyfile.close();

        // Write public key
        BIO *bio_public = BIO_new(BIO_s_mem());
        if (!PEM_write_bio_PUBKEY(bio_public, pkey))
            handleErrors();
        char *public_key_cstr;
        long pub_len = BIO_get_mem_data(bio_public, &public_key_cstr);

        // store public key at file
        file.create_file(PUBLIC_KEY_FILE_NAME);
        string path_pr = DATA_FOLDER;
        path_pr.append("/").append(PUBLIC_KEY_FILE_NAME);
        ofstream public_key_file(path_pr);
        public_key_file << std::string(public_key_cstr, pub_len) << std::endl;
        public_key_file.close();

        // Cleanup
        BIO_free_all(bio_private);
        BIO_free_all(bio_public);
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);
        EVP_cleanup();
        ERR_free_strings();

        return 0;
    }
};
