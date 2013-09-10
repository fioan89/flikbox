#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QNetworkAccessManager>

class HTTPManager : public QObject
{
private:
    QNetworkAccessManager* networkManager;
    HTTPManager();
    HTTPManager(HTTPManager const&);
    void operator=(HTTPManager const&);
public:
    static HTTPManager& getInstance();
    QNetworkAccessManager* getNetworkAccessManager();
    void setNetworkAccessManager(QNetworkAccessManager* networkAccessManager);
    ~HTTPManager();
};

#endif // HTTPMANAGER_H
