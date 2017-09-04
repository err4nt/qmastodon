#ifndef MASTODON_H
#define MASTODON_H

#include <QObject>
#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QUrl>
#include <QList>
#include <QDateTime>

#include "qmastodon_global.h"
#include "mastodonaccount.h"
#include "mastodonstatus.h"


class QMASTODONSHARED_EXPORT mastodon : public QObject
{
    Q_OBJECT
    QNetworkAccessManager *manager;

    Q_PROPERTY(QString clientName MEMBER m_ClientName NOTIFY clientNameChanged)
    Q_PROPERTY(QString instanceURL MEMBER m_InstanceUrl NOTIFY instanceURLChanged)
    Q_PROPERTY(QString clientWebsite MEMBER m_ClientWebsite NOTIFY clientWebsiteChanged)
    Q_PROPERTY(QString clientScopes MEMBER m_ClientScopes NOTIFY clientScopesChanged)
    Q_PROPERTY(QString clientToken MEMBER m_ClientToken NOTIFY clientTokenChanged)
    Q_PROPERTY(QString clientId MEMBER m_ClientId NOTIFY clientIdChanged)
    Q_PROPERTY(QString clientSecret MEMBER m_ClientSecret NOTIFY clientSecretChanged)
    Q_PROPERTY(QString refreshToken MEMBER m_RefreshToken NOTIFY refreshTokenChanged)
    Q_PROPERTY(QDateTime refreshTokenExpire MEMBER m_RefreshTokenExpire NOTIFY refreshTokenExpireChanged)

private slots:
    void TokenRequestFinished();
    void AccessTokenRequestFinished();
    void TimelineRequestFinished();

signals:
    void storeClientCredentials(QString *ClientId, QString *ClientSecret);
    void showAuthorizationPage();
    void authenticationComplete();
    void authenticationError();
    void apiError();

    void timelineRequestComplete(QJsonArray statuses);

    void clientNameChanged();
    void instanceURLChanged();
    void clientWebsiteChanged();
    void clientScopesChanged();
    void clientTokenChanged();
    void clientIdChanged();
    void clientSecretChanged();
    void refreshTokenChanged();
    void refreshTokenExpireChanged();

public:
    mastodon();

    MastodonAccount *getAccount(QString id);
    MastodonAccount *getCurrentAccount();

    Q_INVOKABLE void getClientTokens();
    Q_INVOKABLE QUrl getAuthRequestUrl();
    Q_INVOKABLE void getAccessToken();
    Q_INVOKABLE void getAccessToken(QString auth_code);

    Q_INVOKABLE void timeline(QString timeline, int limit);

private:
    QString m_ClientName;
    QString m_ClientWebsite;
    QString m_ClientScopes;
    QString m_InstanceUrl;

    QString m_ClientId;
    QString m_ClientSecret;
    QString m_ClientToken;
    QString m_RefreshToken;
    QDateTime m_RefreshTokenExpire;

    QNetworkReply * tokenReply;
    QNetworkReply * timelineReply;

    QNetworkRequest buildApiCall(QString method, QString endpoint, QUrlQuery params);
};

#endif // MASTODON_H
