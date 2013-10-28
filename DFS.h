#include <stdio.h>
#include <malloc.h>
int map[10][10] = {
	{0,1,1,1,1,1,1,1,1,1},
	{0,0,0,1,0,0,0,0,1,1},
	{1,0,1,0,0,1,1,0,1,1},
	{1,0,1,0,1,1,1,0,1,1},
	{1,0,0,0,0,1,1,1,1,1},
	{1,1,0,1,0,1,1,1,1,1},
	{1,1,0,0,0,0,1,1,1,1},
	{1,0,0,1,1,0,1,1,1,1},
	{1,0,0,1,1,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,0,3},
};
struct mazePiece
{
	int x;
	int y;
	int state;
	mazePiece* next;

};

void AddMazePiece(mazePiece* start,int x,int y) 
{
	mazePiece* temp = (mazePiece*)malloc(sizeof(mazePiece));
	temp->x = x;
	temp->y = y;
	temp->state = 0;
	temp->next = 0;
	mazePiece *end = start;
	while(end->next != 0) {
		end = end->next;
	}
	end->next = temp;
	//start->next = temp; 
}

int inArr(int x,int y,mazePiece* start) 
{
	int flag = 0;
	mazePiece* temp = start;
	while (temp != 0) {
		if(temp->x == x && temp->y == y) {
			flag = 1;
			break;
		}
		temp = temp->next;
	}
	return flag;
}

int inVisit(int x,int y,mazePiece* start) 
{
	int flag = 0;
	mazePiece* temp = start;
	while (temp != 0) {
		if(temp->x == x && temp->y == y) {
			if(temp->state == 1) {
				flag = 1;
				break;
			}
		}
		temp = temp->next;
	}
	return flag;
}

int setVisit(int x,int y,mazePiece* start) {
	int flag = 0;
	mazePiece* temp = start;
	while (temp != 0) {
		if(temp->x == x && temp->y == y) {
			temp->state = 1;
			flag = 1;
			break;

		}
		temp = temp->next;
	}
	return flag;
}

int setVisit_r(int x,int y,mazePiece* start) {
	int flag = 0;
	mazePiece* temp = start;
	while (temp != 0) {
		if(temp->x == x && temp->y == y) {
			temp->state = 0;
			flag = 1;
			break;

		}
		temp = temp->next;
	}
	return flag;
}

int DelectPiece(int x,int y,mazePiece* start) 
{
	int i = 0;
	int flag = 0;
	mazePiece* temp = start;
	while (temp->x != x || temp->y != y) {
		temp = temp->next;
		i++;
		if(temp == 0) {
			flag = 1;
			break;
		}
	}
	if(flag == 0) {
		mazePiece* del = temp;
		mazePiece* last = start;
		for(int n = 0;n < i-1;n++) {
			last = last->next;
		}
		last->next = del->next;
		free(del);
		return 1;
	}else{
		return 0;
	}
}

void PrintMap(mazePiece* start)
{
	int x,y;
	int way[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,3},
	};
	mazePiece* temp = start; 
	while(temp != 0) {
		x = temp->x;
		y = temp->y;
		if(x != -1 && y != -1){
			way[x][y] = 0;
		}
		temp = temp->next; 
	}
	for (int i = 0;i < 10;i++) {
		for (int n = 0;n < 10;n++){
			printf("%d ",way[i][n]);
		}
		printf("\n");
	}
}

mazePiece* CreateMaze() {
	mazePiece* start = (mazePiece*)malloc(sizeof(mazePiece));
	start->x = -1;
	start->y = -1;
	start->state = 0;
	start->next = NULL;
	for (int i = 0;i < 10;i++) {
		for (int n = 0;n < 10;n++) {
			if(map[i][n] == 0 || map[i][n] == 3)
				AddMazePiece(start,i,n);
		}
	}
	return start;

}

int DFS(int x,int y,mazePiece* start) 
{
	setVisit(x,y,start);
	if(map[x][y] == 3)
		return 1;

	int flag1 = 0;
	int flag2 = 0;
	int flag3 = 0;
	int flag4 = 0;
	int z = 0;
	int c = 0;

	z = inArr(x-1,y,start);
	if(z == 1) {
		c = inVisit(x-1,y,start);
		if(c == 0)
			flag1 = DFS(x-1,y,start);
	}

	z = inArr(x+1,y,start);
	if(z == 1) {
		c = inVisit(x+1,y,start);
		if(c == 0)
			flag2 = DFS(x+1,y,start);
	}

	z = inArr(x,y+1,start);
	if(z == 1) {
		int c = inVisit(x,y+1,start);
		if(c == 0)
			flag3 = DFS(x,y+1,start);
	}

	z = inArr(x,y-1,start);
	if(z == 1) {
		c = inVisit(x,y-1,start);
		if(c == 0)
			flag4 = DFS(x,y-1,start);
	}

	if(flag1 == 1 || flag2 == 1 || flag3 == 1 || flag4 == 1) {
		return 1;
	} else {
		DelectPiece(x,y,start);
		//printf("%d %d ",x,y);
		//printf("\n");
		//PrintMap(start);
		//printf("\n");
		return 0;
	}

}