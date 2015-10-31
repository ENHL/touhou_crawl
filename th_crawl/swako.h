//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: swako.h
//
// ����: ������ �Ǵ� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SWAKO_H__
#define  __SWAKO_H__



enum swako_1_power //�ž��� �����ʴ� ����� �Ǵɵ�
{
	SWAKO_1_JUMP=0, //����
	SWAKO_1_TEMPLE, //���������
	SWAKO_1_WATER_GUN, //����
	SWAKO_1_TONGUE, //������ ��
	SWAKO_1_LAST
};
enum swako_2_power //ȿ���� ���� �нú� �Ǵɵ�
{
	SWAKO_2_KILL_HP=0, //���϶� ü��ȸ��
	SWAKO_2_KILL_MP, //���϶� ����ȸ��
	SWAKO_2_KILL_POWER, //���϶� �Ŀ����
	SWAKO_2_SWIM, //�����Ѵ�. �����߿� �ɷ�ġ�� ���
	SWAKO_2_DEAD_PROTECT, //�������κ����� ��ȣ
	SWAKO_2_LAST
};

enum swako_3_power //�ž��� �Ҹ��ϴ� ����� �Ǵ�
{
	SWAKO_3_CURSE=0, //�����������(����,��)
	SWAKO_3_DIGGING, //����
	SWAKO_3_SUMMON_FLOG, //��������ȯ(������� ����)
	SWAKO_3_STATUE, //���� ���� �����������ȯ
	SWAKO_3_LAST
};

enum swako_4_power //������ �ش�
{
	SWAKO_4_COLD_RESIST=0, //�ñ�����
	SWAKO_4_FIRE_RESIST, //ȭ������
	SWAKO_4_AC, //�߰� AC
	SWAKO_4_CONFUSE_RESIST, //ȥ������
	SWAKO_4_POISON_RESIST, //������
	SWAKO_4_LAST
};

enum swako_5_power //�����Ǵ�
{
	SWAKO_5_RAIN=0, //�ֺ��� ���ٴٷ� �����. �Ʊ� �������� ��ȯ�ȴ�. 
	SWAKO_5_SLEEP, //����. ���� ������ ü�¸����� ���� ȸ���Ѵ�. 
	SWAKO_5_MISYAGUZI, //�̻��������� ��ȯ�Ѵ�. 
	SWAKO_5_SWAKO_HAT, //�����ڴ��� ���ڸ� �޴´�.(�ǵ����� �Ұ���)
	SWAKO_5_LAST
};

enum swako_string //���� ������ �ʿ��Ѱ�
{
	SWAKO_NAME=0, //�̸�
	SWAKO_SIMPLE_INFOR, //�ž�â���� �����ִ� ����
	SWAKO_GET_STRING, //�Ǵ��� ������� ����
	SWAKO_UNGET_STRING, //�Ǵ��� ��������� ����
	SWAKO_STRING
};


const char* GetSwakoString1(swako_1_power power, swako_string kind);
const char* GetSwakoString2(swako_2_power power, swako_string kind);
const char* GetSwakoString3(swako_3_power power, swako_string kind);
const char* GetSwakoString4(swako_4_power power, swako_string kind);
const char* GetSwakoString5(swako_5_power power, swako_string kind);


bool GetSwakoAbility(int level, bool plus);

#endif // __SWAKO_H__