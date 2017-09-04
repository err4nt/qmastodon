#include "mastodonaccount.h"

MastodonAccount::MastodonAccount(QObject *parent) : QObject(parent)
{

}

MastodonAccount::MastodonAccount(QJsonObject data)
{
    m_Id = data["id"].toString();
    m_Username = data["username"].toString();
    m_Acct = data["acct"].toString();
    m_DisplayName = data["display_name"].toString();
    m_IsLocked = data["locked"].toBool();
    m_CreatedAt = data["created_at"].toString();
    m_FollowersCount = data["followers_count"].toInt();
    m_FollowingCount = data["following_count"].toInt();
    m_StatusesCount = data["statuses_count"].toInt();
    m_Note = data["note"].toString();
    m_Url = QUrl::fromUserInput(data["url"].toString());
    m_Avatar = QUrl::fromUserInput(data["avatar"].toString());
    m_AvatarStatic = QUrl::fromUserInput(data["avatar_static"].toString());
    m_Header = QUrl::fromUserInput(data["header"].toString());
    m_HeaderStatic = QUrl::fromUserInput(data["header_static"].toString());
}
