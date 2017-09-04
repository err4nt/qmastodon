#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QDebug>

#include "mastodon.h"
#include "mastodonstatus.h"


mastodon::mastodon()
{
    manager = new QNetworkAccessManager();
}

void mastodon::TokenRequestFinished()
{
    if(tokenReply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Request resulted in error: " << tokenReply->errorString();
    }
    qDebug("Result code: %d" , tokenReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt());

    QJsonObject replyJSON = QJsonDocument::fromJson(tokenReply->readAll()).object();
    tokenReply->deleteLater();

    m_ClientId = QString(replyJSON["client_id"].toString());
    m_ClientSecret = QString(replyJSON["client_secret"].toString());

    emit showAuthorizationPage();
}

void mastodon::AccessTokenRequestFinished()
{
    if(tokenReply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Request resulted in error: " << tokenReply->errorString();
        emit authenticationError();
    }
    qDebug("Result code: %d" , tokenReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt());

    QJsonObject replyJSON = QJsonDocument::fromJson(tokenReply->readAll()).object();
    tokenReply->deleteLater();

    m_ClientToken = QString(replyJSON["access_token"].toString());
    m_RefreshToken = QString(replyJSON["refresh_token"].toString());
    int tokenExpiresIn = QString(replyJSON["expires_in"].toString()).toInt();

    m_RefreshTokenExpire = QDateTime::currentDateTimeUtc().addSecs(tokenExpiresIn);

    emit authenticationComplete();
}

void mastodon::TimelineRequestFinished()
{
    if(timelineReply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Request resulted in error: " << timelineReply->errorString();
        emit apiError();
    }
    qDebug("Result code: %d" , timelineReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt());

    QJsonArray replyJSON = QJsonDocument::fromJson(timelineReply->readAll()).array();
/*    QJsonArray::iterator i;
    QList<MastodonStatus *> statuses;
    for(i = replyJSON.begin(); i != replyJSON.end(); i++)
    {
        statuses.push_back(new MastodonStatus(((QJsonValueRef)*i).toObject()));
    }*/

    //tokenReply->deleteLater();

    emit timelineRequestComplete(replyJSON);
}


void mastodon::getClientTokens()
{
    QUrl qrl(m_InstanceUrl);
    qrl.setPath("/api/v1/apps/");

    qDebug() << qrl.toString();

    QUrlQuery postData;
    postData.addQueryItem("client_name", m_ClientName);
    postData.addQueryItem("scopes", m_ClientScopes);
    postData.addQueryItem("redirect_uris", "urn:ietf:wg:oauth:2.0:oob");

    QNetworkRequest request(qrl);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    tokenReply = manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

    connect(tokenReply, SIGNAL(finished()), this, SLOT(TokenRequestFinished()));
}

void mastodon::getAccessToken()
{
    QUrl qrl(m_InstanceUrl);
    qrl.setPath("/oauth/token");

    QUrlQuery params;
    params.addQueryItem("grant_type", "refresh_token");
    params.addQueryItem("refresh_token", m_RefreshToken);
    params.addQueryItem("client_id", m_ClientId);
    params.addQueryItem("client_secret", m_ClientSecret);
    params.addQueryItem("scope", m_ClientScopes);
    params.addQueryItem("redirect_uri", "urn:ietf:wg:oauth:2.0:oob");

    QNetworkRequest request(qrl);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    tokenReply = manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());

    connect(tokenReply, SIGNAL(finished()), this, SLOT(AccessTokenRequestFinished()));
}

void mastodon::getAccessToken(QString auth_code)
{
    QUrl qrl(m_InstanceUrl);
    qrl.setPath("/oauth/token");

    QUrlQuery params;
    params.addQueryItem("grant_type", "authorization_code");
    params.addQueryItem("code", auth_code);
    params.addQueryItem("client_id", m_ClientId);
    params.addQueryItem("client_secret", m_ClientSecret);
    params.addQueryItem("redirect_uri", "urn:ietf:wg:oauth:2.0:oob");

    QNetworkRequest request(qrl);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    tokenReply = manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());

    connect(tokenReply, SIGNAL(finished()), this, SLOT(AccessTokenRequestFinished()));
}

QUrl mastodon::getAuthRequestUrl()
{
    QString urlString = QString("%1/oauth/authorize?").arg(m_InstanceUrl);

    QUrlQuery params;
    params.addQueryItem("client_id", m_ClientId);
    params.addQueryItem("response_type", "code");
    params.addQueryItem("redirect_uri", "urn:ietf:wg:oauth:2.0:oob");
    params.addQueryItem("scope", m_ClientScopes);

    urlString.append(params.toString(QUrl::FullyEncoded).toUtf8());

    return QUrl(urlString);
}

QNetworkRequest mastodon::buildApiCall(QString method, QString endpoint, QUrlQuery params)
{
    QUrl qrl(m_InstanceUrl);
    qrl.setPath(endpoint);

    QNetworkRequest req(qrl);
    req.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer ").append(m_ClientToken.toUtf8()));
    req.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    if(method == "POST")
    {
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    }
    else if(method == "GET")
    {
        qrl.setPath(QString("%1?").arg(qrl.path()).append(params.toString(QUrl::FullyEncoded).toUtf8()));
    }

    return req;
}

void mastodon::timeline(QString timeline, int limit = 20)
{
    QUrlQuery params;

    params.addQueryItem("limit", QString(limit));

    QNetworkRequest timelineReq = buildApiCall("GET", QString("/api/v1/timelines/%1").arg(timeline), params);
    timelineReply = manager->get(timelineReq);

    connect(timelineReply, SIGNAL(finished()), this, SLOT(TimelineRequestFinished()));
}
