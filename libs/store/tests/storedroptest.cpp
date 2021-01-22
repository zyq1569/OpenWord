/* This file is part of the KDE project
 *  Copyright (C) 2004 David Faure <faure@kde.org>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */
#include <KoStore.h>

#include <QStringList>
#include <QBuffer>
#include <QMimeData>
#include <QClipboard>
#include <QTextBrowser>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QKeyEvent>
#include <QDropEvent>
#include <QApplication>
#include <QCommandLineParser>

class StoreDropTest : public QTextBrowser
{
Q_OBJECT
public:
    StoreDropTest(QWidget* parent);
protected:
    virtual void contentsDragEnterEvent(QDragEnterEvent * e);
    virtual void contentsDragMoveEvent(QDragMoveEvent * e);
    virtual void contentsDropEvent(QDropEvent * e);
    void keyPressEvent(QKeyEvent * e) override;
    virtual void paste();
private:
    bool processMimeData(const QMimeData* mimeData);
    void showZipContents(QByteArray data, const QString &mimeType, bool oasis);
    QString loadTextFile(KoStore* store, const QString& fileName);
};

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    StoreDropTest* window = new StoreDropTest(0);
    window->resize(500, 500);
    window->show();

    QObject::connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));
    return app.exec();
}

StoreDropTest::StoreDropTest(QWidget* parent)
        : QTextBrowser(parent)
{
    setText("KoStore drop/paste test\nDrop or paste a selection from a Calligra application into this widget to see the ZIP contents");
    setAcceptDrops(true);
}

void StoreDropTest::contentsDragEnterEvent(QDragEnterEvent * ev)
{
    ev->acceptProposedAction();
}

void StoreDropTest::contentsDragMoveEvent(QDragMoveEvent * ev)
{
    ev->acceptProposedAction();
}

void StoreDropTest::keyPressEvent(QKeyEvent * e)
{
    if (((e->modifiers() & Qt::ShiftModifier) && e->key() == Qt::Key_Insert) ||
            ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_V))
        paste();
    //else
    //    QTextBrowser::keyPressEvent( e );
}

void StoreDropTest::paste()
{
    qDebug("paste");
    const QMimeData* m = QApplication::clipboard()->mimeData();
    if (!m)
        return;

    const QString acceptMimeType("application/vnd.oasis.opendocument.");
    QStringList formats = m->formats();
    foreach(QString fmt, formats) {
        bool oasis = fmt.startsWith(acceptMimeType);
        if (oasis || fmt == "application/x-kpresenter") {
            QByteArray data = m->data(fmt);
            showZipContents(data, fmt.toLatin1(), oasis);
            return;
        }
    }
    setText("No acceptable format found. All I got was:\n" + formats.join("\n"));

}

void StoreDropTest::contentsDropEvent(QDropEvent *ev)
{
    if (processMimeData(ev->mimeData()))
        ev->acceptProposedAction();
    else
        ev->ignore();
}

bool StoreDropTest::processMimeData(const QMimeData* mimeData)
{
    const QString acceptMimeType("application/vnd.oasis.opendocument.");
    foreach (const QString &format, mimeData->formats()) {
        bool oasis = format.startsWith(acceptMimeType);
        if (oasis || format == "application/x-kpresenter") {
            const QByteArray data = mimeData->data(format);
            showZipContents(data, format, oasis);
            return true;
        }
    }
    setText("No acceptable format found. All I got was:\n" + mimeData->formats().join("\n"));
    return false;
}

void StoreDropTest::showZipContents(QByteArray data, const QString &mimeType, bool oasis)
{
    if (data.isEmpty()) {
        setText("No data!");
        return;
    }
    QBuffer buffer(&data);
    KoStore * store = KoStore::createStore(&buffer, KoStore::Read);
    if (store->bad()) {
        setText("Invalid ZIP!");
	delete store;
        return;
    }
    

    QString txt = QString("Valid ZIP file found for format ") + mimeType + "\n";

    if (oasis) {
        txt += loadTextFile(store, "content.xml");
        txt += loadTextFile(store, "styles.xml");
        txt += loadTextFile(store, "settings.xml");
        txt += loadTextFile(store, "META-INF/manifest.xml");
    } else {
        txt += loadTextFile(store, "maindoc.xml");
    }
    setText(txt);
    delete store;
}

QString StoreDropTest::loadTextFile(KoStore* store, const QString& fileName)
{
    if (!store->open(fileName))
        return QString("%1 not found\n").arg(fileName);

    QByteArray data = store->device()->readAll();
    store->close();
    QString txt = QString("Found %1: \n").arg(fileName);
    txt += QString::fromUtf8(data.data(), data.size());
    txt += "\n";
    return txt;
}
#include "storedroptest.moc"
