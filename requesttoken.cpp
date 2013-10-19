#include "requesttoken.h"

RequestToken::RequestToken()
{
    this->oauthToken = "";
    this->oauthVerifier = "";
}

QString RequestToken::getOAuthToken()
{
    return this->oauthToken;
}

void RequestToken::setOAuthToken(QString token)
{
    this->oauthToken = token;
}

QString RequestToken::getOAuthVerifier()
{
    return this->oauthVerifier;
}

void RequestToken::setOAuthVerifier(QString verifier)
{
    this->oauthVerifier = oauthVerifier;
}
