#ifndef MASTODONACCOUNT_H
#define MASTODONACCOUNT_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QJsonObject>

class MastodonAccount : public QObject
{
    Q_OBJECT
public:
    explicit MastodonAccount(QObject *parent = 0);
    MastodonAccount(QJsonObject data);

    Q_PROPERTY(QString Id MEMBER m_Id NOTIFY IdChanged)
    Q_PROPERTY(QString username MEMBER m_Username NOTIFY UsernameChanged)
    Q_PROPERTY(QString acct MEMBER m_Acct NOTIFY AcctChanged)
    Q_PROPERTY(QString displayName MEMBER m_DisplayName NOTIFY DisplayNameChanged)
    Q_PROPERTY(bool isLocked MEMBER m_IsLocked NOTIFY IsLockedChanged)
    Q_PROPERTY(QString createdAt MEMBER m_CreatedAt NOTIFY CreatedAtChanged)
    Q_PROPERTY(int followersCount MEMBER m_FollowersCount NOTIFY FollowersCountChanged)
    Q_PROPERTY(int followingCount MEMBER m_FollowingCount NOTIFY FollowingCountChanged)
    Q_PROPERTY(int statusesCount MEMBER m_StatusesCount NOTIFY StatusesCountChanged)
    Q_PROPERTY(QString note MEMBER m_Note NOTIFY NoteChanged)
    Q_PROPERTY(QUrl url MEMBER m_Url NOTIFY UrlChanged)
    Q_PROPERTY(QUrl avatar MEMBER m_Avatar NOTIFY AvatarChanged)
    Q_PROPERTY(QUrl avatarStatic MEMBER m_AvatarStatic NOTIFY AvatarStaticChanged)
    Q_PROPERTY(QUrl header MEMBER m_Header NOTIFY HeaderChanged)
    Q_PROPERTY(QUrl headerStatic MEMBER m_HeaderStatic NOTIFY HeaderStaticChanged)

signals:
    void IdChanged();
    void UsernameChanged();
    void AcctChanged();
    void DisplayNameChanged();
    void IsLockedChanged();
    void CreatedAtChanged();
    void FollowersCountChanged();
    void FollowingCountChanged();
    void StatusesCountChanged();
    void NoteChanged();
    void UrlChanged();
    void AvatarChanged();
    void AvatarStaticChanged();
    void HeaderChanged();
    void HeaderStaticChanged();

public slots:

private:
    QString m_Id;
    QString m_Username;
    QString m_Acct;
    QString m_DisplayName;
    bool m_IsLocked;
    QString m_CreatedAt;
    int m_FollowersCount;
    int m_FollowingCount;
    int m_StatusesCount;
    QString m_Note;
    QUrl m_Url;
    QUrl m_Avatar;
    QUrl m_AvatarStatic;
    QUrl m_Header;
    QUrl m_HeaderStatic;
};

#endif // MASTODONACCOUNT_H
