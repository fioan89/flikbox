#include <QCryptographicHash>
#include "crypto.h"


Crypto::Crypto()
{
}

QString Crypto::getRandomString(unsigned int stringLength)
{
    QChar chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    QString nonce("");
    unsigned int i;
    srand((unsigned)time(0));
    for (i = 0; i < stringLength; i++)
    {
        int index = rand() % 10;
        nonce[i] =  chars[index];
    }
    return nonce;
}

// credits to: http://qt-project.org/wiki/HMAC-SHA1
QString Crypto::toHmacSha1(QByteArray baseString, QByteArray key)
{
    int blockSize = 64; // HMAC-SHA-1 block size, defined in SHA-1 standard
    if (key.length() > blockSize) { // if key is longer than block size (64), reduce key length with SHA-1 compression
        key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
    }

    QByteArray innerPadding(blockSize, char(0x36)); // initialize inner padding with char "6"
    QByteArray outerPadding(blockSize, char(0x5c)); // initialize outer padding with char "\"
    // ascii characters 0x36 ("6") and 0x5c ("\") are selected because they have large
    // Hamming distance (http://en.wikipedia.org/wiki/Hamming_distance)

    for (int i = 0; i < key.length(); i++) {
        innerPadding[i] = innerPadding[i] ^ key.at(i); // XOR operation between every byte in key and innerpadding, of key length
        outerPadding[i] = outerPadding[i] ^ key.at(i); // XOR operation between every byte in key and outerpadding, of key length
    }

    // result = hash ( outerPadding CONCAT hash ( innerPadding CONCAT baseString ) ).toBase64
    QByteArray total = outerPadding;
    QByteArray part = innerPadding;
    part.append(baseString);
    total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
    QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);
    return hashed.toBase64();
}
