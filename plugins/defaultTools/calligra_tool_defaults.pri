


HEADERS +=      Plugin.h \
                defaulttool/DefaultTool.h \
                defaulttool/DefaultToolFactory.h \
                defaulttool/DefaultToolWidget.h \
                defaulttool/DefaultToolArrangeWidget.h \
                defaulttool/DefaultToolTransformWidget.h \
                defaulttool/ShapeMoveStrategy.h \
                defaulttool/ShapeResizeStrategy.h \
                defaulttool/ShapeRotateStrategy.h \
                defaulttool/ShapeShearStrategy.h \
                defaulttool/SelectionDecorator.h \
                defaulttool/SelectionTransformCommand.h \
                defaulttool/ChartResizeStrategy.h \
                guidestool/GuidesTool.h \
                guidestool/GuidesToolFactory.h \
                guidestool/GuidesToolOptionWidget.h \
                guidestool/InsertGuidesToolOptionWidget.h \
                connectionTool/ConnectionTool.h \
                connectionTool/ConnectionToolFactory.h \
                connectionTool/AddConnectionPointCommand.h \
                connectionTool/RemoveConnectionPointCommand.h \
                connectionTool/ChangeConnectionPointCommand.h \
                connectionTool/MoveConnectionPointStrategy.h \
                connectionTool/ConnectionPointWidget.h

SOURCES +=      Plugin.cpp \
                defaulttool/DefaultTool.cpp \
                defaulttool/DefaultToolFactory.cpp \
                defaulttool/DefaultToolWidget.cpp \
                defaulttool/DefaultToolArrangeWidget.cpp \
                defaulttool/DefaultToolTransformWidget.cpp \
                defaulttool/ShapeMoveStrategy.cpp \
                defaulttool/ShapeResizeStrategy.cpp \
                defaulttool/ShapeRotateStrategy.cpp \
                defaulttool/ShapeShearStrategy.cpp \
                defaulttool/SelectionDecorator.cpp \
                defaulttool/SelectionTransformCommand.cpp \
                defaulttool/ChartResizeStrategy.cpp \
                guidestool/GuidesTool.cpp \
                guidestool/GuidesToolFactory.cpp \
                guidestool/GuidesToolOptionWidget.cpp \
                guidestool/InsertGuidesToolOptionWidget.cpp \
                connectionTool/ConnectionTool.cpp \
                connectionTool/ConnectionToolFactory.cpp \
                connectionTool/AddConnectionPointCommand.cpp \
                connectionTool/RemoveConnectionPointCommand.cpp \
                connectionTool/ChangeConnectionPointCommand.cpp \
                connectionTool/MoveConnectionPointStrategy.cpp \
                connectionTool/ConnectionPointWidget.cpp

FORMS +=        defaulttool/DefaultToolWidget.ui \
                defaulttool/DefaultToolArrangeWidget.ui \
                defaulttool/DefaultToolTransformWidget.ui \
                guidestool/GuidesToolOptionWidget.ui \
                guidestool/InsertGuidesToolOptionWidget.ui \
                connectionTool/ConnectionPointWidget.ui
