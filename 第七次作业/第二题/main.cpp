#include <iostream>
using namespace std;
#include "huffman.h"

int main()
{
	while (1) {
		int opt, flag = 0; // ��ʼ��flagΪ0
		char ifname[256], ofname[256]; // ������������ļ���
		// ������ѡ��������͵����ִ��ţ�1��ѹ����2����ѹ��3���˳�
		cout << "��ѡ�������\n 1��ѹ��\n 2����ѹ\n 3���˳�\n";
		cin >> opt;
		if (opt == 3)
			break;
		else {
			cout << "�����ļ�����";
			cin >> ifname;
			cout << "����ļ�����";
			cin >> ofname;
		}
		switch (opt) {
		case 1:
			cout << "ѹ���С���\n";
			flag = compress(ifname, ofname); // ѹ��������ֵ�����ж��Ƿ��ļ���������
			break;
		case 2:
			cout << "��ѹ�С���\n";
			flag = extract(ifname, ofname); // ��ѹ������ֵ�����ж��Ƿ��ļ���������
			break;
		}
		if (flag == -1)
			cout << "������ļ������ڣ�\n"; // �����־Ϊ��-1���������ļ�������
		else
			cout << "�ɹ���\n";
	}
	return 0;
}