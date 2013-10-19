#include "accesstoken.h"

AccessToken::AccessToken()
{
    this->oauthToken = "";
    this->secretToken = "";
}

QString AccessToken::getOAuthToken()
{
    return this->oauthToken;
}

void AccessToken::setOAuthToken(QString oauthToken)
{
    this->oauthToken = oauthToken;
}

QString AccessToken::getSecretToken()
{
    return this->secretToken;
}

void AccessToken::setSecretToken(QString secretToken)
{
    this->secretToken = secretToken;
}
