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


##-----------------$$ 修改右侧的工具内容显示方式：--------------------------------------------------------------
能够显示或者隐藏，有一个竖形线显示（参考libreoffice）

目前 判断 整个面板容器是KoModeBoxDocker，需求对这个容器进行显示或者隐藏
通过KoModeBox嵌入 容器KoModeBoxDocker 中



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
 
 
 

