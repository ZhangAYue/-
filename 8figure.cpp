#include<iostream>
#include<queue>
#include<vector>
#define x(i,x,y) for(i=x;i<y;i++)
#define NoResult cout<<"该问题没有结果"<<endl
using namespace std;


typedef struct status{
	int state[3][3];
	int step;
	int price;
	char operate[20];
	int x, y;
	char lastStep;
	bool operator < (const status &a)const{
		return price>a.price;
	}
};

int result[3][3];


bool compare(int a[3][3], int b[3][3]){
	int i, j;
	x(i, 0, 3){
		x(j, 0, 3){
			if (a[i][j] != b[i][j])
				return false;
		}
	}
	return true;
}

status getPrice(status &a){
	int i, j;
	a.price = 0;
	x(i, 0, 3){
		x(j, 0, 3){
			if (a.state[i][j] != 0){
				if (a.state[i][j] != result[i][j])
					a.price++;
			}
		}
	}
	a.price += a.step;
	return a;
}

bool hasAnswer(int a[3][3], int b[3][3]){
	int InverseNumA = 0;
	int InverseNumB = 0;
	int as[9], bs[9];
	int i, j, k = 0;
	x(i, 0, 3){
		x(j, 0, 3){
			as[k] = a[i][j];
			k++;
		}
	}
	k = 0;
	x(i, 0, 3){
		x(j, 0, 3){
			bs[k] = b[i][j];
			k++;
		}
	}
	x(i, 0, 9){
		if (a[i] == 0)
			continue;
		x(j, 0, i){
			if (as[i] < as[j])
				InverseNumA++;
		}
	}
	x(i, 0, 9){
		if (b[i] == 0)
			continue;
		x(j, 0, i){
			if (bs[i] < bs[j])
				InverseNumB++;
		}
	}
	return (InverseNumA % 2 - InverseNumB % 2) == 0;
}

status Move(status b, char direction){
	int temp;
	status a = b;
	switch (direction)
	{
	case'U':{
				temp = a.state[a.x - 1][a.y];
				a.state[a.x - 1][a.y] = 0;
				a.state[a.x][a.y] = temp;
				a.x--;
				a.operate[a.step] = 'U';
				a.lastStep = 'D';
				break; }
	case'D':{
				temp = a.state[a.x + 1][a.y];
				a.state[a.x + 1][a.y] = 0;
				a.state[a.x][a.y] = temp;
				a.x++;
				a.operate[a.step] = 'D';
				a.lastStep = 'U';
				break; }
	case'L':{
				temp = a.state[a.x][a.y - 1];
				a.state[a.x][a.y - 1] = 0;
				a.state[a.x][a.y] = temp;
				a.y--;
				a.operate[a.step] = 'L';
				a.lastStep = 'R';
				break; }
	case'R':{
				temp = a.state[a.x][a.y + 1];
				a.state[a.x][a.y + 1] = 0;
				a.state[a.x][a.y] = temp;
				a.y++;
				a.operate[a.step] = 'R';
				a.lastStep = 'L';
				break; }
	default:break;
	}
	a.step++;
	a = getPrice(a);
	return a;
}

void show(status a){
	int i, j;
	x(i, 0, 3){
		x(j, 0, 3)
			cout << a.state[i][j] << " ";
		cout << endl;
	}
	cout << "步数:" << a.step << endl << endl;
}

void showProcess(char operate[20], int step, status input){
	int i = 0;
	status a = input;
	x(i, 0, step){
		a = Move(a, operate[i]);
		show(a);
	}
}

int main(){
	status input;
	int i, j;
	input.step = 0;
	priority_queue<status>open;

	cout << "请输入起始状态(空位置用0表示):" << endl;
	x(i, 0, 3){
		x(j, 0, 3){
			cin >> input.state[i][j];
			if (input.state[i][j] == 0){
				input.x = i;
				input.y = j;
			}
		}
	}
	cout << "请输入最终状态:" << endl;
	x(i, 0, 3){
		x(j, 0, 3){
			cin >> result[i][j];
		}
	}

	if (!hasAnswer(input.state, result)){
		NoResult;
		return 0;
	}

	memset(input.operate, 0, 20);
	input.lastStep = ' ';
	input.price = 100;
	open.push(input);
	status a;
	status process;
	while (!compare((a = open.top()).state, result)&&!open.empty()){
		open.pop();
		while(a.step > 20){
			a = open.top();
			open.pop();
			if (open.empty()){
				NoResult;
				return 0;
			}
		}
		if (a.lastStep == ' '){
			if (a.y != 0)
				open.push(Move(a, 'L'));
			if (a.y != 2)
				open.push(Move(a, 'R'));
			if (a.x != 0)
				open.push(Move(a, 'U'));
			if (a.x != 2)
				open.push(Move(a, 'D'));
		}
		if (a.lastStep == 'D'){
			if (a.y != 0)
				open.push(Move(a, 'L'));
			if (a.y != 2)
				open.push(Move(a, 'R'));
			if (a.x != 0)
				open.push(Move(a, 'U'));
		}
		if (a.lastStep == 'U'){
			if (a.y != 0)
				open.push(Move(a, 'L'));
			if (a.y != 2)
				open.push(Move(a, 'R'));
			if (a.x != 2)
				open.push(Move(a, 'D'));
		}
		if (a.lastStep == 'L'){
			if (a.y != 2)
				open.push(Move(a, 'L'));
			if (a.x != 0)
				open.push(Move(a, 'U'));
			if (a.x != 2)
				open.push(Move(a, 'D'));
		}
		if (a.lastStep == 'R'){
			if (a.y != 0)
				open.push(Move(a, 'R'));
			if (a.x != 0)
				open.push(Move(a, 'U'));
			if (a.x != 2)
				open.push(Move(a, 'D'));
		}
	}
	status ans = open.top();
	cout << "最终步骤：" << ans.operate << endl << endl;
	showProcess(ans.operate, ans.step, input);

	return 0;
}
