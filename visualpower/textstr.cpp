#include "stdafx.h"

//以下用于定义必须的字符串

//1.线路灵敏度宏文件
char *lsenstr[]={"dat\ntmp.dat\n\npfl\nqlc\nout sen fil\n1\n",
		"3\n","5\n","1\n12\nall\ntmp.out\nend\n"};
//2.节点电压灵敏度宏文件
char *nsenstr[]={"dat\ntmp.dat\n\npfl\nqlc\nout sen fil\n11\n",
		"3\n","1\n12\nall\ntmp.out\nend\n"};
char *wk[]={"日","一","二","三","四","五","六"};


char *glst[]={"发电机名","有功出力","无功出力","有功上限","无功上限","有功下限","无功下限"};
char *llst[]={"线路名","线路ID","流向末端有功","流向末端无功"};
char *dllst[]={"线路名","线路ID","流向末端有功","流向末端无功"};
char *blst[]={"母线名称","母线ID","电压幅值ＰＵ","电压绝对值","电压相角"};
char *dlst[]={"负荷名称","负荷ID","负荷状态","电压等级","有功负荷","无功负荷"};
char *tlst1[]={"变压器名称","变压器ID","高电压等级","档位","额定容量","有功","无功","当前温度","极限温度"};
char *tlst2[]={"变压器名称","变压器ID","高电压等级","高档位","中电压等级","中档位","低电压等级","低档位","额定容量","有功","无功","当前温度","极限温度"};
char *slst[]={"设备名称","设备号","母线名称","电压等级","投切状态","投入容量","投入组数"};
char *srlst[]={"设备名称","设备ID","投入状态","串联电抗"};