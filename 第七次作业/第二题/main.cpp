#include <iostream>
using namespace std;
#include "huffman.h"

int main()
{
	while (1) {
		int opt, flag = 0; // 初始化flag为0
		char ifname[256], ofname[256]; // 保存输入输出文件名
		// 输入所选择操作类型的数字代号：1：压缩，2：解压，3：退出
		cout << "请选择操作：\n 1：压缩\n 2：解压\n 3：退出\n";
		cin >> opt;
		if (opt == 3)
			break;
		else {
			cout << "输入文件名：";
			cin >> ifname;
			cout << "输出文件名：";
			cin >> ofname;
		}
		switch (opt) {
		case 1:
			cout << "压缩中……\n";
			flag = compress(ifname, ofname); // 压缩，返回值用于判断是否文件名不存在
			break;
		case 2:
			cout << "解压中……\n";
			flag = extract(ifname, ofname); // 解压，返回值用于判断是否文件名不存在
			break;
		}
		if (flag == -1)
			cout << "输入的文件不存在！\n"; // 如果标志为‘-1’则输入文件不存在
		else
			cout << "成功！\n";
	}
	return 0;
}