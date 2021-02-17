# ----------------------------------------------------
#
# ------------------------------------------------------


HEADERS +=      KarbonToolsPlugin.h \
                KarbonCursor.h \
                CalligraphyTool/KarbonCalligraphyTool.h \
                CalligraphyTool/KarbonCalligraphyOptionWidget.h \
                CalligraphyTool/KarbonCalligraphyToolFactory.h \
                CalligraphyTool/KarbonCalligraphicShape.h \
                CalligraphyTool/KarbonCalligraphicShapeFactory.h \
                CalligraphyTool/KarbonSimplifyPath.h \
                KarbonGradientTool.h \
                KarbonGradientToolFactory.h \
                KarbonGradientEditStrategy.h \
                KarbonPatternTool.h \
                KarbonPatternToolFactory.h \
                KarbonPatternEditStrategy.h \
                filterEffectTool/KarbonFilterEffectsTool.h \
                filterEffectTool/KarbonFilterEffectsToolFactory.h \
                filterEffectTool/FilterEffectEditWidget.h \
                filterEffectTool/FilterEffectScene.h \
                filterEffectTool/FilterEffectSceneItems.h \
                filterEffectTool/FilterInputChangeCommand.h \
                filterEffectTool/FilterAddCommand.h \
                filterEffectTool/FilterRemoveCommand.h \
                filterEffectTool/FilterStackSetCommand.h \
                filterEffectTool/FilterRegionChangeCommand.h \
                filterEffectTool/FilterEffectResource.h \
                filterEffectTool/FilterResourceServerProvider.h \
                filterEffectTool/FilterRegionEditStrategy.h \
                KarbonPatternOptionsWidget.h

SOURCES +=      KarbonToolsPlugin.cpp \
                KarbonCursor.cpp \
                CalligraphyTool/KarbonCalligraphyTool.cpp \
                CalligraphyTool/KarbonCalligraphyOptionWidget.cpp \
                CalligraphyTool/KarbonCalligraphyToolFactory.cpp \
                CalligraphyTool/KarbonCalligraphicShape.cpp \
                CalligraphyTool/KarbonCalligraphicShapeFactory.cpp \
                CalligraphyTool/KarbonSimplifyPath.cpp \
                KarbonGradientTool.cpp \
                KarbonGradientToolFactory.cpp \
                KarbonGradientEditStrategy.cpp \
                KarbonPatternTool.cpp \
                KarbonPatternToolFactory.cpp \
                KarbonPatternEditStrategy.cpp \
                filterEffectTool/KarbonFilterEffectsTool.cpp \
                filterEffectTool/KarbonFilterEffectsToolFactory.cpp \
                filterEffectTool/FilterEffectEditWidget.cpp \
                filterEffectTool/FilterEffectScene.cpp \
                filterEffectTool/FilterEffectSceneItems.cpp \
                filterEffectTool/FilterInputChangeCommand.cpp \
                filterEffectTool/FilterAddCommand.cpp \
                filterEffectTool/FilterRemoveCommand.cpp \
                filterEffectTool/FilterStackSetCommand.cpp \
                filterEffectTool/FilterRegionChangeCommand.cpp \
                filterEffectTool/FilterEffectResource.cpp \
                filterEffectTool/FilterResourceServerProvider.cpp \
                filterEffectTool/FilterRegionEditStrategy.cpp \
                KarbonPatternOptionsWidget.cpp

FORMS += filterEffectTool/FilterEffectEditWidget.ui \
         KarbonPatternOptionsWidget.ui
