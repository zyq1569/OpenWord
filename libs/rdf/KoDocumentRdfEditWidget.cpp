/* This file is part of the KDE project
   Copyright (C) 2010 KO GmbH <ben.martin@kogmbh.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
*/

#include "KoDocumentRdfEditWidget.h"

#include <ui_KoDocumentRdfEditWidget.h>

#include "KoDocumentRdf.h"
#include "KoRdfSemanticItemRegistry.h"
#include "KoRdfPrefixMapping.h"
#include "KoSopranoTableModelDelegate.h"
#include "KoSopranoTableModel.h"
#include "KoRdfSemanticTreeWidgetItem.h"
// main
#include <KoDocument.h>
#include <KoIcon.h>
// KF5
#include <kdebug.h>
#include <kmenu.h>
#include <kmessagebox.h>
#include <klocalizedstring.h>
// Qt
#include <QComboBox>
#include <QPointer>
#include <QSortFilterProxyModel>


static const char SemanticItemClassId[] = "Ko_semanticItemClass";

/**
 * Helper class to maintain a single row in the namespace editing
 * widget. This allows prefixes to be edited and updates the internal
 * data structures accordingly.
 */
class KoRdfPrefixMappingTreeWidgetItem : public QTreeWidgetItem
{
    KoRdfPrefixMapping *m_mapping;
    QString m_key;
public:
    enum {
        ColKey = 0,
        ColValue = 1,
        ColSize
    };
    KoRdfPrefixMappingTreeWidgetItem(KoRdfPrefixMapping *mapping, const QString &key, int type = Type)
        : QTreeWidgetItem(type)
        , m_mapping(mapping)
        , m_key(key) {
        setFlags(QTreeWidgetItem::flags() | Qt::ItemIsEditable);
    }
    virtual void setData(int column, int role, const QVariant &value) {
        m_mapping->dump();
        kDebug(30015) << "m_key:" << m_key << " value:" << value;
        if (column == ColKey) {
            QString url = m_mapping->prefexToURI(m_key);
            m_mapping->remove(m_key);
            m_key = value.toString();
            m_mapping->insert(m_key, url);
        } else if (column == ColValue) {
            m_mapping->remove(m_key);
            m_mapping->insert(m_key, value.toString());
        }
        QTreeWidgetItem::setData(column, role, value);
    }
    virtual QVariant data(int column, int role) const {
        if (role != Qt::DisplayRole && role != Qt::EditRole) {
            return QVariant();
        }
        if (column == ColKey) {
            return m_key;
        } else if (column == ColValue) {
            QString url = m_mapping->prefexToURI(m_key);
            return url;
        }
        return QTreeWidgetItem::data(column, role);
    }
    void removeFromMapping() {
        m_mapping->remove(m_key);
    }
};

class KoDocumentRdfEditWidget::KoDocumentRdfEditWidgetPrivate
{
public:
    QWidget *m_widget;
    KoDocumentRdf *m_rdf;
    Ui::KoDocumentRdfEditWidget *m_ui;
    QHash<QString, QComboBox*> m_defaultStylesheetComboBoxMap;
    KoSopranoTableModel *m_tripleModel;
    KoSopranoTableModel *m_sparqlResultModel;
    QSortFilterProxyModel *m_tripleProxyModel;
    KoRdfSemanticTree m_semanticItemsTree;
    QList<hKoSemanticStylesheet> m_stylesheets;

    KoDocumentRdfEditWidgetPrivate(KoDocumentRdf *m_rdf)
        : m_rdf(m_rdf)
        , m_tripleProxyModel(0)
    {
        m_ui = new Ui::KoDocumentRdfEditWidget();
        m_widget = new QWidget();
        m_ui->setupUi(m_widget);
    }
    ~KoDocumentRdfEditWidgetPrivate() {
        delete m_ui;
    }

    void setupWidget()
    {
        // setup triple view page
        m_tripleModel = new KoSopranoTableModel(m_rdf);
        m_tripleProxyModel = new QSortFilterProxyModel(m_widget);
        m_tripleProxyModel->setSourceModel(m_tripleModel);
        m_ui->m_tripleView->setModel(m_tripleProxyModel);
        m_ui->m_tripleView->setSelectionBehavior(QAbstractItemView::SelectRows);
        m_ui->m_tripleView->hideColumn(KoSopranoTableModel::ColIsValid);
        m_ui->m_tripleView->hideColumn(KoSopranoTableModel::ColObjXsdType);
        m_ui->m_tripleView->horizontalHeader()->setResizeMode(KoSopranoTableModel::ColSubj, QHeaderView::Stretch);
        m_ui->m_tripleView->horizontalHeader()->setResizeMode(KoSopranoTableModel::ColPred, QHeaderView::Stretch);
        m_ui->m_tripleView->horizontalHeader()->setResizeMode(KoSopranoTableModel::ColObj,  QHeaderView::Stretch);
        m_ui->m_tripleView->horizontalHeader()->setResizeMode(KoSopranoTableModel::ColCtx,  QHeaderView::Stretch);
        m_ui->m_tripleView->setItemDelegate(new KoSopranoTableModelDelegate(m_tripleProxyModel));
        // setup namespace page
        QTreeWidget *v = m_ui->m_namespaceView;
        v->setColumnCount(KoRdfPrefixMappingTreeWidgetItem::ColSize);
        v->sortItems(KoRdfPrefixMappingTreeWidgetItem::ColValue, Qt::DescendingOrder);
        v->header()->setResizeMode(KoRdfPrefixMappingTreeWidgetItem::ColKey,
                                   QHeaderView::ResizeToContents);
        KoRdfPrefixMapping *mapping = m_rdf->prefixMapping();
        const QMap<QString,QString> &m = m_rdf->prefixMapping()->mappings();
        for (QMap<QString,QString>::const_iterator mi = m.begin(); mi != m.end(); ++mi) {
            KoRdfPrefixMappingTreeWidgetItem *item =
                    new KoRdfPrefixMappingTreeWidgetItem(mapping, mi.key());
            v->addTopLevelItem(item);
        }
        // setup semantic page
        v = m_ui->m_semanticView;
        m_semanticItemsTree = KoRdfSemanticTree::createTree(v);
        m_semanticItemsTree.update(m_rdf);
    }

    void buildComboBox(QComboBox *w, hKoRdfSemanticItem si) {
        if (!si) {
            return;
        }
        hKoSemanticStylesheet activeSheet = si->defaultStylesheet();
        int activeSheetIndex = 0;
        kDebug(30015) << "format(), activeSheet:" << activeSheet->name();

        foreach (hKoSemanticStylesheet ss, si->stylesheets()) {
            m_stylesheets << ss;
            QVariant ud = QVariant::fromValue(ss.data());
            w->addItem(ss->name(), ud);
            if (activeSheet->name() == ss->name()) {
                activeSheetIndex = w->count() - 1;
            }
        }
        foreach (hKoSemanticStylesheet ss, si->userStylesheets()) {
            m_stylesheets << ss;
            QVariant ud = QVariant::fromValue(ss.data());
            w->addItem(ss->name(), ud);
            if (activeSheet->name() == ss->name()) {
                activeSheetIndex = w->count() - 1;
            }
        }
        kDebug(30015) << "format(), active:" << activeSheetIndex;
        w->setCurrentIndex(activeSheetIndex);
    }

    void clearTriplesSelection() {
        m_ui->m_tripleView->selectionModel()->clear();
    }

    void selectTriples(int row) {
        m_ui->m_tripleView->selectRow(row);
    }

    void selectTriples(const QModelIndex &mi,
                       QItemSelectionModel::SelectionFlags command = QItemSelectionModel::Select) {
        m_ui->m_tripleView->selectionModel()->select(mi, command | QItemSelectionModel::Rows);
    }

    void selectTriples(const QModelIndexList &ml,
                       QItemSelectionModel::SelectionFlags command = QItemSelectionModel::Select) {
        Q_UNUSED(command);
        foreach (const QModelIndex &mi, ml) {
            selectTriples(mi);
        }
    }

    QModelIndexList mapFromSource(QModelIndexList mil) const {
        QModelIndexList ret;
        foreach (const QModelIndex &idx, mil) {
            QModelIndex pidx = m_tripleProxyModel->mapFromSource(idx);
            ret << pidx;
        }
        return ret;
    }

    QModelIndex mapFromSource(QModelIndex idx) const {
        QModelIndex pidx = m_tripleProxyModel->mapFromSource(idx);
        return pidx;
    }

    QModelIndex mapToSource(const QModelIndex proxyIndex) const {
        QModelIndex sidx = m_tripleProxyModel->mapToSource(proxyIndex);
        return sidx;
    }

    QModelIndexList mapToSource(const QModelIndexList proxyList) const {
        QModelIndexList ret;
        foreach (const QModelIndex &idx, proxyList) {
            QModelIndex sidx = m_tripleProxyModel->mapToSource(idx);
            ret << sidx;
        }
        return ret;
    }
};


KoDocumentRdfEditWidget::KoDocumentRdfEditWidget( KoDocumentRdf *docRdf)
    : d(new KoDocumentRdfEditWidgetPrivate(docRdf))
{
    d->setupWidget();

    // setup stylesheet UI
    const QString buttonText = i18n("Set For All Existing");
    QGridLayout *styleSheetsGridLayout = d->m_ui->m_styleSheetsGridLayout;
    int row = 0;
    foreach (const QString &semanticItemName, KoRdfSemanticItemRegistry::instance()->classNames()) {
        if (KoRdfSemanticItemRegistry::instance()->isBasic(semanticItemName)) {
            continue;
        }

        QLabel *semanticItemLabel =
            new QLabel(KoRdfSemanticItemRegistry::instance()->classDisplayName(semanticItemName));
        styleSheetsGridLayout->addWidget(semanticItemLabel, row, 0, Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        QComboBox *defaultStylesheetComboBox = new QComboBox;
        d->m_defaultStylesheetComboBoxMap.insert(semanticItemName, defaultStylesheetComboBox);
        styleSheetsGridLayout->addWidget(defaultStylesheetComboBox, row, 1);

        QPushButton *setStylesheetButton = new QPushButton(buttonText);
        setStylesheetButton->setProperty(SemanticItemClassId, semanticItemName);
        styleSheetsGridLayout->addWidget(setStylesheetButton, row, 2);
        connect(setStylesheetButton, SIGNAL(clicked()), SLOT(onDefaultSheetButtonClicked()));

	hKoRdfSemanticItem templateItem(static_cast<KoRdfSemanticItem *>(
	    docRdf->createSemanticItem(semanticItemName, this).data()));
        d->buildComboBox(defaultStylesheetComboBox, templateItem);

        ++row;
    }
    QPushButton *setAllStylesheetsButton = new QPushButton(buttonText);
    // no semantic item plugins installed?
    if (row == 0) {
        setAllStylesheetsButton->setEnabled(false);
    }
    styleSheetsGridLayout->addWidget(setAllStylesheetsButton, row, 2);
    connect(setAllStylesheetsButton, SIGNAL(clicked()), SLOT(onDefaultAllSheetButtonClicked()));


    connect(d->m_ui->newTripleButton, SIGNAL(clicked()), this, SLOT(addTriple()));
    connect(d->m_ui->copyTripleButton, SIGNAL(clicked()), this, SLOT(copyTriples()));
    connect(d->m_ui->deleteTripleButton, SIGNAL(clicked()), this, SLOT(deleteTriples()));
    connect(d->m_ui->newNamespaceButton, SIGNAL(clicked()), this, SLOT(addNamespace()));
    connect(d->m_ui->deleteNamespaceButton, SIGNAL(clicked()), this, SLOT(deleteNamespace()));
    d->m_ui->m_semanticView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(d->m_ui->m_semanticView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showSemanticViewContextMenu(QPoint)));
    connect(d->m_ui->m_sparqlExecute, SIGNAL(clicked()), this, SLOT(sparqlExecute()));

    connect(docRdf, SIGNAL(semanticObjectUpdated(hKoRdfBasicSemanticItem)),
            this, SLOT(semanticObjectUpdated(hKoRdfBasicSemanticItem)));
}

KoDocumentRdfEditWidget::~KoDocumentRdfEditWidget()
{
    delete d;
}


QWidget* KoDocumentRdfEditWidget::widget()
{
    return d->m_widget;
}

bool KoDocumentRdfEditWidget::shouldDialogCloseBeVetoed()
{
    bool ret = false;
    if (int invalidCount = d->m_tripleModel->invalidStatementCount()) {
        kDebug(30015) << "invalidCount:" << invalidCount;
        int dialogRet = KMessageBox::warningContinueCancel(
                    this, i18ncp("statement is an Rdf related term",
                                 "<qt>Edits will be lost.<p>There is %1 invalid statement left.</qt>",
                                 "<qt>Edits will be lost.<p>There are %1 invalid statements left.</qt>",
                                 invalidCount),
                    i18nc("statement is an Rdf related term", "Discard invalid statements?"),
                    KStandardGuiItem::cont(),
                    KStandardGuiItem::cancel(),
                    "InvalidTriplesInDocInfoDialog");
        if (dialogRet == KMessageBox::Cancel) {
            ret = true;
            QModelIndexList invalidList = d->m_tripleModel->invalidStatementList();
            if (!invalidList.isEmpty()) {
                d->m_ui->m_tripleView->selectionModel()->clear();
                foreach (QModelIndex idx, invalidList) {
                    QModelIndex pidx = d->mapFromSource(idx);
                    d->m_ui->m_tripleView->selectionModel()->select(
                                pidx, QItemSelectionModel::Select);
                }

                QModelIndex pidx = d->mapFromSource(invalidList.first());
                d->m_ui->m_tripleView->scrollTo(pidx);
            }
        }
        kDebug(30015) << "dialogRet:" << dialogRet << " ret:" << ret;
    }
    return ret;
}

void KoDocumentRdfEditWidget::apply()
{
    KoDocumentRdf *rdf = d->m_rdf;

    QHash<QString, QComboBox*>::ConstIterator it = d->m_defaultStylesheetComboBoxMap.constBegin();
    QHash<QString, QComboBox*>::ConstIterator end = d->m_defaultStylesheetComboBoxMap.constEnd();
    for( ; it != end; ++it) {
        const QString &semanticClass = it.key();
        QComboBox *comboBox = it.value();
	hKoRdfSemanticItem si(static_cast<KoRdfSemanticItem *>(
	    rdf->createSemanticItem(semanticClass).data()));
        si->defaultStylesheet(stylesheetFromComboBox(comboBox));
    }
}

QString KoDocumentRdfEditWidget::name() const
{
    return i18n("Rdf");
}

QString KoDocumentRdfEditWidget::iconName() const
{
    return koIconName("text-rdf");
}

void KoDocumentRdfEditWidget::semanticObjectUpdated(hKoRdfBasicSemanticItem item)
{
    Q_UNUSED(item);
    kDebug(30015) << "updating the sem item list view";
    d->m_semanticItemsTree.update(d->m_rdf);
}

void KoDocumentRdfEditWidget::showSemanticViewContextMenu(const QPoint &position)
{
    QPointer<KMenu> menu = new KMenu(0);
    QList<QAction*> actions;
    if (QTreeWidgetItem *baseitem = d->m_ui->m_semanticView->itemAt(position)) {
        if (KoRdfSemanticTreeWidgetItem *item = dynamic_cast<KoRdfSemanticTreeWidgetItem*>(baseitem)) {
            actions = item->actions(menu);
        }
    }
    if (actions.count() > 0) {
        foreach (QAction *a, actions) {
            menu->addAction(a);
        }
        menu->exec(d->m_ui->m_semanticView->mapToGlobal(position));
    }
    delete menu;
}

void KoDocumentRdfEditWidget::addTriple()
{
    KoDocumentRdf *m_rdf = d->m_rdf;
    //
    // We have to make sure the new triple is unique, so the object
    // is set to a bnode value. Because the user most likely doesn't
    // want to create a bnode, we change it to a URI first.
    //
    Soprano::Node obj(QUrl(m_rdf->model()->createBlankNode().toString()));
    Soprano::Statement st(Soprano::Node(QUrl("http://calligra.org/new-node")),
                          Soprano::Node(QUrl("http://calligra.org/new-node")),
                          obj,
                          m_rdf->manifestRdfNode());
    int newRowNumber = d->m_tripleModel->insertStatement(st);
    QModelIndex pidx = d->mapFromSource(d->m_tripleModel->index(newRowNumber, 0));
    // select newrow
    d->clearTriplesSelection();
    d->selectTriples(pidx.row());
    d->m_ui->m_tripleView->scrollTo(pidx);
}

void KoDocumentRdfEditWidget::copyTriples()
{
    QModelIndexList col = d->m_ui->m_tripleView->selectionModel()->selectedRows();
    QModelIndexList newRowsBackend = d->m_tripleModel->copyTriples(d->mapToSource(col));
    QModelIndexList newRows = d->mapFromSource(newRowsBackend);
    d->clearTriplesSelection();
    d->selectTriples(newRows);
    if (!newRows.isEmpty()) {
        d->m_ui->m_tripleView->scrollTo(newRows.first());
    }
}

void KoDocumentRdfEditWidget::deleteTriples()
{
    QModelIndexList col = d->m_ui->m_tripleView->selectionModel()->selectedRows();
    d->m_tripleModel->deleteTriples(d->mapToSource(col));
}

void KoDocumentRdfEditWidget::addNamespace()
{
    KoDocumentRdf *m_rdf = d->m_rdf;
    QTreeWidget *v = d->m_ui->m_namespaceView;
    QString key = QString("newnamespace%1").arg(QDateTime::currentDateTime().toTime_t());
    QString value = "http://www.example.com/fixme#";
    KoRdfPrefixMapping *mapping = m_rdf->prefixMapping();
    mapping->insert(key, value);
    kDebug(30015) << "adding key:" << key << " value:" << value;
    KoRdfPrefixMappingTreeWidgetItem* item =
            new KoRdfPrefixMappingTreeWidgetItem(mapping, key);
    v->addTopLevelItem(item);
    v->setCurrentItem(item);
    v->editItem(item);
}

void KoDocumentRdfEditWidget::deleteNamespace()
{
    QTreeWidget *v = d->m_ui->m_namespaceView;
    QList<QTreeWidgetItem *> sel = v->selectedItems();
    kDebug(30015) << "selection.sz:" << sel.size();
    foreach (QTreeWidgetItem *item, sel) {
        if (KoRdfPrefixMappingTreeWidgetItem *ritem
                = dynamic_cast<KoRdfPrefixMappingTreeWidgetItem *>(item)) {
            ritem->removeFromMapping();
        }
        v->invisibleRootItem()->removeChild(item);
    }
}

void KoDocumentRdfEditWidget::sparqlExecute()
{
    d->m_ui->m_sparqlResultView->selectionModel()->clear();
    QString sparql = d->m_ui->m_sparqlQuery->toPlainText();
    QSharedPointer<Soprano::Model> m = d->m_rdf->model();
    kDebug(30015) << "running SPARQL query:" << sparql;
    Soprano::QueryResultIterator qrIter =
            m->executeQuery(sparql, Soprano::Query::QueryLanguageSparql);
    QList<Soprano::BindingSet> bindings = qrIter.allBindings();
    QTableWidget *tableWidget = d->m_ui->m_sparqlResultView;
    tableWidget->setSortingEnabled(false);
    tableWidget->setRowCount(bindings.size());
    int row = 0;
    int column = 0;
    QListIterator<Soprano::BindingSet> it(bindings);
    for (; it.hasNext(); column = 0, row++) {
        Soprano::BindingSet bs = it.next();
        QStringList bindingNames = bs.bindingNames();
        kDebug(30015) << "bindings.sz:" << bindingNames.size();
        if (row == 0) {
            tableWidget->setColumnCount(bindingNames.size());
            tableWidget->setHorizontalHeaderLabels(bindingNames);
        }
        foreach (const QString &b, bindingNames) {
            QString cellText = bs[b].toString();
            QTableWidgetItem *newItem = new QTableWidgetItem(cellText);
            tableWidget->setItem(row, column, newItem);
            kDebug(30015) << "r:" << row << " c:" << column << " data:" << cellText;
            ++column;
        }
    }
    tableWidget->setSortingEnabled(true);
}

hKoSemanticStylesheet KoDocumentRdfEditWidget::stylesheetFromComboBox(QComboBox *w) const
{
    QAbstractItemModel *m = w->model();
    QVariant ud = m->data(m->index(w->currentIndex(), 0), Qt::UserRole);
    KoSemanticStylesheet *ss = ud.value<KoSemanticStylesheet*>();
    hKoSemanticStylesheet ret(ss);
    return ret;
}

void KoDocumentRdfEditWidget::applyStylesheetFromComboBox(QComboBox *comboBox) const
{
    KoDocumentRdf *rdf = d->m_rdf;
    Q_ASSERT(rdf);
    QString stylesheetName = comboBox->currentText();
    kDebug(30015) << "changing default stylesheet to:" << stylesheetName;
    hKoSemanticStylesheet ss = stylesheetFromComboBox(comboBox);
    const QString semanticItemClass = comboBox->property(SemanticItemClassId).toString();
    hKoRdfSemanticItem si(static_cast<KoRdfSemanticItem *>(
	rdf->createSemanticItem(semanticItemClass).data()));
    if (si) {
        si->defaultStylesheet(ss);
    }

    QMap<int, KoDocumentRdf::reflowItem> reflowCol;
    const QList<hKoRdfSemanticItem> semanticItems = KoRdfSemanticItem::fromList(rdf->semanticItems(semanticItemClass));
    foreach (hKoRdfSemanticItem semanticItem, semanticItems) {
        rdf->insertReflow(reflowCol, semanticItem, ss);
    }
    rdf->applyReflow(reflowCol);
}

//
// build a map end-pos -> { extent, semitem*, xmlid }
// and apply in reverse order.
//
void KoDocumentRdfEditWidget::onDefaultSheetButtonClicked()
{
    QPushButton *pushButton = qobject_cast<QPushButton*>(sender());
    Q_ASSERT(pushButton);
    const QString semanticItemClass = pushButton->property(SemanticItemClassId).toString();
    QComboBox *comboBox = d->m_defaultStylesheetComboBoxMap.value(semanticItemClass);
    Q_ASSERT(comboBox);
    applyStylesheetFromComboBox(comboBox);
}

void KoDocumentRdfEditWidget::onDefaultAllSheetButtonClicked()
{
    foreach(QComboBox* comboBox, d->m_defaultStylesheetComboBoxMap) {
        applyStylesheetFromComboBox(comboBox);
    }
}

#include <KoDocumentRdfEditWidget.moc>
