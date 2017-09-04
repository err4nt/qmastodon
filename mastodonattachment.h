#ifndef MASTODONATTACHMENT_H
#define MASTODONATTACHMENT_H

#include <QObject>
#include <QString>
#include <QUrl>

class MastodonAttachment : public QObject
{
    Q_OBJECT
public:
    explicit MastodonAttachment(QObject *parent = 0);

    Q_PROPERTY(QString Id MEMBER m_Id NOTIFY IdChanged)
    Q_PROPERTY(QString Type MEMBER m_Type NOTIFY TypeChanged)
    Q_PROPERTY(QUrl Url MEMBER m_Url NOTIFY UrlChanged)
    Q_PROPERTY(QUrl RemoteUrl MEMBER m_RemoteUrl NOTIFY RemoteUrlChanged)
    Q_PROPERTY(QUrl PreviewUrl MEMBER m_PreviewUrl NOTIFY PreviewUrlChanged)
    Q_PROPERTY(QUrl TextUrl	MEMBER m_TextUrl NOTIFY TextUrlChanged)

signals:
    void IdChanged();
    void TypeChanged();
    void UrlChanged();
    void RemoteUrlChanged();
    void PreviewUrlChanged();
    void TextUrlChanged();

private:
    QString m_Id;
    QString m_Type;
    QUrl m_Url;
    QUrl m_RemoteUrl;
    QUrl m_PreviewUrl;
    QUrl m_TextUrl;


public slots:
};

#endif // MASTODONATTACHMENT_H
