#ifndef SCREENSHOTGUN_SETTINGS_H
#define SCREENSHOTGUN_SETTINGS_H

#include <QSettings>

enum class UploadService {
    SERVER,
    DROPBOX,
    YANDEX,
    GOOGLE
};

class Settings {
public:
    Settings();
    bool exists() const;
    void create();

    bool autostartup() const;
    UploadService service() const;
    QString serverUrl() const;
    QString dropboxToken() const;
    QString yandexToken() const;
    QString googleToken() const;
    QString googleRefreshToken() const;
    QString googleFolderId() const;

    void setAutostartup(const bool);
    void setService(const UploadService);
    void setServerUrl(const QString&);
    void setDropboxToken(const QString&);
    void setYandexToken(const QString&);
    void setGoogleToken(const QString&);
    void setGoogleRefreshToken(const QString&);
    void setGoogleFolderId(const QString&);

private:
    QSettings settings_;
};

#endif // SCREENSHOTGUN_SETTINGS_H
