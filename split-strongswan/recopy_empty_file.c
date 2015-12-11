#include <stdio.h>
//重新拷贝空文件
void recopy_empty_file()
{
	char tmp0[254];
	sprintf(tmp0,"cp ./new/data  ./data");
	system(tmp0);

	char tmp1[254];
	sprintf(tmp1,"cp ./new/ipsec.secrets  ./ipsec.secrets");
	system(tmp1);
}
