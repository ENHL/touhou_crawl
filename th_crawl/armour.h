//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: armour.h
//
// ����: ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

struct item_infor;


enum armour_kind
{
	AMK_NORMAL, //����
	AMK_MIKO, //����� (ȥ������)
	AMK_WING, //������ (��������)
	AMK_KAPPA, //ı�Ŀ� (�ñ�����)
	AMK_FIRE, //�����ǿ� (ȭ������)
	AMK_MAID, //���̵�� (��������)
	AMK_POISON, //������(������)
	AMK_MAX
};


enum material_kind
{
	MTK_ROBE,
	MTK_LEATHER,
	MTK_CHAIN,
	MTK_PLATE,
	MTK_MAX
};



enum armour_value
{
	AMV_AC,
	AMV_MAX_EV,
	AMV_MIN_EV
};

void MakeBaseArmour(armour_kind type, material_kind material, item_infor* t);
void MakeArmourEnchant(int good_bad, item_infor* t);
void equipArmour(armour_kind type, int value);

armour_kind GetRandomArmourType(int good_bad);
int GetMaterial(material_kind kind, armour_value value_);

