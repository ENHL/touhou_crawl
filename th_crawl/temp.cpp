//
//
//void map_algorithms01(int num)
//{
//	vector<map_dummy*> vec_map;
//	vector<int> special_enter;
//	calcul_spe_enter(num,special_enter);
//	
//
//	vec_map.reserve(32);
//
//
//	
//
//	int rand_dummy = rand_int(20,30);
//	for(int i=0;i<rand_dummy;i++) //rand_dummy��ŭ�� �ʴ��̸� ����
//	{
//		int repeat = 10;
//		int pattern_ = 0;
//		bool special_ = false;
//		if(!special_enter.empty())
//		{
//			special_ = true;
//			repeat = 99999;//Ư�������� (����)���ѹݺ���Ŵ
//			pattern_ = special_enter.back();
//			special_enter.pop_back();
//		}
//		for(int j=0;j<repeat;j++) //���ѹݺ� ���ſ�
//		{
//			bool success= true;
//			int r_size_x = rand_int(3,8);
//			int r_size_y = rand_int(3,8);
//			int m_size=5;
//			coord_def temp_coord(randA(DG_MAX_X-(r_size_x+2)*2-1-m_size*2)+r_size_x+2+m_size,randA(DG_MAX_Y-(r_size_y+2)*2-1-m_size*2)+r_size_y+2+m_size);		
//			map_dummy* temp = new map_dummy(temp_coord, true,r_size_x,r_size_y, pattern_); //������ �ʴ���
//			
//			vector<map_dummy*>::iterator it;
//			for (it=vec_map.begin();it!=vec_map.end();it++) 
//			{
//				if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //�ʴ����浹�ÿ� ������ ����
//				{
//					success = false;
//					break;
//				}
//			}	
//			if(success) //��ġ�� ������ �ʴ���Ǫ��
//			{
//				vec_map.push_back(temp);
//				break;
//			}
//			else
//			{
//				delete temp; //��ġ�� �޸� �����ϰ� �ٽ� �ʴ��� ����
//				continue;
//			}
//		}
//	}
//
//	vector<map_dummy*>::iterator it;
//	for(it=vec_map.begin();it!=vec_map.end();it++)  //����� ����ũ�ֱ�
//		(*it)->mask(env[num]);
//
//	stack<coord_def> path_stack;
//
//	map_dummy* temp = vec_map.back();
//	for(it=vec_map.begin();it!=vec_map.end();it++) 
//	{
//		if(PathSearch(temp->GetEntrance(),(*it)->GetExit(),path_stack,ST_MAP,num))//�濡 �ɸ� ����ũ�� ���ؼ� �������
//		{
//			(*it)->SetConnectExit(true);
//			temp->SetConnectEnter(true);
//		}
//		temp = (*it);
//	}
//
//	{
//		vector<map_dummy*>::iterator it2 = vec_map.begin();
//		for(it=vec_map.begin();it!=vec_map.end();it++)  //������ �ȵ� ����� �ٽ� ����õ�
//		{
//			for(;!(*it)->GetConnect() && it2 != vec_map.end();it2++)
//			{
//				if(it == it2)
//					continue;
//				if(PathSearch((*it)->GetEntrance(),(*it2)->GetExit(),path_stack,ST_MAP,num))//�濡 �ɸ� ����ũ�� ���ؼ� �������
//				{
//					(*it)->SetConnectEnter(true);
//					temp->SetConnectExit(true);
//				}				
//			}
//		}
//	}
//
//
//	for(int i = 0;i<DG_MAX_X;i++)
//		for(int j = 0;j<DG_MAX_Y;j++)
//			env[num].dgtile[i][j].tile = DG_WALL; //�ٽ� ���� ������
//
//
//	while(!path_stack.empty())
//	{
//		coord_def path_temp = path_stack.top();
//		env[num].dgtile[path_temp.x][path_temp.y].tile = DG_FLOOR; //������ ���θ� ĥ�ϱ�
//		path_stack.pop();
//	}
//
//	int percent_ = randA(10);
//	for(it=vec_map.begin();it!=vec_map.end();it++) 
//	{//���� �����.
//		(*it)->make_map(env[num]);
//		if(!(*it)->pattern && randA(10)>=percent_)
//			(*it)->make_door(env[num]);
//	}
//
//	for (it=vec_map.begin();it!=vec_map.end();it++)
//		delete *it;
//
//	for(int i=0;i<6;i++)
//	{
//		while(1)
//		{
//			int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1);
//			if(env[num].dgtile[x][y].tile == DG_FLOOR  && !(env[num].dgtile[x][y].flag & FLAG_NO_MONSTER) )
//			{
//				if(i>2)
//				{
//					env[num].stair_up[i-3].x = x;
//					env[num].stair_up[i-3].y = y;
//					env[num].dgtile[x][y].tile = DG_UP_STAIR;
//				}
//				else
//				{
//					env[num].stair_down[i].x = x;
//					env[num].stair_down[i].y = y;
//					env[num].dgtile[x][y].tile = DG_DOWN_STAIR;	
//				}
//				break;
//			}
//		}
//	}
//}
//void map_algorithms02(int num, int piece)
//{
//	vector<map_dummy*> vec_map;
//	vector<map_dummy*> vec_special_map;
//	vector<int> special_enter;
//	calcul_spe_enter(num,special_enter);
//
//	int prev_x=0;
//	int prev_y=0;
//	int step = 0;
//
//	int rand_dummy = special_enter.size();
//	for(int i=0;i<rand_dummy;i++) //rand_dummy��ŭ�� �ʴ��̸� ����
//	{	
//		int repeat = 10;
//		int pattern_ = 1;
//		bool special_ = false;
//		if(!special_enter.empty())
//		{
//			special_ = true;
//			repeat = 99999;//Ư�������� (����)���ѹݺ���Ŵ
//			pattern_ = special_enter.back();
//			special_enter.pop_back();
//		}
//		for(int j=0;j<repeat;j++) //���ѹݺ� ���ſ�
//		{
//			bool success= true;
//			int r_size_x = rand_int(2+piece/3,4+piece/3);
//			int r_size_y = rand_int(2+piece/3,4+piece/3);
//			int m_size=5;
//			coord_def temp_coord(randA(DG_MAX_X-(6+2)*2-1-m_size*2)+6+2+m_size,randA(DG_MAX_Y-(6+2)*2-1-m_size*2)+6+2+m_size);		
//			map_dummy* temp = new map_dummy(temp_coord, false,r_size_x,r_size_y,pattern_); //������ �ʴ���
//			
//			vector<map_dummy*>::iterator it;
//			for (it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//			{
//				if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //�ʴ����浹�ÿ� ������ ����
//				{
//					success = false;
//					break;
//				}
//			}		
//			if(success) //��ġ�� ������ �ʴ���Ǫ��
//			{
//				vec_special_map.push_back(temp);
//				break;
//			}
//			else
//			{
//				delete temp; //��ġ�� �޸� �����ϰ� �ٽ� �ʴ��� ����
//				continue;
//			}
//		}
//	}
//
//
//	for(int i=0;i<25-piece;i++)
//	{
//		int j=0;
//		for(;j<20;j++) //���ѹݺ� ���ſ�
//		{
//			bool success= true;
//			int next_x=0,next_y=0;
//			int r_size_x = rand_int(1+piece/3,4+piece/3);
//			int r_size_y = rand_int(1+piece/3,4+piece/3);
//			int m_size=5;
//			if(step != 1)
//				next_x = randA(DG_MAX_X-(r_size_x+2)*2-1-m_size*2)+r_size_x+2+m_size;
//			else
//				next_x = prev_x+rand_int(-r_size_x+1,r_size_x-1);
//
//			if(step != -1)
//				next_y = randA(DG_MAX_Y-(r_size_y+2)*2-1-m_size*2)+r_size_y+2+m_size;
//			else
//				next_y = prev_y+rand_int(-r_size_y+1,r_size_y-1);
//
//			coord_def temp_coord(next_x,next_y);		
//			map_dummy* temp = new map_dummy(temp_coord, false,r_size_x,r_size_y,0); //������ �ʴ���
//
//			if(step)
//			{
//				if(step == 1)
//				{
//					temp->SetEnter(coord_def(next_x,prev_y>next_y?next_y+r_size_y-1:next_y-r_size_y+1));
//				}
//				else
//				{
//					temp->SetEnter(coord_def(prev_x>next_x?next_x+r_size_x-1:next_x-r_size_x+1,next_y));
//				}
//			}
//
//			
//			vector<map_dummy*>::iterator it;
//			if(piece < 4+randA(3))
//			{
//				for (it=vec_map.begin();it!=vec_map.end();it++) 
//				{
//					if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //�ʴ����浹�ÿ� ������ ����
//					{
//						success = false;
//						break;
//					}
//				}
//			}
//			for (it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//			{
//				if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //�ʴ����浹�ÿ� ������ ����
//				{
//					success = false;
//					break;
//				}
//			}
//			if(success) //��ġ�� ������ �ʴ���Ǫ��
//			{
//				step = (step!=-1)?-1:1;
//				prev_x = next_x+rand_int(-r_size_x+1,r_size_x-1);
//				prev_y = next_y+rand_int(-r_size_y+1,r_size_y-1);
//				temp->SetExit(coord_def(prev_x,prev_y));
//				vec_map.push_back(temp);
//				break;
//			}
//			else
//			{
//				delete temp; //��ġ�� �޸� �����ϰ� �ٽ� �ʴ��� ����
//				continue;
//			}
//		}
//		if(j==0)
//		{
//			step = 0;	
//		}
//	}
//
//	vector<map_dummy*>::iterator it;
//	for(it=vec_special_map.begin();it!=vec_special_map.end();it++)  //����� ����ũ�ֱ�
//		(*it)->mask(env[num]);
//
//
//	stack<coord_def> path_stack;
//	map_dummy* temp = vec_map.back();
//	
//	for(it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//	{
//		if(PathSearch(temp->GetEntrance(),(*it)->GetExit(),path_stack,ST_MAP,num))//�濡 �ɸ� ����ũ�� ���ؼ� �������
//		{
//			path_stack.push((*it)->GetEntrance());
//			(*it)->SetConnectExit(true);
//			temp->SetConnectEnter(true);
//		}
//		temp = (*it);
//	}
//	for(it=vec_map.begin();it!=vec_map.end();it++) 
//	{
//		if(PathSearch(temp->GetEntrance(),(*it)->GetExit(),path_stack,ST_MAP,num))//�濡 �ɸ� ����ũ�� ���ؼ� �������
//		{
//			path_stack.push((*it)->GetEntrance());
//			(*it)->SetConnectExit(true);
//			temp->SetConnectEnter(true);
//		}
//		temp = (*it);
//	}
//
//
//	for(int i = 0;i<DG_MAX_X;i++)
//		for(int j = 0;j<DG_MAX_Y;j++)
//			env[num].dgtile[i][j].tile = DG_WALL; //�ٽ� ���� ������
//
//
//
//
//
//	for(it=vec_map.begin();it!=vec_map.end();it++) 
//	{//���� �����.
//		(*it)->make_map(env[num], false);
//		/*(*it)->make_door(env[num]);*/
//	}
//
//	while(!path_stack.empty())
//	{
//		coord_def path_temp = path_stack.top();
//		env[num].dgtile[path_temp.x][path_temp.y].tile = DG_FLOOR; //������ ���θ� ĥ�ϱ�
//		path_stack.pop();
//	}	
//	for(it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//	{//���� �����.
//		(*it)->make_map(env[num], false);
//	}
//
//	for (it=vec_special_map.begin();it!=vec_special_map.end();it++)
//		delete *it;
//
//	for (it=vec_map.begin();it!=vec_map.end();it++)
//		delete *it;
//
//	for(int i=0;i<6;i++)
//	{
//		while(1)
//		{
//			int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1);
//			if(env[num].dgtile[x][y].tile == DG_FLOOR  && !(env[num].dgtile[x][y].flag & FLAG_NO_MONSTER) )
//			{
//				if(i>2)
//				{
//					env[num].stair_up[i-3].x = x;
//					env[num].stair_up[i-3].y = y;
//					if(num == YOUKAI_MOUNTAIN_LEVEL)
//						env[num].dgtile[x][y].tile = DG_RETURN_STAIR;
//					else
//						env[num].dgtile[x][y].tile = DG_UP_STAIR;
//				}
//				else
//				{
//					env[num].stair_down[i].x = x;
//					env[num].stair_down[i].y = y;
//					env[num].dgtile[x][y].tile = DG_DOWN_STAIR;	
//				}
//				break;
//			}
//		}
//	}
//}
//
//void map_algorithms03(int num)
//{
//	vector<map_dummy*> vec_map;
//	vector<map_dummy*> vec_special_map;
//	vector<int> special_enter;
//	calcul_spe_enter(num,special_enter);
//
//	int prev_x=0;
//	int prev_y=0;
//	int step = 0;
//
//
//
//	for(int i=0;i<40;i++)
//	{
//		int j=0;
//		for(;j<50;j++) //���ѹݺ� ���ſ�
//		{
//			bool success= false;
//			int next_x=0,next_y=0;
//			int r_size_x = rand_int(1,5);
//			int r_size_y = r_size_x;
//			int m_size=10;
//			if(step != 1)
//				next_x = randA(DG_MAX_X-(r_size_x+2)*2-1-m_size*2)+r_size_x+2+m_size;
//			else
//				next_x = prev_x+rand_int(-r_size_x+1,r_size_x-1);
//
//			if(step != -1)
//				next_y = randA(DG_MAX_Y-(r_size_y+2)*2-1-m_size*2)+r_size_y+2+m_size;
//			else
//				next_y = prev_y+rand_int(-r_size_y+1,r_size_y-1);
//
//			coord_def temp_coord(next_x,next_y);		
//			map_dummy* temp = new map_dummy(temp_coord, false,r_size_x,r_size_y,1); //������ �ʴ���
//
//			if(step)
//			{
//				if(step == 1)
//				{
//					temp->SetEnter(coord_def(next_x,prev_y>next_y?next_y+r_size_y-1:next_y-r_size_y+1));
//				}
//				else
//				{
//					temp->SetEnter(coord_def(prev_x>next_x?next_x+r_size_x-1:next_x-r_size_x+1,next_y));
//				}
//			}
//
//			
//			vector<map_dummy*>::iterator it;
//			if(vec_map.empty())
//				success = true;
//
//			for (it=vec_map.begin();it!=vec_map.end();it++) 
//			{
//				if(distan_coord(temp->pos,(*it)->pos)<=(temp->size_x+(*it)->size_x+1)*(temp->size_x+(*it)->size_x+1))
//				{
//					success = true;
//					break;
//				}
//			}
//			//for (it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//			//{
//			//	if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //�ʴ����浹�ÿ� ������ ����
//			//	{
//			//		success = false;
//			//		break;
//			//	}
//			//}
//			if(success) //��ġ�� ������ �ʴ���Ǫ��
//			{
//				step = (step!=-1)?-1:1;
//				prev_x = next_x+rand_int(-r_size_x+1,r_size_x-1);
//				prev_y = next_y+rand_int(-r_size_y+1,r_size_y-1);
//				temp->SetExit(coord_def(prev_x,prev_y));
//				vec_map.push_back(temp);
//				break;
//			}
//			else
//			{
//				delete temp; //��ġ�� �޸� �����ϰ� �ٽ� �ʴ��� ����
//				continue;
//			}
//		}
//		if(j==0)
//		{
//			step = 0;	
//		}
//	}
//
//
//	int rand_dummy = special_enter.size();
//	for(int i=0;i<rand_dummy;i++) //rand_dummy��ŭ�� �ʴ��̸� ����
//	{	
//		int repeat = 10;
//		int pattern_ = 1;
//		bool special_ = false;
//		if(!special_enter.empty())
//		{
//			special_ = true;
//			repeat = 99999;//Ư�������� (����)���ѹݺ���Ŵ
//			pattern_ = special_enter.back();
//			special_enter.pop_back();
//		}
//		for(int j=0;j<repeat;j++) //���ѹݺ� ���ſ�
//		{
//			bool success= false;
//			int r_size_x = rand_int(3,8);
//			int r_size_y = rand_int(3,8);
//			int m_size=20;
//			coord_def temp_coord(randA(DG_MAX_X-(6+2)*2-1-m_size*2)+6+2+m_size,randA(DG_MAX_Y-(6+2)*2-1-m_size*2)+6+2+m_size);		
//			map_dummy* temp = new map_dummy(temp_coord, false,r_size_x,r_size_y,pattern_); //������ �ʴ���
//			
//			vector<map_dummy*>::iterator it;
//			for (it=vec_map.begin();it!=vec_map.end();it++) 
//			{
//				if(distan_coord(temp->pos,(*it)->pos)<=(temp->size_x+(*it)->size_x+1)*(temp->size_x+(*it)->size_x+1))
//				{
//					success = true;
//					break;
//				}
//			}
//			for (it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//			{
//				if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //�ʴ����浹�ÿ� ������ ����
//				{
//					success = false;
//					break;
//				}
//			}
//
//
//			if(success) //��ġ�� ������ �ʴ���Ǫ��
//			{
//				vec_special_map.push_back(temp);
//				break;
//			}
//			else
//			{
//				delete temp; //��ġ�� �޸� �����ϰ� �ٽ� �ʴ��� ����
//				continue;
//			}
//		}
//	}
//
//
//
//
//	vector<map_dummy*>::iterator it;
//	//for(it=vec_special_map.begin();it!=vec_special_map.end();it++)  //����� ����ũ�ֱ�
//	//	(*it)->mask(env[num]);
//
//
//	//stack<coord_def> path_stack;
//	//map_dummy* temp = vec_map.back();
//	//
//	//for(it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//	//{
//	//	if(PathSearch(temp->GetEntrance(),(*it)->GetExit(),path_stack,ST_MAP,num))//�濡 �ɸ� ����ũ�� ���ؼ� �������
//	//	{
//	//		path_stack.push((*it)->GetEntrance());
//	//		(*it)->SetConnectExit(true);
//	//		temp->SetConnectEnter(true);
//	//	}
//	//	temp = (*it);
//	//}
//	//for(it=vec_map.begin();it!=vec_map.end();it++) 
//	//{
//	//	if(PathSearch(temp->GetEntrance(),(*it)->GetExit(),path_stack,ST_MAP,num))//�濡 �ɸ� ����ũ�� ���ؼ� �������
//	//	{
//	//		path_stack.push((*it)->GetEntrance());
//	//		(*it)->SetConnectExit(true);
//	//		temp->SetConnectEnter(true);
//	//	}
//	//	temp = (*it);
//	//}
//
//
//	for(int i = 0;i<DG_MAX_X;i++)
//		for(int j = 0;j<DG_MAX_Y;j++)
//			env[num].dgtile[i][j].tile = DG_WALL; //�ٽ� ���� ������
//
//
//
//
//
//	for(it=vec_map.begin();it!=vec_map.end();it++) 
//	{//���� �����.
//		(*it)->make_map(env[num], false);
//		/*(*it)->make_door(env[num]);*/
//	}
//
//	//while(!path_stack.empty())
//	//{
//	//	coord_def path_temp = path_stack.top();
//	//	env[num].dgtile[path_temp.x][path_temp.y].tile = DG_FLOOR; //������ ���θ� ĥ�ϱ�
//	//	path_stack.pop();
//	//}	
//	for(it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//	{//���� �����.
//		(*it)->make_map(env[num], false);
//	}
//
//	for (it=vec_special_map.begin();it!=vec_special_map.end();it++)
//		delete *it;
//
//	for (it=vec_map.begin();it!=vec_map.end();it++)
//		delete *it;
//
//	for(int i=0;i<6;i++)
//	{
//		while(1)
//		{
//			int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1);
//			if(env[num].dgtile[x][y].tile == DG_FLOOR  && !(env[num].dgtile[x][y].flag & FLAG_NO_MONSTER) )
//			{
//				if(i>2)
//				{
//					env[num].stair_up[i-3].x = x;
//					env[num].stair_up[i-3].y = y;
//					if(num == YOUKAI_MOUNTAIN_LEVEL)
//						env[num].dgtile[x][y].tile = DG_RETURN_STAIR;
//					else
//						env[num].dgtile[x][y].tile = DG_UP_STAIR;
//				}
//				else
//				{
//					env[num].stair_down[i].x = x;
//					env[num].stair_down[i].y = y;
//					if(num != YOUKAI_MOUNTAIN_LAST_LEVEL)
//						env[num].dgtile[x][y].tile = DG_DOWN_STAIR;	
//				}
//				break;
//			}
//		}
//	}
//
//
//	{//�ӽ�
//		//while(num == YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL)
//		//{
//		//	int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1);
//		//	if(env[num].dgtile[x][y].tile == DG_FLOOR)
//		//	{
//		//		item_infor t;
//		//		env[num].MakeItem(coord_def(x,y),makeitem(ITM_GOAL, 0, &t, 0));
//		//		break;
//		//	}
//		//}
//	}
//}
