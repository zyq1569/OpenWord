

HEADERS +=  MusicDebug.h \
            MusicShape.h \
            MusicShapeFactory.h \
            MusicTool.h \
            MusicToolFactory.h \
            SimpleEntryTool.h \
            SimpleEntryToolFactory.h \
            MusicStyle.h \
            Engraver.h \
            Renderer.h \
            MusicCursor.h \
            dialogs/PartsWidget.h \
            dialogs/PartDetailsDialog.h \
            dialogs/SimpleEntryWidget.h \
            dialogs/PartsListModel.h \
            dialogs/KeySignatureDialog.h \
            dialogs/StaffElementPreviewWidget.h \
            actions/AbstractMusicAction.h \
            actions/AbstractNoteMusicAction.h \
            actions/NoteEntryAction.h \
            actions/AccidentalAction.h \
            actions/EraserAction.h \
            actions/DotsAction.h \
            actions/SetClefAction.h \
            actions/TimeSignatureAction.h \
            actions/KeySignatureAction.h \
            actions/RemoveBarAction.h \
            actions/TiedNoteAction.h \
            actions/SelectionAction.h \
            commands/AddPartCommand.h \
            commands/RemovePartCommand.h \
            commands/ChangePartDetailsCommand.h \
            commands/CreateChordCommand.h \
            commands/AddNoteCommand.h \
            commands/SetAccidentalsCommand.h \
            commands/AddBarsCommand.h \
            commands/RemoveNoteCommand.h \
            commands/RemoveChordCommand.h \
            commands/AddDotCommand.h \
            commands/SetClefCommand.h \
            commands/RemoveStaffElementCommand.h \
            commands/SetTimeSignatureCommand.h \
            commands/SetKeySignatureCommand.h \
            commands/RemoveBarCommand.h \
            commands/MakeRestCommand.h \
            commands/ToggleTiedNoteCommand.h \
            core/Global.h \
            core/Sheet.h \
            core/Part.h \
            core/PartGroup.h \
            core/Staff.h \
            core/Voice.h \
            core/Bar.h \
            core/VoiceBar.h \
            core/VoiceElement.h \
            core/StaffElement.h \
            core/Chord.h \
            core/Note.h \
            core/Clef.h \
            core/KeySignature.h \
            core/TimeSignature.h \
            core/StaffSystem.h \
            core/MusicXmlWriter.h \
            core/MusicXmlReader.h

SOURCES +=  MusicDebug.cpp \
            MusicShape.cpp \
            MusicShapeFactory.cpp \
            MusicTool.cpp \
            MusicToolFactory.cpp \
            SimpleEntryTool.cpp \
            SimpleEntryToolFactory.cpp \
            MusicStyle.cpp \
            Engraver.cpp \
            Renderer.cpp \
            MusicCursor.cpp \
            dialogs/PartsWidget.cpp \
            dialogs/PartDetailsDialog.cpp \
            dialogs/SimpleEntryWidget.cpp \
            dialogs/PartsListModel.cpp \
            dialogs/KeySignatureDialog.cpp \
            dialogs/StaffElementPreviewWidget.cpp \
            actions/AbstractMusicAction.cpp \
            actions/AbstractNoteMusicAction.cpp \
            actions/NoteEntryAction.cpp \
            actions/AccidentalAction.cpp \
            actions/EraserAction.cpp \
            actions/DotsAction.cpp \
            actions/SetClefAction.cpp \
            actions/TimeSignatureAction.cpp \
            actions/KeySignatureAction.cpp \
            actions/RemoveBarAction.cpp \
            actions/TiedNoteAction.cpp \
            actions/SelectionAction.cpp \
            commands/AddPartCommand.cpp \
            commands/RemovePartCommand.cpp \
            commands/ChangePartDetailsCommand.cpp \
            commands/CreateChordCommand.cpp \
            commands/AddNoteCommand.cpp \
            commands/SetAccidentalsCommand.cpp \
            commands/AddBarsCommand.cpp \
            commands/RemoveNoteCommand.cpp \
            commands/RemoveChordCommand.cpp \
            commands/AddDotCommand.cpp \
            commands/SetClefCommand.cpp \
            commands/RemoveStaffElementCommand.cpp \
            commands/SetTimeSignatureCommand.cpp \
            commands/SetKeySignatureCommand.cpp \
            commands/RemoveBarCommand.cpp \
            commands/MakeRestCommand.cpp \
            commands/ToggleTiedNoteCommand.cpp \
            core/Global.cpp \
            core/Sheet.cpp \
            core/Part.cpp \
            core/PartGroup.cpp \
            core/Staff.cpp \
            core/Voice.cpp \
            core/Bar.cpp \
            core/VoiceBar.cpp \
            core/VoiceElement.cpp \
            core/StaffElement.cpp \
            core/Chord.cpp \
            core/Note.cpp \
            core/Clef.cpp \
            core/KeySignature.cpp \
            core/TimeSignature.cpp \
            core/StaffSystem.cpp \
            core/MusicXmlWriter.cpp \
            core/MusicXmlReader.cpp

FORMS +=    dialogs/PartsWidget.ui \
            dialogs/PartDetailsDialog.ui \
            dialogs/SimpleEntryWidget.ui \
            dialogs/KeySignatureDialog.ui
