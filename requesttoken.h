#ifndef REQUESTTOKEN_H
#define REQUESTTOKEN_H

#include <QString>

class RequestToken
{
private:
    QString oauthToken;
    QString oauthVerifier;
public:
    explicit RequestToken();
    QString getOAuthToken();
    QString getOAuthVerifier();
    void setOAuthToken(QString token);
    void setOAuthVerifier(QString verifier);
};

#endif // REQUESTTOKEN_H
