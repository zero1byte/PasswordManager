// 1. Generate Key pair of Public and Private key of RSA
using namespace std;

#include <string.h>
#include <iostream>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/engine.h>
#include <openssl/evp.h>
#include <vector>

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

    string encrypt(string dataString)
    {
        filesManagement file;

        // Read public key from file
        std::string public_key = file.get_public_key();

        // Load public key from PEM string
        BIO *bio = BIO_new_mem_buf(public_key.data(), public_key.size());
        if (!bio)
        {
            std::cerr << "Failed to create BIO for public key" << std::endl;
            return "";
        }
        EVP_PKEY *pkey = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
        BIO_free(bio);
        if (!pkey)
        {
            std::cerr << "Failed to load public key" << std::endl;
            return "";
        }

        // Prepare encryption context
        EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, NULL);
        if (!ctx)
        {
            EVP_PKEY_free(pkey);
            std::cerr << "Failed to create context" << std::endl;
            return "";
        }
        if (EVP_PKEY_encrypt_init(ctx) <= 0)
        {
            EVP_PKEY_CTX_free(ctx);
            EVP_PKEY_free(pkey);
            std::cerr << "Failed to init encrypt" << std::endl;
            return "";
        }

        // Determine buffer length
        size_t outlen = 0;
        const unsigned char *plaintext = reinterpret_cast<const unsigned char *>(dataString.c_str());
        size_t plaintext_len = dataString.size();
        if (EVP_PKEY_encrypt(ctx, NULL, &outlen, plaintext, plaintext_len) <= 0)
        {
            EVP_PKEY_CTX_free(ctx);
            EVP_PKEY_free(pkey);
            std::cerr << "Failed to determine encrypted length" << std::endl;
            return "";
        }

        std::vector<unsigned char> outbuf(outlen);
        if (EVP_PKEY_encrypt(ctx, outbuf.data(), &outlen, plaintext, plaintext_len) <= 0)
        {
            EVP_PKEY_CTX_free(ctx);
            EVP_PKEY_free(pkey);
            std::cerr << "Encryption failed" << std::endl;
            return "";
        }

        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);

        // Encode to base64 for string output
        BIO *b64 = BIO_new(BIO_f_base64());
        BIO *mem = BIO_new(BIO_s_mem());
        b64 = BIO_push(b64, mem);
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        BIO_write(b64, outbuf.data(), outlen);
        BIO_flush(b64);

        BUF_MEM *bptr;
        BIO_get_mem_ptr(b64, &bptr);
        std::string encrypted_str(bptr->data, bptr->length);

        BIO_free_all(b64);

        cout<<encrypted_str<<endl;
        return encrypted_str;
    }

    string decrypt(string encrypted_string) {
        filesManagement file;

        // Read private key from file
        std::string private_key = file.get_private_key();

        // Load private key from PEM string
        BIO *bio = BIO_new_mem_buf(private_key.data(), private_key.size());
        if (!bio) {
            std::cerr << "Failed to create BIO for private key" << std::endl;
            return "";
        }
        EVP_PKEY *pkey = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL);
        BIO_free(bio);
        if (!pkey) {
            std::cerr << "Failed to load private key" << std::endl;
            return "";
        }

        // Decode base64
        BIO *b64 = BIO_new(BIO_f_base64());
        BIO *mem = BIO_new_mem_buf(encrypted_string.data(), encrypted_string.size());
        b64 = BIO_push(b64, mem);
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

        std::vector<unsigned char> encrypted_buf(encrypted_string.size());
        int encrypted_len = BIO_read(b64, encrypted_buf.data(), encrypted_buf.size());
        BIO_free_all(b64);

        if (encrypted_len <= 0) {
            EVP_PKEY_free(pkey);
            std::cerr << "Failed to decode base64" << std::endl;
            return "";
        }

        // Prepare decryption context
        EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, NULL);
        if (!ctx) {
            EVP_PKEY_free(pkey);
            std::cerr << "Failed to create context" << std::endl;
            return "";
        }
        if (EVP_PKEY_decrypt_init(ctx) <= 0) {
            EVP_PKEY_CTX_free(ctx);
            EVP_PKEY_free(pkey);
            std::cerr << "Failed to init decrypt" << std::endl;
            return "";
        }

        // Determine buffer length
        size_t outlen = 0;
        if (EVP_PKEY_decrypt(ctx, NULL, &outlen, encrypted_buf.data(), encrypted_len) <= 0) {
            EVP_PKEY_CTX_free(ctx);
            EVP_PKEY_free(pkey);
            std::cerr << "Failed to determine decrypted length" << std::endl;
            return "";
        }

        std::vector<unsigned char> outbuf(outlen);
        if (EVP_PKEY_decrypt(ctx, outbuf.data(), &outlen, encrypted_buf.data(), encrypted_len) <= 0) {
            EVP_PKEY_CTX_free(ctx);
            EVP_PKEY_free(pkey);
            std::cerr << "Decryption failed" << std::endl;
            return "";
        }

        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);

        return std::string(reinterpret_cast<char*>(outbuf.data()), outlen);
    }
};
