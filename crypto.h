#ifndef CRYPTO_H
#define CRYPTO_H

#include <QString>

class Crypto
{
public:
    Crypto();

    /**
     * @brief getRandomString Builds a random string with length stringLength. Used by oauth protocol.
     * @param stringLength how many characters long you want youre string to be.
     * @return a random string of length stringLength.
     */
    static QString getRandomString(unsigned int stringLength);

    /**
     * @brief toHmacSha1 Encodes baseString using hmac-sha1 algorithm.
     * @param baseString message to be encoded.
     * @param key used by algorithm to encode.
     * @return a string representing the baseString encoded with key
     * using hmac-sha1 algorithm.
     */
    static QString toHmacSha1(QByteArray baseString, QByteArray key);
};

#endif // CRYPTO_H
