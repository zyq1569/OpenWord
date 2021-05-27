

KoOpenPane是 Open Existing Document 界面
KoDetailsPane是显示最近打开文件+打开这个文档 ：的界面
class KoRecentDocumentsPane : public KoDetailsPane 是KoDetailsPane 具体的动作实现类
KoRecentDocumentsPane.h {static const int MAX_RECENTFILES_ENTRIES = 20;//recent files }
