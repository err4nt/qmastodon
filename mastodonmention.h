#ifndef MASTODONMENTION_H
#define MASTODONMENTION_H

#include <QObject>
#include <QString>
#include <QUrl>

class MastodonMention : public QObject
{
    Q_OBJECT
public:
    explicit MastodonMention(QObject *parent = 0);

    Q_PROPERTY(QUrl Url MEMBER m_Url NOTIFY UrlChanged)
    Q_PROPERTY(QString Username MEMBER m_Username NOTIFY UsernameChanged)
    Q_PROPERTY(QString Acct MEMBER m_Acct NOTIFY AcctChanged)
    Q_PROPERTY(QString Id MEMBER m_Id NOTIFY IdChanged)

signals:
    void UrlChanged();
    void UsernameChanged();
    void AcctChanged();
    void IdChanged();

public slots:

private:
    QUrl m_Url;
    QString m_Username;
    QString m_Acct;
    QString m_Id;
};

#endif // MASTODONMENTION_H
