# ----------------------------------------------------
#
# ------------------------------------------------------

#message(" work!")


#HEADERS += ../../../calligra/plugins/chartshape/ui_StockConfigWidget.h \
#    ../../../calligra/plugins/chartshape/ui_TitlesConfigWidget.h \
#    ../../../calligra/plugins/chartshape/ui_LegendConfigWidget.h \
#    ../../../calligra/plugins/chartshape/ui_PlotAreaConfigWidget.h \
#    ../../../calligra/plugins/chartshape/ui_AxesConfigWidget.h \
#    ../../../calligra/plugins/chartshape/ui_DataSetConfigWidget.h \
#    ../../../calligra/plugins/chartshape/ui_PieConfigWidget.h \
#    ../../../calligra/plugins/chartshape/ui_RadarDataSetConfigWidget.h \
#    ../../../calligra/plugins/chartshape/ui_RingConfigWidget.h \
#    ../../../calligra/plugins/chartshape/ui_ChartTableEditor.h \
#    ../../../calligra/plugins/chartshape/ui_NewAxisDialog.h \
#    ../../../calligra/plugins/chartshape/ui_AxisScalingDialog.h \
#    ../../../calligra/plugins/chartshape/ui_CellRegionDialog.h \
#    ../../../calligra/plugins/chartshape/ui_FormatErrorBarDialog.h \
#    ../../../calligra/plugins/chartshape/ui_PieDataEditor.h \
#    ../../../calligra/plugins/chartshape/ui_BubbleDataEditor.h \
#    ../../../calligra/plugins/chartshape/ui_ScatterDataEditor.h \
#    ../../../calligra/plugins/chartshape/ui_StockDataEditor.h


 HEADERS +=     ChartDebug.cpp \
                kochart_global.h \
                KChartConvertions.h \
                Axis.h \
                DataSet.h \
                CellRegion.h \
                CellRegionStringValidator.h \
                ChartTableModel.h \
                Legend.h \
                TextLabelDummy.h \
                PlotArea.h \
                TableSource.h \
                ChartProxyModel.h \
                KChartModel.h \
                Surface.h \
                ChartDocument.h \
                ChartPart.h \
                ChartShape.h \
                ChartTool.h \
                ChartToolFactory.h \
                ConfigSubWidgetBase.h \
                TitlesConfigWidget.h \
                LegendConfigWidget.h \
                PlotAreaConfigWidget.h \
                AxesConfigWidget.h \
                DataSetConfigWidget.h \
                PieConfigWidget.h \
                StockConfigWidget.h \
                ChartTableView.h \
                ScreenConversions.h \
                ChartLayout.h \
                SingleModelHelper.h \
                OdfLoadingHelper.h \
                OdfHelper.h \
                dialogs/TableEditorDialog.h \
                dialogs/NewAxisDialog.h \
                dialogs/AxisScalingDialog.h \
                dialogs/CellRegionDialog.h \
                dialogs/FontEditorDialog.h \
                dialogs/FormatErrorBarDialog.h \
                dialogs/PieDataEditor.h \
                dialogs/BubbleDataEditor.h \
                dialogs/ScatterDataEditor.h \
                dialogs/BubbleDataSetTableModel.h \
                dialogs/ScatterDataSetTableModel.h \
                dialogs/StockDataEditor.h \
                commands/ChartTypeCommand.h \
                commands/LegendCommand.h \
                commands/AxisCommand.h \
                commands/DatasetCommand.h \
                commands/ChartTextShapeCommand.h \
                commands/AddRemoveAxisCommand.h \
                commands/GapCommand.h \
                commands/PlotAreaCommand.h \
                widgets/StrokeConfigWidget.h \
                widgets/RadarDataSetConfigWidget.h \
                widgets/RingConfigWidget.h

SOURCES +=      ChartDebug.cpp \
                kochart_global.cpp \
                KChartConvertions.cpp \
                Axis.cpp \
                DataSet.cpp \
                CellRegion.cpp \
                CellRegionStringValidator.cpp \
                ChartTableModel.cpp \
                Legend.cpp \
                TextLabelDummy.cpp \
                PlotArea.cpp \
                TableSource.cpp \
                ChartProxyModel.cpp \
                KChartModel.cpp \
                Surface.cpp \
                ChartDocument.cpp \
                ChartPart.cpp \
                ChartShape.cpp \
                ChartTool.cpp \
                ChartToolFactory.cpp \
                ConfigSubWidgetBase.cpp \
                TitlesConfigWidget.cpp \
                LegendConfigWidget.cpp \
                PlotAreaConfigWidget.cpp \
                AxesConfigWidget.cpp \
                DataSetConfigWidget.cpp \
                PieConfigWidget.cpp \
                StockConfigWidget.cpp \
                ChartTableView.cpp \
                ScreenConversions.cpp \
                ChartLayout.cpp \
                SingleModelHelper.cpp \
                OdfLoadingHelper.cpp \
                OdfHelper.cpp \
                dialogs/TableEditorDialog.cpp \
                dialogs/NewAxisDialog.cpp \
                dialogs/AxisScalingDialog.cpp \
                dialogs/CellRegionDialog.cpp \
                dialogs/FontEditorDialog.cpp \
                dialogs/FormatErrorBarDialog.cpp \
                dialogs/PieDataEditor.cpp \
                dialogs/BubbleDataEditor.cpp \
                dialogs/ScatterDataEditor.cpp \
                dialogs/BubbleDataSetTableModel.cpp \
                dialogs/ScatterDataSetTableModel.cpp \
                dialogs/StockDataEditor.cpp \
                commands/ChartTypeCommand.cpp \
                commands/LegendCommand.cpp \
                commands/AxisCommand.cpp \
                commands/DatasetCommand.cpp \
                commands/ChartTextShapeCommand.cpp \
                commands/AddRemoveAxisCommand.cpp \
                commands/GapCommand.cpp \
                commands/PlotAreaCommand.cpp \
                widgets/StrokeConfigWidget.cpp \
                widgets/RadarDataSetConfigWidget.cpp \
                widgets/RingConfigWidget.cpp

FORMS +=    StockConfigWidget.ui \
            TitlesConfigWidget.ui \
            LegendConfigWidget.ui \
            PlotAreaConfigWidget.ui \
            AxesConfigWidget.ui \
            DataSetConfigWidget.ui \
            PieConfigWidget.ui \
            widgets/RadarDataSetConfigWidget.ui \
            widgets/RingConfigWidget.ui \
            dialogs/ChartTableEditor.ui \
            dialogs/NewAxisDialog.ui \
            dialogs/AxisScalingDialog.ui \
            dialogs/CellRegionDialog.ui \
            dialogs/FormatErrorBarDialog.ui \
            dialogs/PieDataEditor.ui \
            dialogs/BubbleDataEditor.ui \
            dialogs/ScatterDataEditor.ui \
            dialogs/StockDataEditor.ui
