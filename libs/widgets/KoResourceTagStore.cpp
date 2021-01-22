 /*  This file is part of the KDE project

    Copyright (c) 2011 Sven Langkamp <sven.langkamp@gmail.com>
    Copyright (C) 2011 Srikanth Tiyyagura <srikanth.tulasiram@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "KoResourceTagStore.h"

#include <QDebug>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDomDocument>

#include <KoResourceServer.h>


class Q_DECL_HIDDEN KoResourceTagStore::Private
{
public:
    QMultiHash<QByteArray, QString> md5ToTag;
    QMultiHash<QString, QString> identifierToTag;

    QHash<QString, int> tagList;

    KoResourceServerBase *resourceServer;
};

KoResourceTagStore::KoResourceTagStore(KoResourceServerBase *resourceServer)
    : d(new Private)
{
    d->resourceServer = resourceServer;
}

KoResourceTagStore::~KoResourceTagStore()
{
    serializeTags();
    delete d;
}

QStringList KoResourceTagStore::assignedTagsList(const KoResource* resource) const
{
    if (!resource) return QStringList();

    QStringList tags = d->md5ToTag.values(resource->md5());
    tags += d->identifierToTag.values(resource->filename());
    tags.removeDuplicates();
    return tags;
}

void KoResourceTagStore::removeResource(const KoResource *resource)
{
    QStringList tags = assignedTagsList(resource);

    d->md5ToTag.remove(resource->md5());
    d->identifierToTag.remove(resource->filename());

    foreach(const QString &tag, tags) {
        if (d->tagList.contains(tag)) {
            if (d->tagList[tag] > 0) {
                d->tagList[tag]--;
            }
        }
    }
}

QStringList KoResourceTagStore::tagNamesList() const
{
    return d->tagList.uniqueKeys();
}

void KoResourceTagStore::addTag(KoResource* resource, const QString& tag)
{
    if (!resource) {
        d->tagList.insert(tag, 0);
        return;
    }

    bool added = false;

    if (!d->md5ToTag.contains(resource->md5(), tag)) {
        added = true;
        d->md5ToTag.insert(resource->md5(), tag);
    }

    if (!d->identifierToTag.contains(resource->filename())) {
        added = true;
        d->identifierToTag.insert(resource->filename(), tag);
    }

    if (added) {
        if (d->tagList.contains(tag)) {
            d->tagList[tag]++;
        }
        else {
            d->tagList.insert(tag, 1);
        }
    }
}

void KoResourceTagStore::delTag(KoResource* resource, const QString& tag)
{
    int res = d->md5ToTag.remove(resource->md5(), tag);
    res += d->identifierToTag.remove(resource->filename(), tag);

    if (res > 0) { // decrease the usecount for this tag
        if (d->tagList.contains(tag)) {
            if (d->tagList[tag] > 0) {
                d->tagList[tag]--;
            }
        }
    }
}

void KoResourceTagStore::delTag(const QString& tag)
{
    foreach(const QByteArray &res, d->md5ToTag.keys(tag)) {
        d->md5ToTag.remove(res, tag);
    }
    foreach(const QString &identifier, d->identifierToTag.keys(tag)) {
        d->identifierToTag.remove(identifier, tag);
    }

    Q_ASSERT(!d->md5ToTag.values().contains(tag));
    Q_ASSERT(!d->identifierToTag.values().contains(tag));
    d->tagList.remove(tag);
}

QStringList KoResourceTagStore::searchTag(const QString& query) const
{
    QStringList tagsList = query.split(QRegExp("[,]\\s*"), QString::SkipEmptyParts);
    if (tagsList.isEmpty()) {
        return QStringList();
    }

    QSet<const KoResource*> resources;

    foreach (QString tag, tagsList) {
        foreach(const QByteArray &md5, d->md5ToTag.keys(tag)) {
            KoResource *res = d->resourceServer->byMd5(md5);
            if (res)
                resources << res;
        }
        foreach(const QString &identifier, d->identifierToTag.keys(tag)) {
            KoResource *res = d->resourceServer->byFileName(identifier);
            if (res)
                resources << res;
        }
    }

    QStringList filenames;
    foreach (const KoResource *res, resources) {
        if (res) {
            filenames << adjustedFileName(res->shortFilename());
        }
    }

    return removeAdjustedFileNames(filenames);
}

void KoResourceTagStore::loadTags()
{
    QStringList tagFiles = QStandardPaths::locateAll(QStandardPaths::AppDataLocation, "tags/" + d->resourceServer->type() + "_tags.xml");
    foreach(const QString &tagFile, tagFiles) {
        readXMLFile(tagFile);
    }
}

void KoResourceTagStore::writeXMLFile(const QString &tagstore)
{
    QDir().mkpath(QFileInfo(tagstore).path());
    QFile f(tagstore);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        warnWidgets << "Cannot write meta information to '" << tagstore << "'.";
        return;
    }
    QDomDocument doc;
    QDomElement root;

    QDomDocument docTemp("tags");
    doc = docTemp;
    doc.appendChild(doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\""));
    root = doc.createElement("tags");
    doc.appendChild(root);

    QSet<KoResource*> taggedResources;
    foreach (const QByteArray &md5, d->md5ToTag.keys()) {
        KoResource *res = d->resourceServer->byMd5(md5);
        if (res) {
            taggedResources << res;
        }
    }

    foreach (const QString &identifier, d->identifierToTag.keys()) {
        KoResource *res = d->resourceServer->byFileName(identifier);
        if (res) {
            taggedResources << res;
        }
    }

    foreach (const KoResource *res, taggedResources) {

        QDomElement resourceEl = doc.createElement("resource");
        resourceEl.setAttribute("identifier", res->filename().replace(QDir::homePath(), QString("~")));
        resourceEl.setAttribute("md5", QString(res->md5().toBase64()));

        foreach (const QString &tag, assignedTagsList(res)) {
            QDomElement tagEl = doc.createElement("tag");
            tagEl.appendChild(doc.createTextNode(tag));
            resourceEl.appendChild(tagEl);
        }
        root.appendChild(resourceEl);

    }

    // Now write empty tags
    foreach (const QString &tag, d->tagList.uniqueKeys())  {
        if (d->tagList[tag] == 0) {
            QDomElement resourceEl = doc.createElement("resource");
            resourceEl.setAttribute("identifier", "dummy");
            QDomElement tagEl = doc.createElement("tag");
            tagEl.appendChild(doc.createTextNode(tag));
            resourceEl.appendChild(tagEl);
            root.appendChild(resourceEl);
        }
    }

    QTextStream metastream(&f);
    metastream << doc.toString();

    f.close();

}

void KoResourceTagStore::readXMLFile(const QString &tagstore)
{
    QString inputFile;

    if (QFile::exists(tagstore)) {
        inputFile = tagstore;
    } else {
        inputFile = QStandardPaths::locate(QStandardPaths::AppDataLocation, "tags.xml");
    }

    QFile f(inputFile);
    if (!f.open(QIODevice::ReadOnly)) {
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&f)) {
        warnWidgets << "The file could not be parsed.";
        return;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != "tags") {
        warnWidgets << "The file doesn't seem to be of interest.";
        return;
    }

    QDomNodeList resourceNodesList = root.childNodes();

    for (int i = 0; i < resourceNodesList.count(); i++) {

        QByteArray resourceMD5;
        QString identifier;

        QDomElement element = resourceNodesList.at(i).toElement();
        if (element.tagName() == "resource") {

            KoResource *resByMd5 = 0;
            KoResource *resByFileName = 0;

            if (element.hasAttribute("md5")) {
                resourceMD5 = QByteArray::fromBase64(element.attribute("md5").toLatin1());
                resByMd5 = d->resourceServer->byMd5(resourceMD5);
            }

            if (element.hasAttribute("identifier")) {
                identifier = element.attribute("identifier");
                QFileInfo fi(identifier);
                resByFileName = d->resourceServer->byFileName(fi.fileName());
            }

            if (identifier == "dummy" || isServerResource(identifier)) {

                QDomNodeList tagNodesList = resourceNodesList.at(i).childNodes();

                for (int j = 0; j < tagNodesList.count() ; j++) {

                    QDomElement tagEl = tagNodesList.at(j).toElement();

                    if (identifier != "dummy") {
                        QFileInfo fi(identifier);
                        KoResource *res = d->resourceServer->byFileName(fi.fileName());
                        addTag(res, tagEl.text());
                    }
                    else {
                        addTag(0, tagEl.text());
                    }
                    d->md5ToTag.insert(resourceMD5, tagEl.text());
                    d->identifierToTag.insert(identifier, tagEl.text());
                }
            }
            else {
                KoResource *res = 0;

                if (resByMd5 && resByFileName && (resByMd5 != resByFileName)) {
                    warnWidgets << "MD5sum and filename point to different resources -- was the resource renamed? We go with md5";
                    res = resByMd5;
                }
                else if (!resByMd5 && resByFileName) {
                    // We didn't find the resource by md5, but did find it by filename, so take that one
                    res = resByFileName;
                }
                else {
                    res = resByMd5;
                }

                QDomNodeList tagNodesList = resourceNodesList.at(i).childNodes();
                for (int j = 0; j < tagNodesList.count() ; j++) {
                    QDomElement tagEl = tagNodesList.at(j).toElement();

                    if (res) {
                        addTag(res, tagEl.text());
                    }
                    d->md5ToTag.insert(resourceMD5, tagEl.text());
                    d->identifierToTag.insert(identifier, tagEl.text());
                }
            }
        }
    }
}

bool KoResourceTagStore::isServerResource(const QString &resourceName) const
{
    bool removeChild = false;
    QStringList extensionsList = d->resourceServer->extensions().split(':');
    foreach (QString extension, extensionsList) {
        if (resourceName.contains(extension.remove('*'))) {
            removeChild = true;
            break;
        }
    }
    return removeChild;
}

QString KoResourceTagStore::adjustedFileName(const QString &fileName) const
{
    if (!isServerResource(fileName)) {
        return fileName + "-krita" + d->resourceServer->extensions().split(':').takeFirst().remove('*');
    }
    return fileName;
}

QStringList KoResourceTagStore::removeAdjustedFileNames(QStringList fileNamesList) const
{
    foreach (const QString & fileName, fileNamesList) {
        if (fileName.contains("-krita")) {
            fileNamesList.append(fileName.split("-krita").takeFirst());
            fileNamesList.removeAll(fileName);
        }
    }
    return fileNamesList;
}

void KoResourceTagStore::serializeTags()
{
    writeXMLFile(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/tags/" + d->resourceServer->type() + "_tags.xml");
}
