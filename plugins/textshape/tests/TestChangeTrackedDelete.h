#ifndef TESTCHANGETRACKEDDELETE_H
#define TESTCHANGETRACKEDDELETE_H

#include <QObject>
#include <QtTest>

class QTextDocument;

class TestChangeTrackedDelete : public QObject
{
    Q_OBJECT
public:
    TestChangeTrackedDelete();
    ~TestChangeTrackedDelete();

private:
    void insertSampleList(QTextDocument *document);
    void insertSampleTable(QTextDocument *document);

private Q_SLOTS:
    void testDeletePreviousChar();
    void testDeleteNextChar();
    void testDeleteSelection();
    void testPrefixMerge();
    void testSuffixMerge();
    void testInterMerge();
    void testPartialListItemDelete();
    void testListItemDelete();
    void testListDelete();
    void testTableDelete();
};

#endif
