#include "const.h"
#include "editorview.h"
#include "newversion.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QWindow>
#include <QClipboard>

#ifdef Q_OS_LINUX
#include "qxtglobalshortcut.h"
#endif

EditorView::EditorView() :
    QGraphicsView(),
    _scene(new QGraphicsScene(this)),
    _editorForm(NULL),
    _trayIcon(new TrayIcon(this)),
    _settings(new Settings(this)),
    _server(new Server(this))
{
    connect(_settings, SIGNAL(valid()),
            this, SLOT(checkVersion()));

    connect(_server, SIGNAL(serverVersion(QString)),
            this, SLOT(serverVersion(QString)));

    connect(_server, SIGNAL(connectionError()),
            this, SLOT(connectionError()));

    connect(_server, SIGNAL(screenshotUrl(QString)),
            this, SLOT(uploaded(QString)));

    connect(_server, SIGNAL(uploadError()),
            this, SLOT(uploadError()));

#ifdef Q_OS_LINUX
    // isValid will send signal `valid'
    if (!_settings->isValid()) {
        _settings->show();
    }

    _trayIcon->show();
#endif
}

EditorView::~EditorView()
{
}

void EditorView::init()
{
    disconnect(_settings, SIGNAL(valid()),
               this, SLOT(checkVersion()));

    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    setScene(_scene);

    connect(_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));

    QxtGlobalShortcut *shortcut = new QxtGlobalShortcut(this);
    shortcut->setShortcut(QKeySequence(Qt::ALT + Qt::Key_Print));

    connect(shortcut, SIGNAL(activated()),
            this, SLOT(run()));
}

QGraphicsScene* EditorView::scene()
{
    return _scene;
}

Settings* EditorView::settings()
{
    return _settings;
}

Server* EditorView::server()
{
    return _server;
}

void EditorView::mousePressEvent(QMouseEvent *e)
{
    _editorForm->mode()->init(e->x(), e->y());
}

void EditorView::mouseMoveEvent(QMouseEvent *e)
{
    _editorForm->mode()->move(e->x(), e->y());
}

void EditorView::mouseReleaseEvent(QMouseEvent *e)
{
    _editorForm->mode()->stop(e->x(), e->y());
}

void EditorView::wheelEvent(QWheelEvent *e)
{
    if (e->delta() < 0) {
        _editorForm->setSelectedNext();
    } else {
        _editorForm->setSelectedPrevious();
    }
}

void EditorView::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() != Qt::Key_Escape) {
        return;
    }

    hide();
    _editorForm->hide();
}

void EditorView::trayActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        run();
    }
}

void EditorView::run()
{
    // Making screenshot
    QDesktopWidget *desktop = QApplication::desktop();
    QRect geo = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));

    _screenshot = QGuiApplication::primaryScreen()->grabWindow(
                desktop->winId(), geo.left(), geo.top(), geo.width(), geo.height());

    int width = _screenshot.width(),
        height = _screenshot.height();

    setGeometry(0, 0, width, height);
    _scene->clear();
    _scene->setSceneRect(0, 0, width, height);

    // Background screenshot
    _scene->addPixmap(_screenshot);
    _editorForm = new EditorForm(this);
    showFullScreen();
}

void EditorView::checkVersion()
{
    _server->setUrl(_settings->server());
    _server->version();
}

void EditorView::serverVersion(QString version)
{
    _settings->setError("")->hide();

    if (VERSION != version) {
        _newVersion = new NewVersion(this, _server);
        _newVersion->show();
    }

    init();
}

void EditorView::connectionError()
{
    _settings->setError(QString("Can't connect to server"))->show();
}

void EditorView::uploaded(QString url)
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(url);

    _trayIcon->showMessage("Link copied to clipboard",
                           url,
                           QSystemTrayIcon::Information,
                           3000);
}

void EditorView::uploadError()
{
    _trayIcon->showMessage("Error while uploading screenshot",
                           "Check your server logs",
                           QSystemTrayIcon::Critical,
                           10000);
}
