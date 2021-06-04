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


