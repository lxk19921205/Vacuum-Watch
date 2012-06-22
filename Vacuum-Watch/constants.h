#ifndef _VACUUM_WATCH_CONSTANTS_H_
#define _VACUUM_WATCH_CONSTANTS_H_

#define VW_WINDOW_TITLE ("Vacuum-Watch")

// #define VW_OPTION_FILENAME ("Options.opt")	//注：这是具体实现的东西，放在自己实现的类里边！
//#define VW_LOG_CLOSED 0	//注：暂时用不到，日志常开着吧..
//////////////////////////////////////////////////////////////////////////
//在option里的默认设置，即没有之前文件可读的时候的返回的参数
//背景音乐开启？
#define VW_OPTION_DEF_BGM (true)
//音效开启？
#define VW_OPTION_DEF_EFFECT (true)
//默认音量百分比
#define VW_OPTION_DEF_VOLUME (50)	//50%
//默认fire的键位
#define VW_OPTION_DEF_FIRE_KEY (100)	//TODO 默认采用100，一个随便写的值，以后再改
//////////////////////////////////////////////////////////////////////////

#endif
