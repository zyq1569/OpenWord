shellpower : chcp 65001  --> utf8

界面说明：

KoOpenPane是 Open Existing Document 界面
KoDetailsPane是显示最近打开文件+打开这个文档 ：的界面
class KoRecentDocumentsPane : public KoDetailsPane 是KoDetailsPane 具体的动作实现类
KoRecentDocumentsPane.h {static const int MAX_RECENTFILES_ENTRIES = 20;//recent files }


对象创建过程：

创建 KoPart过程
bool KoApplication::start()
---> KoPart *part = entry.createKoPart(&errorMsg);
---> KoPart *KoDocumentEntry::createKoPart(QString* errorMsg) const
---> QObject* KWFactory::create( 中创建 KoPart
同时释放采用延后释放： 在 void KoPart::deleteOpenPane(bool closing)---> ：d->startUpWidget->hide();     d->startUpWidget->deleteLater();


KoOpenPane KoRecentDocumentsPane 创建过程 【KoPart 中】
创建过程 ：KoPart::showStartUpWidget--》创建  KoOpenPane ，在KoOpenPane::initRecentDocs()中 创建KoRecentDocumentsPane
{
在 void KoPart::showStartUpWidget(KoMainWindow *mainWindow, bool alwaysShow) 中
创建 d->startUpWidget = createOpenPane(mainWindow, d->templatesResourcePath);
在
KoOpenPane *KoPart::createOpenPane(QWidget *parent, const QString& templatesResourcePath) 中
创建KoOpenPane  KoOpenPane *openPane = new KoOpenPane(parent, mimeFilter, templatesResourcePath);


void KoOpenPane::initRecentDocs()
{
 KoRecentDocumentsPane* recentDocPane = new KoRecentDocumentsPane(this, header);
}

}

所有插件通过KoPluginLoader::load( 来添加的
例如：
void KoDockRegistry::init()
{
    KoPluginLoader::PluginsConfig config;
    config.whiteList = "DockerPlugins";
    config.blacklist = "DockerPluginsDisabled";
    config.group = "calligra";
    KoPluginLoader::load(QStringLiteral("calligra/dockers"), config);
}


////----------当前的激活得到窗体  -----------------
KoView *KoMainWindow::rootView() const
{
    if (d->rootViews.indexOf(d->activeView) != -1)
    {
        return d->activeView;
    }
    return d->rootViews.empty() ? nullptr : d->rootViews.first();
}
///----------------------------------------------------

///------------dockers 中 shape properties 对应的组件 class ShapePropertiesDocker : public QDockWidget, public KoCanvasObserverBase
显示时无法调整组件所在窗体


##-----------------$$ 修改右侧的工具内容显示方式：--------------------------------------------------------------
能够显示或者隐藏，有一个竖形线显示（参考libreoffice）

目前 判断 整个面板容器是KoModeBoxDocker，需求对这个容器进行显示或者隐藏
通过KoModeBox（目前定义的名称 为main tool）嵌入 容器KoModeBoxDocker 中
KoModeBoxDocker::KoModeBoxDocker(KoModeBox *modeBox)
    : m_modeBox(modeBox)
{
    setWidget(modeBox);
//    setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    setFeatures(AllDockWidgetFeatures);
    setWindowTitle("MainTool");//openword20210531
    setObjectName("ModeBox");

    connect(this, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(locationChanged(Qt::DockWidgetArea)));
}

///
void KoModeBoxDocker::locationChanged(Qt::DockWidgetArea area)

KoModeBoxDocker 中选中某一项响应
void KoModeBox::toolSelected(int index)
{
    if (index != -1)
    {
        d->addedToolActions.at(index)->trigger();
    }
}

$$$---------------------------------------------------------------
class ToolDockerFactory : public KoDockFactoryBase
{
public:
    ToolDockerFactory() : KoDockFactoryBase() { }

    QString id() const override
    {
        return "sharedtooldocker";////??????????????当前是那个控件？？？？？20210605
    }

    QDockWidget* createDockWidget() override
    {
        KoToolDocker * dockWidget = new KoToolDocker();
        return dockWidget;
    }

    DockPosition defaultDockPosition() const override
    {
        return DockRight;
    }
};

$$------------------------------------------------------------------



KoDockerManager::KoDockerManager(KoMainWindow *mainWindow)



插件的添加方式：
KoToolRegistry::instance()->add(new TextToolFactory()){
   KoToolRegistry::instance()->add(new TextToolFactory());
    KoToolRegistry::instance()->add(new ReviewToolFactory());
    KoToolRegistry::instance()->add(new ReferencesToolFactory());
    KoShapeRegistry::instance()->add(new TextShapeFactory());
    KoShapeRegistry::instance()->add(new AnnotationTextShapeFactory());
	KoDockRegistry::instance()->add(new TextDocumentInspectionDockerFactory());
	}
	dockRegistry->add(new KWStatisticsDockerFactory());
    dockRegistry->add(new KWNavigationDockerFactory());
	

--------------------------->	
KoModeBoxFactory.cpp
QDockWidget* KoModeBoxFactory::createDockWidget() 中 【 dockWidget = factory->createDockWidget();】创建 KoModeBoxDocker容器 然后把创建的KoModeBox嵌入容器KoModeBoxDocker

https://blog.csdn.net/czyt1988/article/details/51209619 可以参考容器的关系

在 KoView::KoView(KoPart *part, KoDocument *document, QWidget *parent) 中     // add all plugins.  
   foreach(const QString & docker, KoDockRegistry::instance()->keys())
   
   
   
 KoMainWindow::KoMainWindow( ) ---->    d->dockerManager = new KoDockerManager(this);  --->
 d->toolOptionsDocker = qobject_cast<KoToolDocker*>(mainWindow->createDockWidget(&toolDockerFactory));  ---->
 dockWidget = factory->createDockWidget();
 
 
 
 
$$$---------------------------------------------------------------------------------
bool KoApplication::start()-------->

KoPart *part = entry.createKoPart(&errorMsg);  ----> 调用下面函数

KoPart *KoDocumentEntry::createKoPart(QString* errorMsg) const  ---->
{
KPluginFactory *factory = qobject_cast<KPluginFactory *>(obj);
KoPart *part            = factory->create<KoPart>(0, QVariantList());		
}
通过下面 创建窗体 
KoMainWindow *mainWindow = part->createMainWindow();

然后显示窗体
KWPart::showStartUpWidget(KoMainWindow *parent, bool alwaysShow)



$$$------------------------------------------------------------------------------------
KoToolProxy 代理所有鼠标键盘事件响应





[[[[
KoView *view = d->rootPart->createView(doc, this); ----------------------->>>>>>>>>>
KoView *KWPart::createViewInstance(KoDocument *document, QWidget *parent)
{
    KWView *view = new KWView(this, qobject_cast<KWDocument*>(document), parent);
    setupViewInstance(document, view);
    return view;
}

------------------------>

KWView::KWView(KoPart *part, KWDocument *document, QWidget *parent)
    : KoView(part, document, parent)
    , m_canvas(0)
    , m_textMinX(1)
    , m_textMaxX(600)
    , m_minPageNum(1)
    , m_maxPageNum(1)
    , m_isFullscreenMode(false)
{
    setAcceptDrops(true);

    m_document = document;
    m_snapToGrid = m_document->gridData().snapToGrid();
    m_gui = new KWGui(QString(), this);
    m_canvas = m_gui->canvas();
}   
}
----------------------->    KWGui::KWGui(const QString &viewMode, KWView *parent)



文档编辑中，文字中光标选中时间，对应的响应事件
void TextTool::editingPluginEvents()

编辑中 对应的文字中URL 的链接 函数 void TextTool::runUrl(KoPointerEvent *event, QString &url)



$$------------------------------
KoDocument.cpp 中存储了各个文档的类型 后缀



$$-----------------------------
style manager界面的语言调试通过
void KoGlobal::createListOfLanguages() 
读取语言进行翻译



$$$$$$$$$$$$$$$$$$$---------------------------------------------------------------------------
文档编辑中，滚动条工具
class FLAKE_EXPORT KoCanvasControllerWidget : public QAbstractScrollArea, public KoCanvasController

KWGui::KWGui(const QString &viewMode, KWView *parent) ------------------->
KoCanvasControllerWidget *canvasController = new KoCanvasControllerWidget(m_view->actionCollection(), this);
    m_canvasController = canvasController;
	
	------------------------>>>>>>>>>>>>>>>>>>>
gridLayout->addWidget(canvasController, 1, 1);



------------------------------------------------------------------
显示各个组件的标题内容title
void KoMainWindow::showDockerTitleBars(bool show)
{
    foreach (QDockWidget *dock, dockWidgets())
    {
        if (dock->titleBarWidget())
        {
            dock->titleBarWidget()->setVisible(show);
        }
    }

    KConfigGroup configGroupInterface =  KSharedConfig::openConfig()->group("Interface");
    configGroupInterface.writeEntry("ShowDockerTitleBars", show);
}
////////////////

添加了显示或者隐藏工具箱的按钮
在 KWGui::KWGui(const QString &viewMode, KWView *parent)：
{
	//将QDockWidget 和 窗体关联起来代码设置
    if (m_view->mainWindow())
    {
        KoModeBoxFactory modeBoxFactory(canvasController, qApp->applicationName(), i18n("Tools"));
        QDockWidget* modeBox = m_view->mainWindow()->createDockWidget(&modeBoxFactory);
		
        m_view->mainWindow()->dockerManager()->removeToolOptionsDocker();
		//modeBox = class KoModeBoxDocker : public QDockWidget, public KoCanvasObserverBase
		//所以可以使用dynamic_cast<KoCanvasObserverBase*>进行关联
        dynamic_cast<KoCanvasObserverBase*>(modeBox)->setObservedCanvas(m_canvas);
    }
	
	
	....
    //openword  add2021-0605
    m_showtoolbox = new QToolButton();
    if (m_showtoolbox)
    {
        m_showtoolbox->setArrowType(Qt::ArrowType::RightArrow);
        m_showtoolbox->setAutoRaise(true);
        m_showtoolbox->setToolTip("显示工具箱");
        gridLayout->addWidget(m_showtoolbox, 1, 2);
    }
}



//----
是否为maintool 工具列表组合？？？
void KoModeBox::setOptionWidgets(const QList<QPointer<QWidget> > &optionWidgetList)


/// 组件的锁的功能
void KoDockWidgetTitleBar::setLocked(bool locked)


//增加按钮来显示或者隐藏工具箱
void KWGui::visibleDockWidget(bool checked)


    // add all plugins. 读取配置信息
    foreach(const QString & docker, KoDockRegistry::instance()->keys())
    {
        debugMain<<"foreach(const QString & docker, KoDockRegistry::instance()->keys())"<<docker;
        KoDockFactoryBase *factory = KoDockRegistry::instance()->value(docker);
        if (mainWindow())
        {
            mainWindow()->createDockWidget(factory);
        }
    }
	

		KConfigGroup group =  KSharedConfig::openConfig()->group(d->rootPart->componentData().componentName()).group("DockWidget " + factory->id());
	collapsed = group.readEntry("Collapsed", collapsed);
	locked = group.readEntry("Locked", locked);
	
			// Save collapsable state of dock widgets
for (QMap<QString, QDockWidget*>::const_iterator i = d->dockWidgetsMap.constBegin();
		i != d->dockWidgetsMap.constEnd(); ++i)
{
	if (i.value()->widget())
	{
		KConfigGroup dockGroup = group.group(QString("DockWidget ") + i.key());
		dockGroup.writeEntry("Collapsed", i.value()->widget()->isHidden());
		dockGroup.writeEntry("Locked", i.value()->property("Locked").toBool());
		dockGroup.writeEntry("DockArea", (int) dockWidgetArea(i.value()));
	}
}



//选择图片的对话框  ------>
KUndo2Command* addShape(KoShape *shape, bool showDialog, KUndo2Command *parent)

获取选择的图片的路径

----------->
void PictureShapeLoadWaiter::setImageData(KJob *job)

是否关系到 QImage KoImageData::image() const   ???

KoShape *KoShapeRegistry::Private::createShapeInternal(const KoXmlElement &fullElement,
        KoShapeLoadingContext &context,
        const KoXmlElement &element) const
		
		
		
###########代码错误修改bug
// 解决doc docx文件导入的错误
KoFilter* KoFilterEntry::createFilter(KoFilterChain* chain, QObject* parent)


解决打印PDF文件中图像丢失 
在void preparePage(const QVariant &page)中修改的20210424
{

....
 ///open word ---> to find print file problem??? 20210424  解决打印PDF文件中图像丢失///
            const int progressPart = 45 / shapes.count();
            foreach(KoShape *shape, shapes)
            {
                debugMain << "Calling waitUntilReady on shape;" << shape;
                if(! stop)
                {
                    ///set false:for error! {print or export PDF file: loss image! }
                    shape->waitUntilReady(zoomer,false);
                }
                debugMain << "done";
                updater->setProgress(updater->progress() + progressPart);
            }
			
...
}
