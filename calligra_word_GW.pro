#https://community.kde.org/Calligra/Libs/KoText/Layout_Overview

CONFIG     +=   ordered

TEMPLATE    =   subdirs

SUBDIRS    +=   log/easylog.pro \
                filters/words/rtf/import/3rdparty/rtf-qt/src/RtfReader.pro \
                libs/plugin/koplugin.pro \
                plugins/chartshape/chartshapecore.pro \
                libs/vectorimage/kovectorimage.pro \
                libs/version/koversion.pro \
                filters/libmso/mso.pro \
                libs/store/kostore.pro \
                libs/odf/koodf.pro \
                filters/libodf2/koodf2.pro \
                libs/kundo2/kundo2.pro \
                libs/pigment/pigmentcms.pro \
                libs/widgetutils/kowidgetutils.pro \
                filters/libodfreader/koodfreader.pro \
                libs/flake/flake.pro \
                libs/text/kotext.pro \
                libs/widgets/kowidgets.pro \
                libs/basicflakes/basicflakes.pro \
                libs/textlayout/kotextlayout.pro \
                filters/words/msword-odf/wv2/src/kowv2.pro \
                libs/main/komain.pro \
                plugins/formulashape/koformula.pro \
                filters/libmsooxml/komsooxml.pro \
                libs/basicflakes/plugin/calligra_tool_basicflakes.pro \
                words/part/wordsprivate.pro \
                plugins/dockers/calligra_docker_defaults.pro \
                plugins/stencilsdocker/calligra_docker_stencils.pro \
                filters/words/msword-odf/calligra_filter_doc2odt.pro \
                filters/words/docx/import/calligra_filter_docx2odt.pro \
                filters/words/docx/export/calligra_filter_odt2docx.pro \
                plugins/artistictextshape/calligra_shape_artistictext.pro \
                plugins/formulashape/calligra_shape_formula.pro \
                plugins/musicshape/calligra_shape_music.pro \
                plugins/pathshapes/calligra_shape_paths.pro \
                plugins/pictureshape/calligra_shape_picture.pro \
                plugins/pluginshape/calligra_shape_plugin.pro \
                plugins/textshape/calligra_shape_text.pro \
                plugins/vectorshape/calligra_shape_vector.pro \
                plugins/videoshape/calligra_shape_video.pro \
                plugins/chartshape/calligra_shape_chart.pro \
                plugins/defaultTools/calligra_tool_defaults.pro \
                words/part/calligrawordspart.pro \
#                plugins/karbonplugins/tools/karbon_tools.pro \
                libs/kross/kokross.pro \
                extras/thumbnail/calligraimagethumbnail.pro \
                extras/thumbnail/calligrathumbnail.pro \
                plugins/variables/calligra_textinlineobject_variables.pro \
                plugins/textediting/autocorrection/calligra_textediting_autocorrect.pro \
                plugins/textediting/changecase/calligra_textediting_changecase.pro \
                plugins/textediting/spellcheck/calligra_textediting_spellcheck.pro \
                plugins/textediting/thesaurus/calligra_textediting_thesaurus.pro \
#                libs/ki18n/KF5I18n.pro \
                filters/words/epub/calligra_filter_odt2html.pro \
                sheets/calligrasheets.pro \
                words/app/calligrawords.pro
#-------------------------------------------------
#                karbon/karbonpart.pro \
#                karbon/ui/karbonui.pro \
#                karbon/common/karboncommon.pro \
#                libs/pageapp/kopageapp.pro \
#-------------------------------------------------
#wordperfect to odf
#               filters/words/wordperfect/import/calligra_filter_wpd2odt.pro \
#----------------------------------------------------
#               extras/calligra/calligra.pro \
                #filters/words/applixword/calligra_filter_applixword2odt.pro \
                #filters/words/ascii/calligra_filter_ascii2words.pro \
                #filters/sheets/dbase/calligra_filter_dbase2kspread.pro \
                #filters/karbon/eps/calligra_filter_eps2svgai.pro \
                #filters/karbon/karbon1.x/calligra_filter_karbon1x2karbon.pro \
                #filters/karbon/image/calligra_filter_karbon2image.pro \
                #filters/karbon/svg/calligra_filter_karbon2svg.pro \
                #filters/karbon/wmf/calligra_filter_karbon2wmf.pro \
                #filters/stage/kpr2odf/calligra_filter_kpr2odp.pro \
                #filters/words/ascii/calligra_filter_odt2ascii.pro \
                #filters/words/epub/calligra_filter_odt2epub2.pro \
                #filters/words/mobi/calligra_filter_odt2mobi.pro \
                #filters/words/wiki/export/calligra_filter_odt2wiki.pro \
                #filters/stage/pptx/calligra_filter_pptx2odp.pro \
                #filters/words/rtf/import/calligra_filter_rtf2odt.pro \
                #filters/karbon/svg/calligra_filter_svg2karbon.pro \
                #filters/karbon/wmf/calligra_filter_wmf2svg.pro \
                #filters/karbon/xfig/calligra_filter_xfig2odg.pro \
                #plugins/shapefiltereffects/calligra_filtereffects.pro \
                #extras/properties/calligradocinfopropspage.pro \
                #stage/plugins/eventactions/calligrastageeventactions.pro \
                #stage/part/calligrastagepart.pro \
                #stage/part/calligrastageprivate.pro \
                #stage/part/tools/animationtool/calligrastagetoolanimation.pro \
                #karbon/plugins/flattenpath/karbon_flattenpath.pro \
                #karbon/plugins/refinepath/karbon_refinepath.pro \
                #karbon/plugins/roundcorners/karbon_roundcorners.pro \
                #karbon/plugins/whirlpinch/karbon_whirlpinch.pro \
                #stage/app/kdeinit_calligrastage.pro \
                #words/app/kdeinit_calligrawords.pro \
                #karbon/kdeinit_karbon.pro \
                #libs/pageapp/tools/backgroundTool/kopabackgroundtool.pro \
                #stage/plugins/pageeffects/barwipe/kpr_pageeffect_barwipe.pro \
                #stage/plugins/pageeffects/clockwipe/kpr_pageeffect_clockwipe.pro \
                #stage/plugins/pageeffects/edgewipe/kpr_pageeffect_edgewipe.pro \
                #stage/plugins/pageeffects/fade/kpr_pageeffect_fade.pro \
                #stage/plugins/pageeffects/iriswipe/kpr_pageeffect_iriswipe.pro \
                #stage/plugins/pageeffects/matrixwipe/kpr_pageeffect_matrixwipe.pro \
                #stage/plugins/pageeffects/slidewipe/kpr_pageeffect_slidewipe.pro \
                #stage/plugins/pageeffects/spacerotation/kpr_pageeffect_spacerotation.pro \
                #stage/plugins/pageeffects/swapeffect/kpr_pageeffect_swapeffect.pro \
                #stage/plugins/shapeanimations/example/kpr_shapeanimation_example.pro \
                #filters/stage/powerpoint/ppttoodplib.pro \


#ERROR_LOG(QString("Error reading file [ %1]\n Possible cause: %2 ").arg(filename).arg(status.text()))
