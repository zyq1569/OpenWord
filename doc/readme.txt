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



##-----------------$$ 修改右侧的工具内容显示方式：--------------------------------------------------------------
能够显示或者隐藏，有一个竖形线显示（参考libreoffice）

目前 判断 整个面板容器是KoModeBoxDocker，需求对这个容器进行显示或者隐藏
通过KoModeBox嵌入 容器KoModeBoxDocker 中


QDockWidget* KoModeBoxFactory::createDockWidget() 中 【 dockWidget = factory->createDockWidget();】创建 KoModeBoxDocker容器 然后把创建的KoModeBox嵌入容器KoModeBoxDocker


在 KoView::KoView(KoPart *part, KoDocument *document, QWidget *parent) 中     // add all plugins.  
   foreach(const QString & docker, KoDockRegistry::instance()->keys())

