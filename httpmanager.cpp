#include "httpmanager.h"

HTTPManager::HTTPManager()
{
    this->networkManager = new QNetworkAccessManager(this);
}

HTTPManager& HTTPManager::getInstance()
{
    static HTTPManager instance;
    return instance;
}

QNetworkAccessManager* HTTPManager::getNetworkAccessManager()
{
    return this->networkManager;
}

void HTTPManager::setNetworkAccessManager(QNetworkAccessManager* networkAccessManager)
{
    this->networkManager = networkAccessManager;
}

HTTPManager::~HTTPManager()
{
    delete this->networkManager;
}
