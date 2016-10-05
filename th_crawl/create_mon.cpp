//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: create_mon.cpp
//
// ����: �ʿ� �´� ���ͱ׷��� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_infor.h"
#include "environment.h"
#include "event.h"


void create_id_to_mon(int id, int level);
int get_unique_to_id(int m_id);
void create_id_to_unique(int id, int level);
vector<unique_infor> unique_list;

struct mon_group
{
	int id; //������ȣ <- ������ȣ
	int min_level; //�ּҷ��� <- ������ ���� ��
	int max_level; //�ִ뷹�� <- ������ ���� ��
	int percent; //Ȯ��  <- ���� �󵵸� �����Ѵ�.
	int strong; //������ ���̵�  (10�� �⺻) <- ���� ���̳� ���� ���� �ʹ� ���� �������� ����

};
mon_group normal_group[] = //�Ϲݸ� �׷�
{
	{  0,  0,  4,  30,  1}, //��� 1
	{  1,  0,  4,  30,  1}, //�� 1
	{  2,  0,  3,  8,  2}, //���̹����� 1
	{  3,  0,  2,  30,  1}, //�ʷϿ��� 1
	//{  4,  0,  4,  20,  3}, //��� 3
	{  6,  0,  1,  10,  3}, //�Ķ����� 1
	{  7,  0,  2,  10,  2}, //�ʷϿ��� 2~3
	
	{  5,  1,  2,  2,  3}, //�������� 1
	{ 23,  1,  5,  5,  3}, //�ݵ�����
	{  8,  1,  4,  10,  3}, //�Ź� 1
	{  9,  1,  5,  10,  5}, //�� 1
	{ 11,  1,  4,  12,  3}, //�ʷϿ���1 �Ķ�����1
	{ 12,  1,  5,  12,  3}, //�ʷϿ���1 ��������1
	//{ 13,  1,  5,  40,  3}, //���2 ���4
	//{ 14,  1,  3,  8,  5}, //ı��2~3 (���� �ʹ� �꼭 ����)
	{ 24,  1,  4,  5,  5}, //�ΰ��δ�(����)
	{ 27,  1,  14,  8,  5}, //���䱫
	{ 28,  1,  5,  5,  5}, //�ʷϸ��
	
	{ 15,  2,  9,  20,  5}, //�ʷϿ���2 �Ķ�����1 ��������1
	{ 14,  2,  3,  8,  5}, //ı��2~3
	{ 18,  2,  6,  25,  6}, //ı��4~5
	{ 20,  2,  9,  10,  7}, //�Ź�1 ��1
	{ 10,  2,  11,  10,  6}, //�η�� 1
	{ 24,  2,  4,  5,  5}, //�ΰ��δ�(����)
	{ 29,  2,  7,  5,  5}, //��Ȳ���
	{ 28,  2,  5,  10,  5}, //�ʷϸ��

	
	{ 10,  3,  14,  3,  6}, //�η�� 1
	{ 4,   3,  7,  10 , 3}, //���3
	{ 16,  3,  9,  10,  6}, //�Ķ�����2 ��������2
	{ 25,  3,  6,  7, 10}, //�ΰ��δ�(�߰�)
	{ 30,  3,  9,  5,  5}, //ȸ�����

	
	{ 25,  4,  6,  20, 10}, //�ΰ��δ�(�߰�)
	{ 29,  4,  7,  10,  5}, //��Ȳ���

	
	{ 21,  5,  11,  10,  8}, //���� ������ ȣ���δ�
	{ 35,  5,  14,  5, 10}, //����������
	{ 30,  5,  9,  10,  5}, //ȸ�����

	
	{ 22,  6,  12,  10, 13}, //��� ���� ȣ���δ�
	{ 32,  6,  14,  15, 10}, //�����
	
	{ 31,  7,  14,  20, 10}, //������
	{ 26,  7,  14,  30, 20}, //�ΰ��δ�(����)
	{ 33,  7,  14,  15, 15}, //����ٱ�
	{ 38,  7,  14,  8, 10}, //�߸�����


	{ 34,  9,  14,  5, 30}, //����
	{ 39,  9,  14,  5, 15}, //ı��â���δ�
	{ 36,  9,  14,  5, 10}, //Ű���̸���

	{ 37,  10,  14,  5, 30}, //���и��� ����
	{ 53,  10,  14,  5, 30}, //��	
	{ 54,  10,  14,  5, 30}, //ȣ����

	
	{ 58,  11,  14,  5, 30}, //����� 1��
	{ 34,  11,  14,  5, 30}, //����
	{ 42,  11,  14,  10, 30}, //�ٱ��δ�


	{ 43,  12,  14,  5, 30}, //�ƿ�����
	{ 55,  12,  14,  5, 30}, //����
	
	{ 56,  13,  14,  5, 30}, //��

	
	//YOUKAI_MOUNTAIN_LEVEL

	
	
	{ 15,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+3,  8,  5}, //�ʷϿ���2 �Ķ�����1 ��������1
	{ 21,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+4,  10,  8}, //���� ������ ȣ���δ�
	{ 22,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+4,  10, 13}, //��� ���� ȣ���δ�
	{  3,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+1,  1,  1}, //�ʷϿ��� 1
	{  5,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+1,  1,  3}, //�������� 1
	{  6,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  1,  3}, //�Ķ����� 1
	{  7,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  1,  2}, //�ʷϿ��� 2~3
	{  0,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  1,  1}, //��� 1
	{ 29,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  2,  5}, //��Ȳ���
	{ 28,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+3,  2,  5}, //�ʷϸ��
	{ 30,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+3,  2,  5}, //ȸ�����
	
	{ 21,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  5,  8}, //���� ������ ȣ���δ�
	{ 22,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  8, 13}, //��� ���� ȣ���δ�
	{ 14,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  2,  5}, //ı��2~3
	{ 17,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4, 2,  5}, //ı��â��
	{ 31,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  7, 10}, //������
	{ 94,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  7, 15}, //�����䱫
		
	{ 22,  MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4, 5, 13}, //��� ���� ȣ���δ�
	{ 65,  MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4, 2, 20}, //���������δ�
	
	{ 63,  MISTY_LAKE_LEVEL+3,  MISTY_LAKE_LEVEL+4, 5, 13}, //ū�β���

	{ 66,  MISTY_LAKE_LEVEL+3,  MISTY_LAKE_LEVEL+4, 2, 20}, //�����Ҽ���
	{ 67,  MISTY_LAKE_LEVEL+3,  MISTY_LAKE_LEVEL+4, 2, 25}, //�����عٶ��

	//YOUKAI_MOUNTAIN_LEVEL

	{ 18,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+2, 15,  6}, //ı��4~5
	{ 31,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+2,  7, 10}, //������
	{ 17,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+1, 10,  5}, //ı��â��
	{ 19,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+1,  7, 10}, //ı��1~3 ı�ļ�����
	{ 33,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+3,  3, 15}, //����ٱ�
	{ 39,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+2,  2, 15}, //ı��â���δ�
	{ 36,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+3,  1, 10}, //Ű���̸���

	{ 17,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+2,  5, 10}, //ı��â�� 
	{ 33,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+3,  3, 15}, //����ٱ�
	{ 39,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //ı��â���δ�
	{ 44,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 20}, //ı�� â ���� ����Ʈ�δ�
	{ 57,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+3,  1, 25}, //�߸��ͷ� �δ�


	{ 33,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //����ٱ�
	{ 39,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //ı��â���δ�
	{ 44,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 20}, //ı�� â ���� ����Ʈ�δ�
	{ 40,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //�߸��ν��ٱ�
	{ 41,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 20}, //�ϳ�Ÿī�ٱ�
	{ 36,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  3, 10}, //Ű���̸���
	{ 42,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  10, 30}, //�ٱ��δ�
	//{ 45,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+4,  10, 30}, //����ٱ�
	{ 57,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3, 2, 25}, //�߸��ͷ� �δ�

	 
	{ 40,  YOUKAI_MOUNTAIN_LEVEL+3,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //�߸��ν��ٱ�
	{ 41,  YOUKAI_MOUNTAIN_LEVEL+3,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 20}, //�ϳ�Ÿī�ٱ�
	{ 61,  YOUKAI_MOUNTAIN_LEVEL+3,  YOUKAI_MOUNTAIN_LEVEL+3,  2, 30}, //������������
	{ 57,  YOUKAI_MOUNTAIN_LEVEL+3,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 25}, //�߸��ͷ� �δ�


	
	//SCARLET_LEVEL
	{ 51,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 15,  6}, //���̵����3~4
	{ 48,  SCARLET_LEVEL,  SCARLET_LEVEL+2, 15,  16}, //ȩ��� �Һδ� 
	{ 49,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 5,  16}, //ȩ��� ���̵�2��
	{ 50,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 1,  16}, //ȩ��� ����
	
	{ 48,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 5,  16}, //ȩ��� �Һδ� 
	{ 50,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 3,  16}, //ȩ��� ����
	{ 47,  SCARLET_LEVEL+1,  SCARLET_LEVEL+3, 3,  20}, //����å
	{ 52,  SCARLET_LEVEL+1,  SCARLET_LEVEL+3, 1,  30}, //����ī���
	{ 62,  SCARLET_LEVEL+1,  SCARLET_LEVEL+3, 1,  20}, //��������
	
	{ 48,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 5,  16}, //ȩ��� �Һδ� 
	{ 49,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 5,  16}, //ȩ��� ���̵�2��
	{ 50,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 5,  16}, //ȩ��� ����
	{ 47,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 5,  20}, //����å
	{ 37,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 3,  30}, //���и��� ����
	{ 60,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 3,  30}, //ȩ��� �Ǹ�����
	
	{ 52,  SCARLET_LEVEL+3,  SCARLET_LEVEL+3, 5,  30}, //����ī���
	
	{ 47,  SCARLET_LIBRARY_LEVEL,  SCARLET_LIBRARY_LEVEL, 5,  20}, //�������� ����å
	

	//������
	{ 95,  EIENTEI_LEVEL,  EIENTEI_LEVEL, 10,  30}, //�䳢��



	//������
	{ 2,  YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL-1, 2,  1}, //���̹�����
	{ 35, YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL-1, 2, 2}, //����������
	{ 36, YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL, 10, 2}, //Ű���̸���
	{ 37, YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL, 10, 2}, //���и�������
	{ 97, YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL, 10, 2}, //�����ٸ���
	{ 98, YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL, 10, 2}, //������칫



	//���±�
	{ 68,  DEPTH_LEVEL,  DEPTH_LEVEL+2, 10,  28}, //������δ�
	{ 64,  DEPTH_LEVEL,  DEPTH_LEVEL+3, 10,  25}, //����3����
	{ 86,  DEPTH_LEVEL,  DEPTH_LEVEL+3, 10,  20}, //�ʱ���
	{ 83,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  25}, //����
	{ 84,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  25}, //������
	{ 87,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  25}, //����䱫
	{ 34,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  30}, //����
	{ 43,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  30}, //�ƿ�����
	{ 56,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  35}, //��
	{ 59,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  35}, //�����

	
	//���� ����
	{ 73,  DREAM_LEVEL,  DREAM_LEVEL, 10,  35}, //��
	{ 74,  DREAM_LEVEL,  DREAM_LEVEL, 10,  35}, //�Ǹ�
	{ 75,  DREAM_LEVEL,  DREAM_LEVEL, 10,  35}, //����
	{ 59,  DREAM_LEVEL,  DREAM_LEVEL, 10,  35}, //�����
	{ 69,  DREAM_LEVEL,  DREAM_LEVEL, 10,  35}, //���䳢 ������
	{ 70,  DREAM_LEVEL,  DREAM_LEVEL, 10,  35}, //���䳢 ô�ĺ�
	//�Ʒ��� ����� Ȯ���� ������
	{ 89,  DREAM_LEVEL,  DREAM_LEVEL, 2,  35}, //������
	{ 68,  DREAM_LEVEL,  DREAM_LEVEL, 2,  35}, //������
	{ 83,  DREAM_LEVEL,  DREAM_LEVEL, 2,  35}, //����
	{ 95,  DREAM_LEVEL,  DREAM_LEVEL, 2,  30}, //�䳢��
	{ 42,  DREAM_LEVEL,  DREAM_LEVEL, 2, 30}, //�ٱ��δ�




	//���� ����
	{ 75,  MOON_LEVEL,  MOON_LEVEL, 10,  35}, //����
	{ 69,  MOON_LEVEL,  MOON_LEVEL, 10,  35}, //���䳢 ������
	{ 70,  MOON_LEVEL,  MOON_LEVEL, 10,  35}, //���䳢 ô�ĺ�
	{ 72,  MOON_LEVEL,  MOON_LEVEL, 10,  35}, //���䳢 ����Ʈ
	
	//����
	{ 87,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL+2, 10,  30}, //����䱫
	{ 68,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL+3, 10,  28}, //������δ�
	{ 62,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL+3, 10,  20}, //��������
	{ 60,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL+4, 2,  30}, //ȩ��� �Ǹ�����
	{ 76,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL_LAST_LEVEL-1, 10,  30}, //���ɶ�
	{ 78,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL_LAST_LEVEL-1, 10,  30}, //��ġ����
	{ 34,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL_LAST_LEVEL-1, 10,  30}, //����

	{ 79,  SUBTERRANEAN_LEVEL+1,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 10,  30}, //�ͺ�����
	{ 43,  SUBTERRANEAN_LEVEL+1,  SUBTERRANEAN_LEVEL_LAST_LEVEL-1, 10,  30}, //�ƿ�����
	{ 32,  SUBTERRANEAN_LEVEL+1,  SUBTERRANEAN_LEVEL+4, 7,  30}, //�����

	{ 80,  SUBTERRANEAN_LEVEL+2,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 10,  30}, //������

	{ 77,  SUBTERRANEAN_LEVEL+3,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 3,  30}, //ȭ��
	{ 34,  SUBTERRANEAN_LEVEL+3,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 5,  30}, //����
	{ 43,  SUBTERRANEAN_LEVEL+3,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 5,  30}, //�ƿ�����

	{ 85,  SUBTERRANEAN_LEVEL+4,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 10,  30}, //�������	
	
	{ 76,  SUBTERRANEAN_LEVEL_LAST_LEVEL,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 5,  30}, //���ɶ�
	{ 85,  SUBTERRANEAN_LEVEL_LAST_LEVEL,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 10,  30}, //�������
	{ 77,  SUBTERRANEAN_LEVEL_LAST_LEVEL,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 10,  30}, //ȭ��
	
	//�ǵ���Ͼ�
	{ 89,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 50,  35}, //3Ƽ���+����
	{ 90,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 6,  35}, //���ո���
	{ 91,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 7,  35}, //��Ű
	{ 92,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 7,  35}, //����
	{ 93,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 6,  35}, //�縮��
	{ 74,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 4,  35}, //�Ǹ�
	{ 79,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 4,  35}, //�Ǻ�����
	

	//���� (����� ���� ���̰� ����?
	{ 89,  PANDEMONIUM_LEVEL+1,  PANDEMONIUM_LEVEL+1, 60,  35}, //3Ƽ���+����
	{ 93,  PANDEMONIUM_LEVEL+1,  PANDEMONIUM_LEVEL+1, 10,  35}, //�縮��
	{ 59,  PANDEMONIUM_LEVEL+1,  PANDEMONIUM_LEVEL+1, 10,  35}, //�����
	{ 74,  PANDEMONIUM_LEVEL+1,  PANDEMONIUM_LEVEL+1, 5,  35}, //�Ǹ�
	{ 79,  PANDEMONIUM_LEVEL+1,  PANDEMONIUM_LEVEL+1, 5,  35}, //�Ǻ�����

	//��������	
	{ 99,  PANDEMONIUM_LEVEL+2,  PANDEMONIUM_LEVEL+2, 70,  35}, //�������� ������ ��������
	{ 92,  PANDEMONIUM_LEVEL+2,  PANDEMONIUM_LEVEL+2, 15,  35}, //����
	{ 83,  PANDEMONIUM_LEVEL+2,  PANDEMONIUM_LEVEL+2, 6,  35}, //����
	{ 74,  PANDEMONIUM_LEVEL+2,  PANDEMONIUM_LEVEL+2, 3,  35}, //�Ǹ�

	//�ǵ���Ͼ�
	{ 89,  PANDEMONIUM_LEVEL+3,  PANDEMONIUM_LEVEL+3, 60,  35}, //3Ƽ���+����
	{ 91,  PANDEMONIUM_LEVEL+3,  PANDEMONIUM_LEVEL+3, 5,  35}, //��Ű
	{ 92,  PANDEMONIUM_LEVEL+3,  PANDEMONIUM_LEVEL+3, 15,  35}, //����

	//������ �Ż�
	{ 56,  HAKUREI_LEVEL,  HAKUREI_LAST_LEVEL, 10,  35}, //��
	{ 81,  HAKUREI_LEVEL,  HAKUREI_LAST_LEVEL, 10,  35}, //�ö�� ����
	{ 96,  HAKUREI_LEVEL,  HAKUREI_LAST_LEVEL, 10,  30}, //�����аŸ�
	{ 86,  HAKUREI_LEVEL,  HAKUREI_LAST_LEVEL, 5,  20}, //�ʱ���
	//{ 90,  HAKUREI_LEVEL+1,  HAKUREI_LAST_LEVEL, 3,  35}, //���ո���
	{ 83,  HAKUREI_LEVEL+1,  HAKUREI_LAST_LEVEL, 5,  35}, //����
	{ 77,  HAKUREI_LEVEL+2,  HAKUREI_LAST_LEVEL, 10,  35}, //ȭ��
	{ 82,  HAKUREI_LEVEL+3,  HAKUREI_LAST_LEVEL, 10,  35}, //�̺� ����
	//{ 88, HAKUREI_LAST_LEVEL,  HAKUREI_LAST_LEVEL, 10,  35}, //�����

	{ -1,  0,  0,  0,  0} //�迭�� ��
};


mon_group unigue_group[] = //���ӵ�� �׷� Ȯ���� 100�� �ְ�
{
	{  0,  1,  3,  35,  1}, //��̾�
	{  6,  1,  3,  35,  1}, //Ű����
	{  11,  1,  6,  5,  2}, //���׹�Ʈ
	{  1,  2,  4,  35,  1}, //����
	{  9,  2,  4,  35,  2}, //�����
	{  10, 2,  4,  30,  2}, //����
	{  8,  3,  5,  35,  2}, //�ڰ���
	{  2,  4,  6,  35,  2}, //�̽�Ƽ��
	{  7,  6,  9,  35,  3}, //þ
	{  44,  6,  9,  30,  3}, //���̶�
	{  5,  7,  8,  35,  2}, //�����
	{  16,  7,  11,  15,  3}, //���
	{  3,  8,  10,  35,  3}, //ġ����
	{  4,  8,  12,  20,  3}, //�޵�
	
	{  15,  9,  14,  15,  3}, //�߸���
	{  17,  9,  14,  15,  3}, //���ī
	{  18,  9,  14,  15,  3}, //��Ű��Ű
	{  20,  9,  14,  15,  3}, //ī�Է�
	{  21,  9,  14,  10,  3}, //�ĸ���
	{  22,  9,  14,  20,  3}, //�����
	{  31,  9,  14,  25,  3}, //���̽�
	{  49,  9,  14,  15,  3}, //å�д¿䱫(��Ű��)
	{  35,  11,  14,  15,  3}, //Ŭ����ǽ�
	{  37,  11,  14,  15,  3}, //��Ƽ

	//�Ȱ�ȣ��
	{  9, MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  40,  2}, //�����
	{  14,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+3,  40,  2}, //����
	{  5, MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  40,  2}, //�����
	{  3, MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4,  40,  3}, //ġ����
	{  21,  MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4,  10,  3}, //�ĸ���
	{  18,  MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4,  15,  2}, //��Ű��Ű
	{  49,  MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4,  15,  2}, //å�д¿䱫(��Ű��)
	{  18,  MISTY_LAKE_LEVEL+3,  MISTY_LAKE_LEVEL+4,  15,  2}, //��Ű��Ű
	
	{  12,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+3,  60,  4}, //�����
	{  22,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+3, 20,  3}, //�����
	{  16,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+3,  20,  3}, //���
	//{  13,  YOUKAI_MOUNTAIN_LEVEL+4,  YOUKAI_MOUNTAIN_LEVEL+4,  100,  5}, //�ƾ�(����������� ��Ʈ�� ����)
	{  21,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+3,  10,  3}, //�ĸ���
	//{  19,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+2,  30,  3}, //���丮(����������� ��Ʈ�� ����)

	
	{  21,  SCARLET_LEVEL+1,  SCARLET_LEVEL+3,  10,  3}, //�ĸ���
	//{  25,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3,  40,  4}, //����(�Ƹ� ��Ʈ����)
	{  26,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3,  50,  3}, //�ҾǸ�
	//{  27,  MISTY_LAKE_LEVEL+3,  MISTY_LAKE_LEVEL+4,  60,  4}, //���̸�(�Ƹ� ��Ʈ����)
	{  28,  SCARLET_LEVEL+3,  SCARLET_LEVEL+4,  50,  4}, //�����
	//{  29,  SCARLET_LEVEL+4,  SCARLET_LEVEL+4,  60,  5}, //���и��� �Ƹ� ��Ʈ ����
	
	

	{ 18,  YUKKURI_LEVEL, YUKKURI_LAST_LEVEL-1, 20,  28}, //��Ű��Ű
	{  21,  YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL-1,  5,  3}, //�ĸ���

	
	{ 23,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL, 30,  3}, //����
	{ 32,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL, 30,  28}, //����
	{ 35,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL, 30,  28}, //Ŭ����ǽ�
	{ 21,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL,  10,  3}, //�ĸ���
	{ 24,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL,  30,  3}, //��ġ��
	{ 37,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL,  15,  3}, //��Ƽ
	{ 43,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL,  30,  3}, //�ٸ���
	
	{ 6,  SUBTERRANEAN_LEVEL, SUBTERRANEAN_LEVEL+1, 20,  28}, //Ű���� 
	{ 15,  SUBTERRANEAN_LEVEL, SUBTERRANEAN_LEVEL+2, 20,  28}, //�߸��� 
	{ 21,  SUBTERRANEAN_LEVEL, SUBTERRANEAN_LEVEL+3, 20,  28}, //�ĸ��� 
	{ 23,  SUBTERRANEAN_LEVEL, SUBTERRANEAN_LEVEL+5, 30,  28}, //����

	{ 37,  HAKUREI_LEVEL,  HAKUREI_LAST_LEVEL-1,  30,  3}, //����ī

	{ -1,  0,  0,  0,  0} //�迭�� ��
};


void init_monster()
{
	int i=0;
	while(unigue_group[i].id != -1)
	{
		if(randA_1(100)<=unigue_group[i].percent)
		{
			int f_id_ = unigue_group[i].id;
			auto it = find_if(unique_list.begin(),unique_list.end(),
				[f_id_](unique_infor &v)->bool{
					return v.id == f_id_;
				}
				);

			if(it != unique_list.end())
			{
				if(randA(1))
				{
					unique_list.erase(it);
					unique_list.push_back(unique_infor(unigue_group[i].id,rand_int(unigue_group[i].min_level,unigue_group[i].max_level)));
				}
			}
			else	
				unique_list.push_back(unique_infor(unigue_group[i].id,rand_int(unigue_group[i].min_level,unigue_group[i].max_level)));

		}
		i++;
	}

}



bool is_exist_named(monster_index m_id_) //�ش� ���ӵ尡 ����Ȯ���Ǿ��ִ���
{		
	int id_ = get_unique_to_id(m_id_);

	auto it = find_if(unique_list.begin(),unique_list.end(),
		[id_](unique_infor &v)->bool{
			return v.id == id_;
		}
	);
	return it != unique_list.end();
}
void set_exist_named(monster_index m_id_) //���ӵ带 ����Ȯ��(��Ʈ������)
{
	for(auto it = unique_list.begin();  it !=  unique_list.end(); it++)
	{ //������ ������ ����������.
		if(it->id == get_unique_to_id(m_id_))
		{
			unique_list.erase(it);
			break;
		}
	}
	int id_ = get_unique_to_id(m_id_);
	unique_list.push_back(unique_infor(id_,-1));
}
void unset_exist_named(monster_index m_id_) //���ӵ带 �ٽ� ������ �� �ִ� ���·�
{
	for(auto it = unique_list.begin();  it !=  unique_list.end(); it++)
	{ //������ ������ ����������.
		if(it->id == get_unique_to_id(m_id_))
		{
			unique_list.erase(it);
			break;
		}
	}
}





void create_mon(int floor, int num_)
{
	if(num_ == 0)
		return;

	int i = 0, total=0, num = num_?num_:10;
	vector<mon_group*> group;
	group.reserve(128);
	while(normal_group[i].id != -1)
	{
		if(normal_group[i].min_level<=floor && normal_group[i].max_level>=floor)
		{
			group.push_back(&normal_group[i]);
			total+=normal_group[i].percent;
		}
		else if(normal_group[i].min_level > floor)
			break;
		i++;
	}

	for(int i = 0; i<num; i++)
	{
		int rand_ = randA_1(total);
		vector<mon_group*>::iterator it;
		for(it = group.begin(); it != group.end(); it++)
		{
			if(rand_<=(*it)->percent)
			{
				create_id_to_mon((*it)->id, floor);
				break;
			}
			else
				rand_ -= (*it)->percent;	
	
		}
	}

	for(vector<unique_infor>::iterator it = unique_list.begin();it!=unique_list.end();it++)
	{
		if(it->level == floor)
		{
			create_id_to_unique(it->id, floor);

		}
	}
}


void Set_X_Y(int &x_, int x, int rand_x, int &y_, int y, int rand_y)
{
	x_= x+rand_x;
	y_= y+rand_y;
	if(x_<0)
		x_=0;
	else if(x_>=DG_MAX_X)
		x = DG_MAX_X-1;
	if(y_<0)
		y_=0;
	else if(y_>=DG_MAX_Y)
		y_ = DG_MAX_Y-1;
}




void create_id_to_mon(int id, int level)
{
	vector<monster_index> index;

	switch(id)
	{
	case 0:
		index.push_back(MON_MOOK);
		break;
	case 1:
		index.push_back(MON_RAT);
		break;
	case 2:
		index.push_back(MON_REIMUYUKKURI);
		break;
	case 3:
		index.push_back(MON_FAIRY_GREEN);
		break;
	case 4:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_CROW);
		break;
	case 5:
		index.push_back(MON_FAIRY_RED);
		break;
	case 6:
		index.push_back(MON_FAIRY_BLUE);
		break;
	case 7:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_FAIRY_GREEN);
		break;
	case 8:
		index.push_back(MON_SPIDER);
		break;
	case 9:
		index.push_back(MON_SNAKE);
		break;
	case 10:
		index.push_back(MON_CRANE);
		break;
	case 11:
		index.push_back(MON_FAIRY_BLUE);
		index.push_back(MON_FAIRY_GREEN);
		break;
	case 12:
		index.push_back(MON_FAIRY_RED);
		index.push_back(MON_FAIRY_GREEN);
		break;
	case 13:
		//index.push_back(MON_MOOK);
		//index.push_back(MON_MOOK);
		//index.push_back(MON_CROW);
		//index.push_back(MON_CROW);
		//index.push_back(MON_CROW);
		//index.push_back(MON_CROW);
		break;
	case 14:
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		break;
	case 15:
		index.push_back(MON_FAIRY_RED);
		index.push_back(MON_FAIRY_BLUE);
		index.push_back(MON_FAIRY_GREEN);
		index.push_back(MON_FAIRY_GREEN);
		break;
	case 16:
		index.push_back(MON_FAIRY_RED);
		index.push_back(MON_FAIRY_RED);
		index.push_back(MON_FAIRY_BLUE);
		index.push_back(MON_FAIRY_BLUE);
		break;
	case 17:
		//����־�
		/*index.push_back(MON_KATPA);
		index.push_back(MON_KATPA);*/
		index.push_back(MON_KATPA_SPEAR);
		break;
	case 18:
		for(int rand_ =rand_int(3,4), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		break;
	case 19:
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		index.push_back(MON_KATPA_WATER_WIZARD);
		/*for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back((monster_index)rand_int(MON_FAIRY_GREEN_WARRIOR,MON_FAIRY_RED_COMMANDER));*/
		
		break;
	case 20:
		index.push_back(MON_SPIDER);
		index.push_back(MON_SNAKE);
		break;
	case 21:
		for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
			index.push_back(randA(2)?MON_FAIRY_GREEN:randA(1)?MON_FAIRY_BLUE:MON_FAIRY_RED);
		for(int rand_ = randA(3)?1:2, i=0;i<rand_;i++)
			index.push_back(randA(2)?MON_FAIRY_GREEN_WARRIOR:MON_FAIRY_BLUE_MAGICIAN);
		break;
	case 22:
		for(int rand_ =rand_int(0,2), i=0;i<rand_;i++)
			index.push_back(randA(2)?MON_FAIRY_GREEN:randA(1)?MON_FAIRY_BLUE:MON_FAIRY_RED);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_FAIRY_GREEN_WARRIOR:MON_FAIRY_BLUE_MAGICIAN);
		index.push_back(MON_FAIRY_RED_COMMANDER);
		break;
	case 23:
		index.push_back(MON_FIREFLY);
		break;
	case 24:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_HUMAM_MAN);
		break;
	case 25:
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(MON_HUMAM_MAN);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_HUMAM_PRIEST:MON_HUMAM_YINYANG);
		if(randA(4)<1)
			index.push_back(MON_HUMAM_SAMURI);
		break;
	case 26:
		for(int rand_ = rand_int(0,2), i=0;i<rand_;i++)
			index.push_back(MON_HUMAM_MAN);
		index.push_back(MON_HUMAM_PRIEST);
		index.push_back(MON_HUMAM_YINYANG);
		index.push_back(randA(1)?MON_HUMAM_PRIEST:MON_HUMAM_YINYANG);
		index.push_back(MON_HUMAM_SAMURI);
		break;
	case 27:
		index.push_back(MON_BAKEKASA);
		break;
	case 28:
		index.push_back(MON_GREEN_MOOK);
		break;
	case 29:
		index.push_back(MON_ORANGE_MOOK);
		break;
	case 30:
		index.push_back(MON_GRAY_MOOK);
		break;
	case 31:
		index.push_back(MON_FROG);
		break;
	case 32:
		index.push_back(randA(2)?(randA(1)?MON_ORANGE_CAT:MON_WHITE_CAT):MON_BLACK_CAT);
		break;
	case 33:
		index.push_back(MON_CROW_TENGU);
		break;
	case 34:
		index.push_back(MON_ONI);
		break;
	case 35:
		index.push_back(MON_MARISAYUKKURI);
		break;
	case 36:
		index.push_back(MON_AYAYUKKURI);
		break;
	case 37:
		index.push_back(MON_REMILIAYUKKURI);
		break;
	case 38:
		index.push_back(MON_YAMABIKO);
		break;
	case 39:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		index.push_back(MON_KATPA_WATER_WIZARD);
		index.push_back(MON_KATPA_SPEAR);
		break;
	case 40:
		index.push_back(MON_YAMABUSH_TENGU);
		break;
	case 41:
		index.push_back(MON_HANATACA_TENGU);
		break;
	case 42:
		for(int rand_ =rand_int(0,2), i=0;i<rand_;i++)
			index.push_back(MON_CROW);
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(MON_CROW_TENGU);
		index.push_back(MON_YAMABUSH_TENGU);
		break;
	case 43:
		index.push_back(MON_BLUE_ONI);
		break;
	case 44:
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(MON_KATPA_SPEAR);
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(MON_KATPA_WATER_WIZARD);
		break;
	case 45:
		index.push_back(MON_WOLF_TENGU);
		break;
		
	case 46:	
		for(int rand_ =rand_int(1,4), i=0;i<rand_;i++)
			index.push_back(MON_ZOMBIE_FAIRY);
		break;			
	case 47:
		//����å�� ������ �����־���ϹǷ� ����
		index.push_back(MON_MAGIC_BOOK);
		break;		
	case 48:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_HOBGOBRIN);
		if(randA(2)<1)
			index.push_back(MON_HOBGOBRIN_MAID);
		if(randA(4)<1)
			index.push_back(MON_HOBGOBRIN_LIBRARIAN);
		break;		
	case 49:
		index.push_back(MON_HOBGOBRIN_MAID);
		index.push_back(MON_HOBGOBRIN_MAID);
		break;	
	case 50:
		index.push_back(MON_HOBGOBRIN_LIBRARIAN);
		break;
	case 51:	
		for(int rand_ =rand_int(3,5), i=0;i<rand_;i++)
			index.push_back(MON_MAID_FAIRY);
		break;
	case 52:
		index.push_back(MON_CHUPARCABRA);
		break;
	case 53:
		index.push_back(MON_EAGLE);
		break;
	case 54:
		index.push_back(MON_TIGER);
		break;
	case 55:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_RAIJUU);
		break;
	case 56:
		index.push_back(MON_DRAGON_BABY);
		break;
	case 57:
		for(int rand_ =rand_int(1,5), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_YAMAWARO_NINJA:MON_YAMAWARO_WAWRRIOR);
		if(randA(3)<1)
			index.push_back(MON_YAMAWARO_FLAG);
		break;
	case 58:
		index.push_back(MON_RED_UFO);
		break;
	case 59:
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
		index.push_back(randA(2)?(randA(1)?MON_RED_UFO:MON_BLUE_UFO):MON_GREEN_UFO);
		break;
	case 60:
		index.push_back(MON_HOBGOBRIN_TEMP);
		break;
	case 61:
		index.push_back(MON_SANPEI_FIGHTER);
		break;
	case 62:
		for(int rand_ =rand_int(3,4), i=0;i<rand_;i++)
			index.push_back(MON_VAMPIER_BAT);
		break;
	case 63:
		index.push_back(MON_DEAGAMA);
		break;	
	case 64:
		index.push_back(MON_EAGLE);
		for(int rand_ =rand_int(0,1), i=0;i<rand_;i++)
			index.push_back(MON_TIGER);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_RAIJUU);
		break;
	case 65:		
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_FAIRY_GREEN:randA(1)?MON_FAIRY_BLUE:MON_FAIRY_RED);
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(randA(2)==0?MON_FAIRY_GREEN_WARRIOR:(randA(1)?MON_FAIRY_BLUE_MAGICIAN:MON_FAIRY_RED_COMMANDER));
		index.push_back(MON_FAIRY_HERO);
		break;
	case 66:
		index.push_back(MON_FAIRY_SOCERER);
		break;	
	case 67:		
		for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_FAIRY_GREEN:randA(1)?MON_FAIRY_BLUE:MON_FAIRY_RED);
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_FAIRY_GREEN_WARRIOR:MON_FAIRY_BLUE_MAGICIAN);
		index.push_back(MON_FAIRY_SUN_FLOWER);
		break;
	case 68:
		index.push_back(MON_FAIRY_HERO);
		index.push_back(MON_FAIRY_SOCERER);
		index.push_back(MON_FAIRY_SUN_FLOWER);
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_FAIRY_GREEN:randA(1)?MON_FAIRY_BLUE:MON_FAIRY_RED);
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(randA(2)==0?MON_FAIRY_GREEN_WARRIOR:(randA(1)?MON_FAIRY_BLUE_MAGICIAN:MON_FAIRY_RED_COMMANDER));
		break;	
	case 69:
		index.push_back(MON_MOON_RABIT_SUPPORT);
		break;
	case 70:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_MOON_RABIT_ATTACK);
		break;
	case 71:
		index.push_back(MON_MOON_RABIT_ELITE);
		break;		
	case 72:
		if(randA(3)==0)
			index.push_back(MON_MOON_RABIT_SUPPORT);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_MOON_RABIT_ATTACK);
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(MON_MOON_RABIT_ELITE);
		break;	
	case 73:
		index.push_back(MON_MAC);
		break;	
	case 74:
		index.push_back(MON_NIGHTMARE);
		break;	
	case 75:
		index.push_back(MON_LUNATIC);
		break;	
	case 76:
		for(int rand_ =rand_int(3,6), i=0;i<rand_;i++)
			index.push_back(MON_HAUNT);
		break;
	case 77:
		index.push_back(MON_FIRE_CAR);
		break;	
	case 78:
		index.push_back(MON_HELL_SPIDER);
		break;	
	case 79:
		index.push_back(MON_BLOOD_HAUNT);
		break;	
	case 80:
		index.push_back(MON_HELL_HOUND);
		if(randA(4)==0)
		{
			for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
				index.push_back(MON_HELL_HOUND);
		}
		break;	
	case 81:
		index.push_back(MON_FLOWER_TANK);
		break;	
	case 82:
		index.push_back(MON_EVIL_EYE_TANK);
		break;	
	case 83:
		index.push_back(MON_SNOW_GIRL);
		break;	
	case 84:
		index.push_back(MON_NAMAZ);
		break;	
	case 85:
		for(int rand_ =rand_int(3,6), i=0;i<rand_;i++)
			index.push_back(MON_HELL_CROW);
		break;	
	case 86:
		index.push_back(MON_RACCON);
		break;	
	case 87:
		index.push_back(MON_LANTERN_YOUKAI);
		break;
	case 88:
		index.push_back(MON_YINYAN);
		break;
	case 89:
		if(randA(2)==0)
		{
			for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
				index.push_back(MON_LITTLE_IMP);
		}
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(randA(2)==0?MON_SARA:randA(1)?MON_LUIZE:MON_ELIS);
		break;
	case 90:
		for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
			index.push_back(MON_EVIL_EYE);
		index.push_back(MON_YUUGENMAGAN);
		break;
	case 91:
		index.push_back(MON_YUKI);
		break;
	case 92:
		index.push_back(MON_MAI);
		break;
	case 93:
		index.push_back(MON_SARIEL);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(randA(2)==0?MON_SARA:randA(1)?MON_LUIZE:MON_ELIS);
		break;
	case 94:
		index.push_back(MON_MUSHROOM);
		break;
	case 95:
		for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
			index.push_back(randA(4)?MON_RABIT_SPEAR:randA(1)?MON_RABIT_MAGIC:MON_RABIT_BOMB);
		if(randA(3)==0)
		{
			index.push_back(MON_RABIT_SUPPORT);
		}
		break;
	case 96:
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_ONI:MON_BLUE_ONI);
		break;
	case 97:
		index.push_back(MON_ALICEYUKKURI);
		break;
	case 98:
		index.push_back(MON_YOUMUYUKKURI);
		break;
	case 99:
		if(randA(2)==0)
		{
			for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
				index.push_back(MON_LITTLE_IMP);
		}
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(randA(4)?MON_LUIZE:randA(1)?MON_SARA:MON_ELIS);
		break;
	}

	int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1),rand_x=0,rand_y=0, r=2+index.size()/3,k=0;
	for(vector<monster_index>::iterator it=index.begin();it!=index.end();it++)
	{ 
		int x_ = 0, y_ = 0;
		Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		while(!env[level].isMove(x_,y_) || (env[level].dgtile[x_][y_].flag & FLAG_NO_MONSTER) || env[level].isMonsterPos(x_,y_) || env[level].isStair(x_,y_))
		{
			if(it==index.begin())
			{
				x = randA(DG_MAX_X-1),y = randA(DG_MAX_Y-1);
			}
			else
			{
				rand_x=rand_int(-r,r);
				rand_y=rand_int(-r,r);
				if(++k%5 == 0)
				{
					r++;
				}
			}
			Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		}
		if(env[level].AddMonster((*it),0,coord_def(x_,y_)))
		{
			continue;
		}
		k = 0;
		r=2+index.size()/3;
		rand_x=rand_int(-r,r);
		rand_y=rand_int(-r,r);
	}
}	


int get_unique_to_id(int m_id)
{
	switch(m_id)
	{
	default: return -1;
	case MON_RUMIA:return 0;
	case MON_WRIGGLE: return 1;
	case MON_MISTIA: return 2;
	case MON_CIRNO: return 3;
	case MON_MEDICINE: return 4;
	case MON_DIEFAIRY: return 5;
	case MON_KISUME: return 6;
	case MON_CHEN: return 7;
	case MON_KOGASA: return 8;
	case MON_SUNNY:case MON_LUNAR:case MON_STAR: return 9;
	case MON_KYOUKO: return 10;
	case MON_FORTUNE_TELLER: return 11;
	case MON_MOMIZI: return 12;
	case MON_AYA: return 13;
	case MON_WAKASAGI: return 14;
	case MON_YAMAME: return 15;
	case MON_NAZRIN:case MON_DAUZING: return 16;
	case MON_YOSIKA: return 17;
	case MON_SEKIBANKI:
	case MON_SEKIBANKI_BODY:
	case MON_SEKIBANKI_HEAD: return 18;
	case MON_NITORI: return 19;
	case MON_KEGERO: return 20;
	case MON_PARSI: return 21;
	case MON_BENBEN:
	case MON_YATHASI: return 22;
	case MON_ORIN:
	case MON_ORIN_CAT: return 23;
	case MON_ICHIRIN:
	case MON_UNZAN:
	case MON_UNZAN_PUNCH: return 24;
	case MON_PACHU: return 25;
	case MON_KOAKUMA: return 26;
	case MON_MEIRIN: return 27;
	case MON_SAKUYA: return 28;
	case MON_REMILIA: return 29;
	case MON_KASEN: return 30;
	case MON_KOISHI: return 31;
	case MON_NUE: return 32;
	case MON_FLAN: 
	case MON_FLAN_BUNSIN: return 33;
	case MON_TEWI:  return 34;
	case MON_CLOWNPIECE:  return 35;
	case MON_DOREMI:  return 36;
	case MON_LETTY:  return 37;
	case MON_YORIHIME:  return 38;
	case MON_TOYOHIME:  return 39;
	case MON_UTSUHO:  return 40;
	case MON_SUIKA:  return 41;
	case MON_REIMU:  return 42;
	case MON_ALICE:  return 43;
	case MON_SEIRAN:  return 44;
	case MON_RINGO:  return 45;
	case MON_UDONGE:  return 46;
	case MON_KAGUYA:  return 47;
	case MON_MOKOU:  return 48;
	case MON_TOKIKO: return 49;
	case MON_TOZIKO: return 50;
	case MON_FUTO: return 51;
	case MON_MAMIZO: return 52;
	}
}




void create_id_to_unique(int id, int level)
{
	vector<monster_index> index;

	switch(id)
	{
	case 0:
		index.push_back(MON_RUMIA);
		break;
	case 1:
		index.push_back(MON_WRIGGLE);
		break;
	case 2:
		index.push_back(MON_MISTIA);
		break;
	case 3:
		index.push_back(MON_CIRNO);
		break;
	case 4:
		index.push_back(MON_MEDICINE);
		break;
	case 5:
		index.push_back(MON_DIEFAIRY);
		break;
	case 6:
		{
			int x_=randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
			while(!env[level].isMove(x_,y_) || (env[level].dgtile[x_][y_].flag & FLAG_NO_MONSTER) || env[level].isMonsterPos(x_,y_) || env[level].isStair(x_,y_))
			{
				x_=randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
			}			
			env[level].MakeEvent(EVL_KISME,coord_def(x_,y_),EVT_APPROACH_SMALL);
		}
		break;
	case 7:
		index.push_back(MON_CHEN);
		for(int i=0;i<4;i++)
			index.push_back(randA(2)?(randA(1)?MON_ORANGE_CAT:MON_WHITE_CAT):MON_BLACK_CAT);
		break;
	case 8:
		index.push_back(MON_KOGASA);
		break;
	case 9:
		index.push_back(MON_SUNNY);
		index.push_back(MON_LUNAR);
		index.push_back(MON_STAR);
		break;
	case 10:
		index.push_back(MON_KYOUKO);
		break;
	case 11:
		index.push_back(MON_FORTUNE_TELLER);
		break;
	case 12:
		index.push_back(MON_MOMIZI);
		break;
	case 13:
		index.push_back(MON_AYA);
		break;
			
	case 14:	
		index.push_back(MON_WAKASAGI);
		break;
	case 15:
		index.push_back(MON_YAMAME);
		break;
	case 16:
		index.push_back(MON_NAZRIN);
		if(randA(2)<1)
		{			
			for(int rand_ =rand_int(2,5), i=0;i<rand_;i++)
				index.push_back(MON_RAT);
		}
		break;
	case 17:
		index.push_back(MON_YOSIKA);
		break;
	case 18:
		index.push_back(MON_SEKIBANKI);
		break;
	case 19:
		index.push_back(MON_NITORI);
		if(randA(2)<1)
		{			
			index.push_back(MON_KATPA);
			index.push_back(MON_KATPA_SPEAR);
			index.push_back(MON_KATPA_WATER_WIZARD);
		}
		break;
	case 20:
		index.push_back(MON_KEGERO);
		break;		
	case 21:
		index.push_back(MON_PARSI);
		break;	
	case 22:
		index.push_back(MON_BENBEN);
		index.push_back(MON_YATHASI);
		break;
	case 23:
		index.push_back(MON_ORIN);
		for(int rand_ =rand_int(3,4), i=0;i<rand_;i++)
			index.push_back(MON_ZOMBIE_FAIRY);
		break;
	case 24:
		index.push_back(MON_ICHIRIN);
		break;	
	case 25:
		//ȫ���� ������ ���� ����
		index.push_back(MON_PACHU);
		break;	
	case 26:
		index.push_back(MON_KOAKUMA);
		break;	
	case 27:
		//�Ƹ� �� ��ȣ�� �Ⱦ�����? ���̸��� ȫ���� �Ա� ���� ����
		index.push_back(MON_MEIRIN);
		break;	
	case 28:
		index.push_back(MON_SAKUYA);
		break;	
	case 29:
		//���� ȫ���� �ֽ��� ��������(�����������)
		index.push_back(MON_REMILIA);
		break;		
	case 30:
		index.push_back(MON_KASEN);
		index.push_back(MON_EAGLE);
		index.push_back(MON_TIGER);
		index.push_back(MON_RAIJUU);
		index.push_back(MON_DRAGON_BABY);
		break;	
	case 31:
		if(randA(5)==0)
		{
			int x_=randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
			while(!env[level].isMove(x_,y_) || (env[level].dgtile[x_][y_].flag & FLAG_NO_MONSTER) || env[level].isMonsterPos(x_,y_) || env[level].isStair(x_,y_))
			{
				x_=randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
			}			
			env[level].MakeEvent(EVL_KOISHI,coord_def(x_,y_),EVT_APPROACH_SMALL);
		}
		else
			index.push_back(MON_KOISHI);
		break;
	case 32:
		index.push_back(MON_NUE);
		break;
	case 33:
		index.push_back(MON_FLAN);
		break;
	case 34:
		index.push_back(MON_TEWI);
		break;
	case 35:
		index.push_back(MON_CLOWNPIECE);
		break;
	case 36:
		index.push_back(MON_DOREMI);
		break;
	case 37:
		index.push_back(MON_LETTY);
		break;
	case 38: //���ǵ��� �������ӵ�
		index.push_back(MON_YORIHIME);
		break;
	case 39: //���ǵ��� �������ӵ�
		index.push_back(MON_TOYOHIME);
		break;
	case 40: //������ �������ӵ�
		index.push_back(MON_UTSUHO);
		break;
	case 41:
		index.push_back(MON_SUIKA);
		break;
	case 42: //��������
		index.push_back(MON_REIMU);
		break;
	case 43:
		index.push_back(MON_ALICE);
		break;
	case 44:
		index.push_back(MON_SEIRAN);
		break;
	case 45:
		index.push_back(MON_RINGO);
		break;
	case 46: //������ ����
		index.push_back(MON_UDONGE);
		break;
	case 47: //������ ����
		index.push_back(MON_KAGUYA);
		break;
	case 48:
		index.push_back(MON_MOKOU);
		break;
	case 49:
		index.push_back(MON_TOKIKO);
		break;
	case 50:
		index.push_back(MON_TOZIKO);
		break;
	case 51:
		index.push_back(MON_FUTO);
		break;
	case 52:
		index.push_back(MON_MAMIZO);
		break;
	}

	int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1),rand_x=0,rand_y=0, r=2+index.size()/3,k=0;
	for(vector<monster_index>::iterator it=index.begin();it!=index.end();it++)
	{ 
		int x_ = 0, y_ = 0, limit_ = 10000;
		Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		bool only_water = (mondata[(*it)].flag & M_FLAG_CANT_GROUND) && (mondata[(*it)].flag & M_FLAG_SWIM);
		while(!env[level].isMove(x_,y_,false, only_water, only_water) || 
			(env[level].dgtile[x_][y_].flag & FLAG_NO_MONSTER) || 
			env[level].isMonsterPos(x_,y_) || env[level].isStair(x_,y))
		{
			if(limit_--<0)
				break;
			if(it==index.begin())
			{
				x = randA(DG_MAX_X-1),y = randA(DG_MAX_Y-1);
			}
			else
			{
				rand_x=rand_int(-r,r);
				rand_y=rand_int(-r,r);
				if(++k%5 == 0)
				{
					r++;
				}
			}
			Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		}
		if(limit_<=0)
			continue;

			
		if(env[level].AddMonster((*it),0,coord_def(x_,y_)))
		{
			continue;
		}
		k = 0;
		r=2+index.size()/3;
		rand_x=rand_int(-r,r);
		rand_y=rand_int(-r,r);
	}
}


void SetResistMonster(monster* mon)
{
	mon->ice_resist = 0;
	mon->fire_resist = 0;
	mon->poison_resist=0;
	mon->elec_resist=0;
	switch(mon->id)
	{
	case MON_CIRNO:
		mon->ice_resist=3;
		mon->fire_resist=-1;
		break;
	case MON_MISTIA:
		mon->poison_resist=-1;
		mon->wind_resist=1;
		break;
	case MON_MEDICINE:
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_DIEFAIRY:
		mon->ice_resist=1;
		break;
	case MON_GHOST:
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_BAKEKASA:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_GREEN_MOOK:
		mon->poison_resist=1;
		break;
	case MON_KOGASA:
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_CROW_TENGU:
		mon->wind_resist=1;
		break;
	case MON_ONI:
		mon->fire_resist=1;
		break;
	case MON_REMILIAYUKKURI:
		mon->poison_resist=1;
		break;
	case MON_KATPA_WATER_WIZARD:
		mon->ice_resist=1;
		break;
	case MON_YAMABUSH_TENGU:
		mon->wind_resist=1;
		break;
	case MON_HANATACA_TENGU:
		mon->poison_resist=1;
		mon->wind_resist=1;
		break;
	case MON_BLUE_ONI:
		mon->ice_resist=1;
		break;
	case MON_MUSHROOM:
		mon->poison_resist=1;
		break;
	case MON_AYA:
		mon->wind_resist=1;
		break;
	case MON_WAKASAGI:
		mon->ice_resist=1;
		break;
	case MON_YAMAME:		
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_NAZRIN:
		mon->poison_resist=1;
		break;
	case MON_DAUZING:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_YOSIKA:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_SEKIBANKI:
	case MON_SEKIBANKI_BODY:
		mon->fire_resist=1;
		break;
	case MON_NITORI:
		mon->elec_resist=2;
		mon->ice_resist=2;
		break;
	case MON_BENBEN:
	case MON_YATHASI:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_ORIN:		
	case MON_ORIN_CAT:
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;
	case MON_ZOMBIE_FAIRY:
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_ICHIRIN:
		mon->fire_resist=1;
		mon->poison_resist=1;
		mon->elec_resist=1;
		break;
	case MON_UNZAN:
	case MON_UNZAN_PUNCH:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;
	case MON_PACHU:
		mon->elec_resist=2;
		mon->ice_resist=2;
		mon->fire_resist=2;
		mon->poison_resist=1;
		break;
	case MON_MAGIC_BOOK:
		mon->elec_resist=2;
		mon->ice_resist=2;
		mon->fire_resist=2;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_HOBGOBRIN_MAID:
		mon->poison_resist=1;
		break;
	case MON_HOBGOBRIN_LIBRARIAN:
		mon->ice_resist=1;
		mon->fire_resist=1;
		break;
	case MON_CHUPARCABRA:
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_KOAKUMA:
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_REMILIA:
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_RAIJUU:
		mon->elec_resist=3;
		mon->poison_resist=1;
		break;
	case MON_TIGER:
		mon->ice_resist=1;
		break;
	case MON_DRAGON_BABY:
		mon->fire_resist=2;
		mon->poison_resist=1;
		break;
	case MON_YAMAWARO_NINJA:
	case MON_YAMAWARO_WAWRRIOR:
	case MON_YAMAWARO_FLAG:
		mon->fire_resist=1;
		break;
	case MON_ONBASIRA:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;		
	case MON_RED_UFO:
		mon->fire_resist=2;
		break;
	case MON_GREEN_UFO:
		mon->elec_resist=2;
		mon->poison_resist=1;
		break;
	case MON_BLUE_UFO:
		mon->ice_resist=2;
		break;
	case MON_NUE:
		mon->elec_resist=3;
		mon->poison_resist=1;
		break;
	case MON_SANPEI_FIGHTER:
		mon->ice_resist=2;
		mon->fire_resist=1;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_DEAGAMA:
		mon->poison_resist=1;
		break;
	case MON_NAMAZ:
		mon->elec_resist=1;
		break;
	case MON_HELL_CROW:
		mon->fire_resist=2;
		break;
	case MON_LANTERN_YOUKAI:
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;
	case MON_YINYAN:
		mon->elec_resist=2;
		mon->ice_resist=2;
		mon->fire_resist=2;
		mon->poison_resist=1;
		break;
	case MON_YUUGENMAGAN:
		mon->elec_resist=3;
		mon->poison_resist=1;
		break;
	case MON_ELIS:
		mon->elec_resist=1;
		mon->poison_resist=1;
		break;
	case MON_SARIEL:
		mon->elec_resist=1;
		mon->ice_resist=2;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_SARA:
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_LUIZE:
		mon->ice_resist=1;
		break;
	case MON_YUKI:
		mon->fire_resist=3;
		break;
	case MON_MAI:
		mon->ice_resist=3;
		break;
	case MON_YUMEKO:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->fire_resist=2;
		mon->poison_resist=1;
		break;
	case MON_MAGICAL_STAR:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;		
	case MON_GOLEM:
		mon->elec_resist=3;
		mon->ice_resist=2;
		mon->fire_resist=2;
		mon->poison_resist=1;
	case MON_EVIL_EYE:
		mon->elec_resist=3;
		mon->poison_resist=1;
		break;		
	case MON_SCHEMA_EYE:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;		
	case MON_FLAN:
	case MON_FLAN_BUNSIN:
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_TEWI:
		break;
	case MON_CLOWNPIECE:
		mon->fire_resist=2;
		break;
	case MON_DOREMI:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;		
	case MON_FAIRY_HERO:
		break;
	case MON_FAIRY_SOCERER:
		mon->ice_resist=1;
		break;
	case MON_FAIRY_SUN_FLOWER:
		mon->fire_resist=1;
		break;
	case MON_MOON_RABIT_SUPPORT:
		mon->confuse_resist=1;
		break;
	case MON_MOON_RABIT_ATTACK:
		mon->confuse_resist=1;
		break;
	case MON_MOON_RABIT_ELITE:
		mon->confuse_resist=1;
		break;
	case MON_MAC:
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_NIGHTMARE:
		mon->elec_resist=2;
		mon->ice_resist=1;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_LUNATIC:
		mon->elec_resist=2;
		mon->fire_resist=1;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_HAUNT:
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_FIRE_CAR:
		mon->ice_resist=-1;
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;
	case MON_HELL_SPIDER:
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_BLOOD_HAUNT:
		mon->elec_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_HELL_HOUND:
		mon->fire_resist=1;
		break;
	case MON_DESIRE:
		break;
	case MON_FLOWER_TANK:
		mon->ice_resist=1;
		mon->elec_resist=2;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_EVIL_EYE_TANK:
		mon->ice_resist=1;
		mon->elec_resist=3;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_SNOW_GIRL:
		mon->ice_resist=3;
		mon->fire_resist=-1;
		break;
	case MON_LETTY:
		mon->ice_resist=3;
		mon->fire_resist=-1;
		mon->poison_resist=1;
		break;
	case MON_YORIHIME:
		mon->ice_resist=2;
		mon->elec_resist=2;
		mon->confuse_resist=1;
		break;
	case MON_TOYOHIME:
		mon->ice_resist=2;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_UTSUHO:
		mon->poison_resist=1;
		mon->fire_resist=3;
		break;
	case MON_SUIKA:
		mon->fire_resist=2;
		break;
	case MON_REIMU:
		break;
	case MON_ALICE:
		mon->elec_resist=1;
		mon->poison_resist=1;
		break;
	case MON_SEIRAN:
		mon->confuse_resist=1;
		break;
	case MON_RINGO:
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_UDONGE:
		mon->elec_resist=1;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_KAGUYA:
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_MOKOU:
		mon->fire_resist=3;
		break;
	case MON_NESI:
		mon->fire_resist=2;
		mon->ice_resist=2;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_SANGHAI:
	case MON_FAKE_SANGHAI:
		mon->ice_resist=1;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_HOURAI:
	case MON_FAKE_HOURAI:
		mon->elec_resist=1;
		mon->fire_resist=1;
		mon->ice_resist=1;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_TOKIKO:
		mon->wind_resist=1;
		mon->poison_resist=-1;
		break;
	case MON_TOZIKO:
		mon->elec_resist=3;
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_FUTO:
		mon->fire_resist=2;
		break;
	case MON_MAMIZO:
		break;
	}
}