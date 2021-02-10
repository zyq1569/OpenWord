#ifndef KUNDO2COMMAND_H
#define KUNDO2COMMAND_H

#include <kundo2stack.h>

class KUNDO2_EXPORT KUndo2Command
{
    KUndo2CommandPrivate *d;
    int timedID;

public:
    explicit KUndo2Command(KUndo2Command *parent = 0);
    explicit KUndo2Command(const KUndo2MagicString &text, KUndo2Command *parent = 0);
    virtual ~KUndo2Command();

    virtual void undo();
    virtual void redo();

    QString actionText() const;
    KUndo2MagicString text() const;
    void setText(const KUndo2MagicString &text);

    virtual int id() const;
    virtual int timedId();
    virtual void setTimedID(int timedID);
    virtual bool mergeWith(const KUndo2Command *other);
    virtual bool timedMergeWith(KUndo2Command *other);

    int childCount() const;
    const KUndo2Command *child(int index) const;

    bool hasParent();
    virtual void setTime();
    virtual QTime time();
    virtual void setEndTime();
    virtual QTime endTime();

    virtual QVector<KUndo2Command*> mergeCommandsVector();
    virtual bool isMerged();
    virtual void undoMergedCommands();
    virtual void redoMergedCommands();

    /**
     * \return user-defined object associated with the command
     *
     * \see setExtraData()
     */
    KUndo2CommandExtraData* extraData() const;

    /**
     * The user can assign an arbitrary object associated with the
     * command. The \p data object is owned by the command. If you assign
     * the object twice, the first one will be destroyed.
     */
    void setExtraData(KUndo2CommandExtraData *data);

    /**
     * Add the @p command as a child to this command
     */
    void addCommand(KUndo2Command *command);

private:
    Q_DISABLE_COPY(KUndo2Command)
    friend class KUndo2QStack;


    bool m_hasParent;
    int m_timedID;

    QTime m_timeOfCreation;
    QTime m_endOfCommand;
    QVector<KUndo2Command*> m_mergeCommandsVector;
};


class KUndo2CommandPrivate
{
public:
    KUndo2CommandPrivate() : id(-1) {}
    QList<KUndo2Command*> child_list;
    QString actionText;
    KUndo2MagicString text;
    int id;

    QScopedPointer<KUndo2CommandExtraData> extraData;
};


#endif // KUNDO2COMMAND_H
