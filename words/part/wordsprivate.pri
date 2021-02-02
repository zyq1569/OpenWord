
HEADERS +=  ui_KWFrameConnectSelector.h \
            ui_KWRunAroundProperties.h \
            ui_KWAnchoringProperties.h \
            ui_KWDocumentColumns.h \
            ui_KWStartupWidget.h \
            ui_KWCreateBookmark.h \
            ui_KWSelectBookmark.h \
            ui_KWInsertImage.h \
            ui_StatisticsPreferencesPopup.h \
            ui_SimpleSetupWidget.h \
            ui_SimpleHeaderFooterWidget.h

SOURCES +=  KWFactory.cpp \
            WordsDebug.cpp \
            Words.cpp \
            KWApplicationConfig.cpp \
            KWCanvasBase.cpp \
            KWCanvas.cpp \
            KWCanvasItem.cpp \
            KWDocument.cpp \
            KWGui.cpp \
            KWView.cpp \
            KWPart.cpp \
            KWPage.cpp \
            KWPageCacheManager.cpp \
            KWPageManager.cpp \
            KWPageStyle.cpp \
            KWViewMode.cpp \
            KWViewModeNormal.cpp \
            KWViewModePreview.cpp \
            KWStatusBar.cpp \
            KWOdfLoader.cpp \
            KWOdfWriter.cpp \
            KWOdfSharedLoadingData.cpp \
            KWRootAreaProviderBase.cpp \
            KWRootAreaProviderTextBox.cpp \
            KWRootAreaProvider.cpp \
            pagetool/KWPageTool.cpp \
            pagetool/KWPageToolFactory.cpp \
            pagetool/SimpleSetupWidget.cpp \
            pagetool/SimpleHeaderFooterWidget.cpp \
            frames/KWFrameLayout.cpp \
            frames/KWFrame.cpp \
            frames/KWFrameSet.cpp \
            frames/KWTextFrameSet.cpp \
            frames/KWCopyShape.cpp \
            widgets/KoFindToolbar.cpp \
            dialogs/KWFrameConnectSelector.cpp \
            dialogs/KWRunAroundProperties.cpp \
            dialogs/KWAnchoringProperties.cpp \
            dialogs/KWFrameDialog.cpp \
            dialogs/KWShapeConfigFactory.cpp \
            dialogs/KWDocumentColumns.cpp \
            dialogs/KWStartupWidget.cpp \
            dialogs/KWPageSettingsDialog.cpp \
            dialogs/KWPrintingDialog.cpp \
            dialogs/KWCreateBookmarkDialog.cpp \
            dialogs/KWSelectBookmarkDialog.cpp \
            dialogs/KWConfigureDialog.cpp \
            dockers/KWStatisticsDocker.cpp \
            dockers/KWStatisticsWidget.cpp \
            dockers/StatisticsPreferencesPopup.cpp \
            dockers/KWNavigationDocker.cpp \
            dockers/KWNavigationDockerFactory.cpp \
            dockers/KWNavigationWidget.cpp \
            commands/KWPageStylePropertiesCommand.cpp \
            commands/KWNewPageStyleCommand.cpp \
            commands/KWChangePageStyleCommand.cpp \
            commands/KWShapeCreateCommand.cpp \
            dockers/KWDebugDocker.cpp \
            dockers/KWDebugDockerFactory.cpp \
            dockers/KWDebugWidget.cpp

FORMS +=    dialogs/KWFrameConnectSelector.ui \
            dialogs/KWRunAroundProperties.ui \
            dialogs/KWAnchoringProperties.ui \
            dialogs/KWDocumentColumns.ui \
            dialogs/KWStartupWidget.ui \
            dialogs/KWCreateBookmark.ui \
            dialogs/KWSelectBookmark.ui \
            dialogs/KWInsertImage.ui \
            dockers/StatisticsPreferencesPopup.ui \
            pagetool/SimpleSetupWidget.ui \
            pagetool/SimpleHeaderFooterWidget.ui
