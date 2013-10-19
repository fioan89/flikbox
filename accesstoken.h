#ifndef ACCESSTOKEN_H
#define ACCESSTOKEN_H

#include <QString>
class AccessToken
{
private:
    QString oauthToken;
    QString secretToken;
public:
    AccessToken();
    QString getOAuthToken();
    void setOAuthToken(QString oauthToken);
    QString getSecretToken();
    void setSecretToken(QString secretToken);
};

#endif // ACCESSTOKEN_H
