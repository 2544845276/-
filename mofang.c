#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef enum color {
	white = 'w',
	red = 'r',
	bule = 'b',
	yellow = 'y',
	green = 'g',
	orange = 'o',
}Color;

typedef struct face {
	Color  s[4][4];
}Face;


typedef struct cube {
	Face up, down, front, back, left, right;
}Cube;

/*************************魔方旋转的基本操作*************************/ 
void CClockwise_Face(Face* f);	 	// 逆时针旋转面 
void Clockwise_Face(Face* f);	 	// 顺时针旋转面
void CCfront(Cube* box)	;			//逆时针旋转前面
void Back(Cube* box);				//顺时针旋转后面
void CBack(Cube* box);				//逆时针旋转后面
void Left(Cube* box);				//顺时针旋转左面 
void CLeft(Cube* box);				//逆时针旋转左面 
void Right(Cube* box);				//顺时针旋转右面
void CRight(Cube* box);				//逆时针旋转右面 
void CTop(Cube* box);				//顺时针旋转上面
void CCTop(Cube* box);				//逆时针旋转上面
/*****************************初始化操作*****************************/ 
void InitFace(Face* f, char e);		//初始化面
void InitCube(Cube* box);			//初始化魔方
/********************************打印********************************/ 
void PrintFace(Face* f)	;			//打印面 
void PrintCube(Cube* box);			// 打印魔方 

void Disrupt(Cube* box);			//打乱魔方
/********************************魔方还原********************************/
void BottomCross(Cube* box)	;		//底面十字 
void BottomCornerReduction(Cube* box);//底部角块还原
void MedianEdge(Cube* box);			//中棱还原 
void TopCross(Cube* box);			//顶角十字做成 
void Vertexface(Cube* box) ;		//顶角面还原 
void VertexReduction(Cube* box);	//顶部还原
void TopEdgeReduction(Cube* box);	//上面还原 


int main(void) {
	double start, finish;
	start = clock();
	Cube box;
	InitCube(&box);
	printf("\n 魔方初始化\n");
	PrintCube(&box);
	printf("\n 随机打乱魔方\n");
	Disrupt(&box);
	PrintCube(&box);
	printf("\n 将魔方还原\n");
	BottomCross(&box);
	printf(" 底部十字\n");
	BottomCornerReduction(&box);
	printf(" 底部角块\n");
	MedianEdge(&box);
	printf(" 中棱归位\n");
	TopCross(&box);
	printf(" 顶面十字\n");
	Vertexface(&box);
	printf(" 顶角面还原\n");
	VertexReduction(&box);
	printf(" 顶角还原\n");
	TopEdgeReduction(&box);
	printf(" 顶棱还原\n");
	finish = clock();
	PrintCube(&box);
	return 0;
}

// 逆时针旋转面 
void CClockwise_Face(Face* f)			
{

	Face t;
	t = *f;


	f->s[1][1] = t.s[1][3];    // 面的颜色变化
	f->s[1][2] = t.s[2][3];
	f->s[1][3] = t.s[3][3];
	f->s[2][1] = t.s[1][2];
	f->s[2][2] = t.s[2][2];
	f->s[2][3] = t.s[3][2];
	f->s[3][1] = t.s[1][1];
	f->s[3][2] = t.s[2][1];
	f->s[3][3] = t.s[3][1];
}

// 顺时针旋转面
void Clockwise_Face(Face* f)			 
{
	Face t;								//定义一个结构体存储初始状态
	t = *f;
	f->s[1][1] = t.s[3][1];				
	f->s[1][2] = t.s[2][1];
	f->s[1][3] = t.s[1][1];
	f->s[2][1] = t.s[3][2];
	f->s[2][2] = t.s[2][2];
	f->s[2][3] = t.s[1][2];
	f->s[3][1] = t.s[3][3];
	f->s[3][2] = t.s[2][3];
	f->s[3][3] = t.s[1][3];
}


//顺时针旋转前面
void Cfront(Cube* box)			
{
	Cube n;
	n = *box;
	Clockwise_Face(&box->front);
	box->up.s[3][1] = n.left.s[3][3];
	box->up.s[3][2] = n.left.s[2][3];
	box->up.s[3][3] = n.left.s[1][3];
	box->right.s[1][1] = n.up.s[3][1];
	box->right.s[2][1] = n.up.s[3][2];
	box->right.s[3][1] = n.up.s[3][3];
	box->down.s[1][1] = n.right.s[3][1];
	box->down.s[1][2] = n.right.s[2][1];
	box->down.s[1][3] = n.right.s[1][1];
	box->left.s[1][3] = n.down.s[1][1];
	box->left.s[2][3] = n.down.s[1][2];
	box->left.s[3][3] = n.down.s[1][3];
}


//逆时针旋转前面
void CCfront(Cube* box)				
{
	Cube n;
	n = *box;
	CClockwise_Face(&box->front);
	box->up.s[3][1] = n.right.s[1][1];
	box->up.s[3][2] = n.right.s[2][1];
	box->up.s[3][3] = n.right.s[3][1];
	box->right.s[1][1] = n.down.s[1][3];
	box->right.s[2][1] = n.down.s[1][2];
	box->right.s[3][1] = n.down.s[1][1];
	box->down.s[1][1] = n.left.s[1][3];
	box->down.s[1][2] = n.left.s[2][3];
	box->down.s[1][3] = n.left.s[3][3];
	box->left.s[1][3] = n.up.s[3][3];
	box->left.s[2][3] = n.up.s[3][2];
	box->left.s[3][3] = n.up.s[3][1];
}

//顺时针旋转后面
void Back(Cube* box)					
{
	Cube n;
	n = *box;
	Clockwise_Face(&box->back);
	box->up.s[1][1] = n.right.s[1][3];
	box->up.s[1][2] = n.right.s[2][3];
	box->up.s[1][3] = n.right.s[3][3];
	box->right.s[1][3] = n.down.s[3][3];
	box->right.s[2][3] = n.down.s[3][2];
	box->right.s[3][3] = n.down.s[3][1];
	box->down.s[3][1] = n.left.s[1][1];
	box->down.s[3][2] = n.left.s[2][1];
	box->down.s[3][3] = n.left.s[3][1];
	box->left.s[1][1] = n.up.s[1][3];
	box->left.s[2][1] = n.up.s[1][2];
	box->left.s[3][1] = n.up.s[1][1];

}

//逆时针旋转后面
void CBack(Cube* box)				
{
	Cube n;
	n = *box;
	CClockwise_Face(&box->back);
	box->up.s[1][1] = n.left.s[3][1];
	box->up.s[1][2] = n.left.s[2][1];
	box->up.s[1][3] = n.left.s[1][1];

	box->down.s[3][1] = n.right.s[3][3];
	box->down.s[3][2] = n.right.s[2][3];
	box->down.s[3][3] = n.right.s[1][3];

	box->right.s[1][3] = n.up.s[1][1];
	box->right.s[2][3] = n.up.s[1][2];
	box->right.s[3][3] = n.up.s[1][3];

	box->left.s[1][1] = n.down.s[3][1];
	box->left.s[2][1] = n.down.s[3][2];
	box->left.s[3][1] = n.down.s[3][3];
}

//顺时针旋转左面 
void Left(Cube* box)				
{
	Cube n;
	n = *box;
	Clockwise_Face(&box->left);
	box->up.s[1][1] = n.back.s[1][1];
	box->up.s[2][1] = n.back.s[2][1];
	box->up.s[3][1] = n.back.s[3][1];

	box->front.s[1][1] = n.up.s[1][1];
	box->front.s[2][1] = n.up.s[2][1];
	box->front.s[3][1] = n.up.s[3][1];

	box->down.s[1][1] = n.front.s[1][1];
	box->down.s[2][1] = n.front.s[2][1];
	box->down.s[3][1] = n.front.s[3][1];

	box->back.s[1][1] = n.down.s[1][1];
	box->back.s[2][1] = n.down.s[2][1];
	box->back.s[3][1] = n.down.s[3][1];

}

//逆时针旋转左面 
void CLeft(Cube* box)
{
	Cube n;
	n = *box;
	CClockwise_Face(&box->left);

	box->up.s[1][1] = n.front.s[1][1];
	box->up.s[2][1] = n.front.s[2][1];
	box->up.s[3][1] = n.front.s[3][1];

	box->front.s[1][1] = n.down.s[1][1];
	box->front.s[2][1] = n.down.s[2][1];
	box->front.s[3][1] = n.down.s[3][1];

	box->down.s[1][1] = n.back.s[1][1];
	box->down.s[2][1] = n.back.s[2][1];
	box->down.s[3][1] = n.back.s[3][1];

	box->back.s[1][1] = n.up.s[1][1];
	box->back.s[2][1] = n.up.s[2][1];
	box->back.s[3][1] = n.up.s[3][1];
}


//顺时针旋转右面
void Right(Cube* box)						
{
	Cube n;
	n = *box;
	Clockwise_Face(&box->right);				

	box->front.s[1][3] = n.down.s[1][3];		
	box->front.s[2][3] = n.down.s[2][3];
	box->front.s[3][3] = n.down.s[3][3];

	box->down.s[1][3] = n.back.s[1][3];		 
	box->down.s[2][3] = n.back.s[2][3];
	box->down.s[3][3] = n.back.s[3][3];

	box->back.s[1][3] = n.up.s[1][3];		 
	box->back.s[2][3] = n.up.s[2][3];
	box->back.s[3][3] = n.up.s[3][3];

	box->up.s[1][3] = n.front.s[1][3];			
	box->up.s[2][3] = n.front.s[2][3];
	box->up.s[3][3] = n.front.s[3][3];
}

//逆时针旋转右面 
void CRight(Cube* box)						
{
	Cube n;
	n = *box;
	CClockwise_Face(&box->right);

	box->up.s[1][3] = n.back.s[1][3];
	box->up.s[2][3] = n.back.s[2][3];
	box->up.s[3][3] = n.back.s[3][3];

	box->down.s[1][3] = n.front.s[1][3];
	box->down.s[2][3] = n.front.s[2][3];
	box->down.s[3][3] = n.front.s[3][3];

	box->front.s[1][3] = n.up.s[1][3];
	box->front.s[2][3] = n.up.s[2][3];
	box->front.s[3][3] = n.up.s[3][3];

	box->back.s[1][3] = n.down.s[1][3];
	box->back.s[2][3] = n.down.s[2][3];
	box->back.s[3][3] = n.down.s[3][3];

}


//顺时针旋转上面
void CTop(Cube* box)					
{
	Cube n;
	n = *box;
	Clockwise_Face(&box->up);
	box->front.s[1][1] = n.right.s[1][1];
	box->front.s[1][2] = n.right.s[1][2];
	box->front.s[1][3] = n.right.s[1][3];

	box->back.s[3][1] = n.left.s[1][3];
	box->back.s[3][2] = n.left.s[1][2];
	box->back.s[3][3] = n.left.s[1][1];

	box->left.s[1][1] = n.front.s[1][1];
	box->left.s[1][2] = n.front.s[1][2];
	box->left.s[1][3] = n.front.s[1][3];

	box->right.s[1][1] = n.back.s[3][3];
	box->right.s[1][2] = n.back.s[3][2];
	box->right.s[1][3] = n.back.s[3][1];

}

//逆时针旋转上面
void CCTop(Cube* box)					
{
	Cube n;
	n = *box;
	CClockwise_Face(&box->up);
	box->front.s[1][1] = n.left.s[1][1];
	box->front.s[1][2] = n.left.s[1][2];
	box->front.s[1][3] = n.left.s[1][3];

	box->back.s[3][1] = n.right.s[1][3];
	box->back.s[3][2] = n.right.s[1][2];
	box->back.s[3][3] = n.right.s[1][1];

	box->left.s[1][1] = n.back.s[3][3];
	box->left.s[1][2] = n.back.s[3][2];
	box->left.s[1][3] = n.back.s[3][1];

	box->right.s[1][1] = n.front.s[1][1];
	box->right.s[1][2] = n.front.s[1][2];
	box->right.s[1][3] = n.front.s[1][3];
}


//初始化面
void InitFace(Face* f, char e)			
{
	int i, j;
	for (i = 1; i <= 3; i++)
		for (j = 1; j <= 3; j++)
		{

			f->s[i][j] = e;
		}
}


//初始化魔方
void InitCube(Cube* box)				
{

	InitFace(&(box->up), 'y');

	InitFace(&(box->down), 'w');

	InitFace(&(box->front), 'b');

	InitFace(&(box->back), 'g');

	InitFace(&(box->left), 'o');

	InitFace(&(box->right), 'r');
}

//打印面 
void PrintFace(Face* f)					
{
	int i, j;
	for (i = 1; i <= 3; i++)
	{
		for (j = 1; j <= 3; j++)
			printf("%c", f->s[i][j]);
		printf("\n");
	}
}


// 打印魔方 
void PrintCube(Cube* box)			
{
	printf("\n顶面颜色:\n");
	PrintFace(&box->up);
	printf("\n底面颜色:\n");
	PrintFace(&box->down);
	printf("\n前面颜色:\n");
	PrintFace(&box->front);
	printf("\n后面颜色:\n");
	PrintFace(&box->back);
	printf("\n左面颜色:\n");
	PrintFace(&box->left);
	printf("\n右边颜色:\n");
	PrintFace(&box->right);
}



//打乱魔方
void Disrupt(Cube* box)					
{
	Cfront(box);
	CTop(box);
	Back(box);
	CTop(box);
	CTop(box);
	Cfront(box);
	CLeft(box);

}

//底面十字 
void BottomCross(Cube* box)						
{
	while (!((box->down.s[1][2] == 'w' && box->front.s[3][2] == 'b')
		&& (box->down.s[2][1] == 'w' && box->left.s[3][2] == 'o')
		&& (box->down.s[2][3] == 'w' && box->right.s[3][2] == 'r')
		&& (box->down.s[3][2] == 'w' && box->back.s[1][2] == 'g')))
	{

		
		switch (box->down.s[1][2])
		{
		case 'w': 
			switch (box->front.s[3][2])
			{
			case 'b':
				break;
			case 'o':
				Cfront(box);
				Cfront(box);
				CTop(box);
				Left(box);
				Left(box);
				break;
			case 'r':
				CCfront(box);
				CCfront(box);
				CCTop(box);
				CRight(box);
				CRight(box);


				break;
			case 'g':
				Cfront(box);
				Cfront(box);
				CTop(box);
				CTop(box);
				Back(box);
				Back(box);


				break;
			default:
				break;
			}
			break;
		case 'b':  
			switch (box->front.s[3][2])
			{
			case 'w':
				CCfront(box);
				Right(box);
				Cfront(box);
				CRight(box);
				CCfront(box);
				CCfront(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->front.s[3][2])
			{
			case 'w':
				Cfront(box);
				Left(box);
				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->front.s[3][2])
			{
			case 'w':
				CCfront(box);
				CRight(box);
				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->front.s[3][2])
			{
			case 'w':
				CCfront(box);
				CCfront(box);
				CCTop(box);
				Right(box);
				CBack(box);
				CRight(box);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
		

		switch (box->down.s[2][3])
		{
		case 'w':
			switch (box->right.s[3][2])
			{
			case 'b':
				Right(box);
				Right(box);
				CTop(box);
				Cfront(box);
				Cfront(box);
				break;
			case 'o':
				Right(box);
				Right(box);
				Cfront(box);
				Cfront(box);
				Left(box);
				Left(box);

				break;
			case 'r':
				break;
			case 'g':
				Right(box);
				Right(box);
				CCTop(box);
				Back(box);
				Back(box);
				break;
			default:
				break;
			}
			break;

		case 'b':  
			switch (box->right.s[3][2])
			{
			case 'w':
				Right(box);
				Cfront(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->right.s[3][2])
			{
			case 'w':
				CRight(box);
				CBack(box);
				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->right.s[3][2])
			{
			case 'w':
				Right(box);
				Right(box);
				CTop(box);
				Cfront(box);
				Right(box);
				CCfront(box);
				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->right.s[3][2])
			{
			case 'w':
				CRight(box);
				Back(box);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		
		switch (box->down.s[3][2])
		{
		case 'w':
			switch (box->back.s[1][2])
			{
			case 'b':
				Back(box);
				Back(box);
				CTop(box);
				CTop(box);
				Cfront(box);
				Cfront(box);
				break;
			case 'o':
				Back(box);
				Back(box);
				CCTop(box);
				Left(box);
				Left(box);
				break;
			case 'r':
				Back(box);
				Back(box);
				CTop(box);
				Right(box);
				Right(box);
				break;
			case 'g':
				break;
			default:
				break;
			}
			break;

		case 'b':  
			switch (box->back.s[1][2])
			{
			case 'w':
				Back(box);
				Back(box);
				CTop(box);
				CRight(box);
				Cfront(box);
				Right(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->back.s[1][2])
			{
			case 'w':
				CBack(box);
				CLeft(box);
				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->back.s[1][2])
			{
			case 'w':
				Back(box);
				Right(box);

				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->back.s[1][2])
			{
			case 'w':
				Back(box);
				CRight(box);
				CCTop(box);
				Back(box);
				Back(box);
				Right(box);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		switch (box->down.s[2][1])
		{
		case 'w':
			switch (box->left.s[3][2])
			{
			case 'b':
				CLeft(box);
				CLeft(box);
				CCTop(box);
				Cfront(box);
				Cfront(box);

				break;
			case 'o':
				break;
			case 'r':
				Left(box);
				Left(box);
				CTop(box);
				CTop(box);
				Right(box);
				Right(box);

				break;
			case 'g':
				Left(box);
				Left(box);
				CTop(box);
				Back(box);
				Back(box);
				break;
			default:
				break;
			}
			break;

		case 'b': 
			switch (box->left.s[3][2])
			{
			case 'w':
				CLeft(box);
				CCfront(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->left.s[3][2])
			{
			case 'w':
				Back(box);
				Back(box);
				CCTop(box);
				CCfront(box);
				Left(box);
				Cfront(box);

				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->left.s[3][2])
			{
			case 'w':
				Back(box);
				Back(box);
				CTop(box);
				CTop(box);
				Right(box);
				Right(box);


				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->left.s[3][2])
			{
			case 'w':
				Left(box);
				Back(box);

				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		switch (box->front.s[2][3])
		{
		case 'w':
			switch (box->right.s[2][1])
			{
			case 'b':

				Right(box);
				CTop(box);
				CRight(box);
				Cfront(box);
				Cfront(box);

				break;
			case 'o':
				Right(box);
				CTop(box);
				CTop(box);
				CRight(box);
				Left(box);
				Left(box);
				break;
			case 'r':
				CRight(box);
				break;
			case 'g':
				Right(box);
				CCTop(box);
				CRight(box);
				Back(box);
				Back(box);
				break;
			default:
				break;
			}
			break;

		case 'b':
			switch (box->right.s[2][1])
			{
			case 'w':
				Cfront(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->right.s[2][1])
			{
			case 'w':

				CCfront(box);
				CCTop(box);
				Cfront(box);
				Left(box);
				Left(box);


				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->right.s[2][1])
			{
			case 'w':
				CCfront(box);
				CCTop(box);
				Cfront(box);
				Right(box);
				Right(box);


				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->right.s[2][1])
			{
			case 'w':
				CCfront(box);
				CCTop(box);
				CCTop(box);
				Cfront(box);
				Back(box);
				Back(box);

				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		switch (box->front.s[2][1])
		{
		case 'w':
			switch (box->left.s[2][3])
			{
			case 'b':

				CLeft(box);
				CCTop(box);
				Left(box);
				Cfront(box);
				Cfront(box);

				break;
			case 'o':
				Left(box);
				break;
			case 'r':
				Cfront(box);
				Cfront(box);
				Right(box);
				CCfront(box);
				CCfront(box);

				break;
			case 'g':
				CLeft(box);
				CCTop(box);
				Left(box);
				Back(box);
				Back(box);
				break;
			default:
				break;
			}
			break;

		case 'b':
			switch (box->left.s[2][3])
			{
			case 'w':
				CCfront(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->left.s[2][3])
			{
			case 'w':

				Cfront(box);
				CTop(box);
				CCfront(box);
				Left(box);
				Left(box);


				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->left.s[2][3])
			{
			case 'w':
				Cfront(box);
				CCTop(box);
				Cfront(box);
				Right(box);
				Right(box);
				break;
			default:
				break;
			}
			break;
		case 'g':
			switch (box->left.s[2][3])
			{
			case 'w':
				Cfront(box);
				CCTop(box);
				CCTop(box);
				CCfront(box);
				Back(box);
				Back(box);

				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		switch (box->back.s[2][1])
		{
		case 'w':
			switch (box->left.s[2][1])
			{
			case 'b':

				Left(box);
				CCTop(box);
				CLeft(box);
				Cfront(box);
				Cfront(box);

				break;
			case 'o':
				CLeft(box);
				break;
			case 'r':
				Left(box);
				CTop(box);
				CTop(box);
				CLeft(box);
				Right(box);
				Right(box);
				break;
			case 'g':
				Left(box);
				CTop(box);
				CLeft(box);
				Back(box);
				Back(box);
				break;
			default:
				break;
			}
			break;

		case 'b':
			switch (box->left.s[2][1])
			{
			case 'w':
				Left(box);
				Left(box);
				CCfront(box);
				CLeft(box);
				CLeft(box);

				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->left.s[2][1])
			{
			case 'w':

				CBack(box);
				CCTop(box);
				Back(box);
				Left(box);
				Left(box);


				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->left.s[2][1])
			{
			case 'w':
				CBack(box);
				CTop(box);
				Back(box);
				Right(box);
				Right(box);


				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->left.s[2][1])
			{
			case 'w':
				Back(box);

				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
		switch (box->back.s[2][3])
		{
		case 'w':
			switch (box->right.s[2][3])
			{
			case 'b':

				CRight(box);
				CTop(box);
				Right(box);
				Cfront(box);
				Cfront(box);

				break;
			case 'o':
				Back(box);
				Back(box);
				CLeft(box);
				CBack(box);
				CBack(box);


				break;
			case 'r':
				Right(box);
				break;
			case 'g':
				CRight(box);
				CCTop(box);
				Right(box);
				Back(box);
				Back(box);
				break;
			default:
				break;
			}
			break;

		case 'b':
			switch (box->right.s[2][3])
			{
			case 'w':
				Back(box);
				CTop(box);
				CTop(box);
				CBack(box);
				Cfront(box);
				Cfront(box);

				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->right.s[2][3])
			{
			case 'w':

				Back(box);
				CCTop(box);
				CBack(box);
				Left(box);
				Left(box);


				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->right.s[2][3])
			{
			case 'w':
				Back(box);
				CTop(box);
				CBack(box);
				Right(box);
				Right(box);


				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->right.s[2][3])
			{
			case 'w':
				CBack(box);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		switch (box->up.s[3][2])
		{
		case 'w': 
			switch (box->front.s[1][2])
			{
			case 'b':
				Cfront(box);
				Cfront(box);
				break;
			case 'o':

				CTop(box);
				Left(box);
				Left(box);
				break;
			case 'r':

				CCTop(box);
				CRight(box);
				CRight(box);


				break;
			case 'g':

				CTop(box);
				CTop(box);
				Back(box);
				Back(box);


				break;
			default:
				break;
			}
			break;
		case 'b':
			switch (box->front.s[1][2])
			{
			case 'w':

				CTop(box);
				Left(box);
				CCfront(box);
				CLeft(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->front.s[1][2])
			{
			case 'w':
				CCfront(box);
				Left(box);
				Cfront(box);
				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->front.s[1][2])
			{
			case 'w':
				Cfront(box);
				CRight(box);
				Cfront(box);

				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->front.s[1][2])
			{
			case 'w':
				Cfront(box);
				Right(box);
				CCTop(box);
				CRight(box);
				CCfront(box);
				Back(box);
				Back(box);

				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		switch (box->up.s[2][3])
		{
		case 'w':
			switch (box->right.s[1][2])
			{
			case 'b':

				CTop(box);
				Cfront(box);
				Cfront(box);
				break;
			case 'o':

				CTop(box);
				CTop(box);
				Left(box);
				Left(box);

				break;
			case 'r':
				CRight(box);
				CRight(box);
				break;
			case 'g':

				CCTop(box);
				CBack(box);
				CBack(box);
				break;
			default:
				break;
			}
			break;

		case 'b':
			switch (box->right.s[1][2])
			{
			case 'w':
				CRight(box);
				Cfront(box);
				Right(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->right.s[1][2])
			{
			case 'w':
				CRight(box);
				CCfront(box);
				CTop(box);
				Right(box);
				Cfront(box);
				Left(box);
				Left(box);


				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->right.s[1][2])
			{
			case 'w':

				CTop(box);
				Cfront(box);
				CRight(box);
				CCfront(box);
				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->right.s[1][2])
			{
			case 'w':
				Right(box);
				CBack(box);
				Right(box);

				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		switch (box->up.s[1][2])
		{
		case 'w':
			switch (box->back.s[3][2])
			{
			case 'b':

				CTop(box);
				CTop(box);
				Cfront(box);
				Cfront(box);
				break;
			case 'o':

				CCTop(box);
				Left(box);
				Left(box);
				break;
			case 'r':

				CTop(box);
				Right(box);
				Right(box);
				break;
			case 'g':
				Back(box);
				Back(box);

				break;
			default:
				break;
			}
			break;

		case 'b':
			switch (box->back.s[3][2])
			{
			case 'w':
				Back(box);
				Back(box);
				Cfront(box);
				CRight(box);
				Cfront(box);
				Right(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->back.s[3][2])
			{
			case 'w':

				Back(box);
				CLeft(box);
				CBack(box);

				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->back.s[3][2])
			{
			case 'w':
				CBack(box);
				Right(box);
				Back(box);

				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->back.s[3][2])
			{
			case 'w':

				CTop(box);
				Right(box);
				CBack(box);
				CRight(box);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		switch (box->up.s[2][1])
		{
		case 'w':
			switch (box->left.s[1][2])
			{
			case 'b':

				CCTop(box);
				Cfront(box);
				Cfront(box);

				break;
			case 'o':
				Left(box);
				Left(box);
				break;
			case 'r':

				CTop(box);
				CTop(box);
				Right(box);
				Right(box);

				break;
			case 'g':

				CTop(box);
				Back(box);
				Back(box);
				break;
			default:
				break;
			}
			break;

		case 'b':  
			switch (box->left.s[1][2])
			{
			case 'w':
				Left(box);
				CCfront(box);
				CLeft(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->left.s[1][2])
			{
			case 'w':

				CCTop(box);
				CCfront(box);
				Left(box);
				Cfront(box);

				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->left.s[1][2])
			{
			case 'w':

				CTop(box);
				Cfront(box);
				CRight(box);
				CCfront(box);


				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->left.s[1][2])
			{
			case 'w':
				CLeft(box);
				Back(box);
				Left(box);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

	}

}


//底部角块还原
void BottomCornerReduction(Cube* box)				
{
	while (!((box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')
		&& (box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')
		&& (box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')
		&& (box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')))
	{
		if ((box->front.s[3][1] == 'w') || (box->left.s[3][3] == 'w') || (box->down.s[1][1] == 'w' && ((box->front.s[3][1] != 'b') || (box->left.s[3][3] != 'o'))))
		{
			CTop(box);
			Cfront(box);
			CCTop(box);
			CCfront(box);
		}

		if ((box->front.s[3][3] == 'w') || (box->right.s[3][1] == 'w') || (box->down.s[1][3] == 'w' && !((box->front.s[3][3] == 'b') && (box->right.s[3][1] == 'r'))))
		{
			CTop(box);
			Right(box);
			CCTop(box);
			CRight(box);
		}
		if ((box->right.s[3][3] == 'w') || (box->back.s[1][3] == 'w') || (box->down.s[3][3] == 'w' && !((box->right.s[3][3] == 'r') && (box->back.s[1][3] == 'g'))))
		{
			CTop(box);
			Back(box);
			CCTop(box);
			CBack(box);
		}
		if ((box->left.s[3][1] == 'w') || (box->back.s[1][1] == 'w') || (box->down.s[3][1] == 'w' && !((box->left.s[3][1] == 'o') && (box->back.s[1][1] == 'g'))))
		{
			CTop(box);
			Left(box);
			CCTop(box);
			CLeft(box);
		}

		switch (box->front.s[1][3])
		{
		case 'w':
			if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'b') {
				CTop(box);
				while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
					CTop(box);
					Cfront(box);
					CCTop(box);
					CCfront(box);
				}
			}
			else if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'r') {
				CTop(box);
				Right(box);
				CCTop(box);
				CRight(box);

			}
			else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'o') {
				CTop(box);
				CTop(box);
				CTop(box);
				Left(box);
				CCTop(box);
				CLeft(box);

			}
			else if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'g') {
				CCTop(box);
				CTop(box);
				Back(box);
				CCTop(box);
				CBack(box);


			}

			break;
		case 'b':
			if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'w') {
				while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
					CTop(box);
					Right(box);
					CCTop(box);
					CRight(box);
				}
			}
			else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'o') {
				CTop(box);
				while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
					CTop(box);
					Left(box);
					CCTop(box);
					CLeft(box);
				}
			}
			break;
		case 'r':
			if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'b') {
				while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
					CTop(box);
					Cfront(box);
					CCTop(box);
					CCfront(box);
				}
			}
			else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'w') {
				CCTop(box);
				while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
					CTop(box);
					Back(box);
					CCTop(box);
					CBack(box);
				}
			}
			break;
		case 'o':
			if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'w') {
				CTop(box);
				while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
					CTop(box);
					Cfront(box);
					CCTop(box);
					CCfront(box);
				}
			}
			else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'g') {
				CCTop(box);
				CCTop(box);

				while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
					CTop(box);
					Left(box);
					CCTop(box);
					CLeft(box);
				}
			}
			break;
		case 'g':
			if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'r') {
				CCTop(box);
				while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
					CTop(box);
					Back(box);
					CCTop(box);
					CBack(box);
				}
			}
			else if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'w') {
				CCTop(box);
				CCTop(box);

				while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
					CTop(box);
					Left(box);
					CCTop(box);
					CLeft(box);
				}
			}
			break;
		default:
			break;
		}

		if (box->up.s[3][1] == 'w' || box->front.s[1][1] == 'w' || box->left.s[1][3] == 'w') {
			CCTop(box);
			switch (box->front.s[1][3])
			{
			case 'w':
				if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'b') {
					CTop(box);
					CTop(box);
					Cfront(box);
					CCTop(box);
					CCfront(box);


				}
				else if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'r') {
					CTop(box);
					Right(box);
					CCTop(box);
					CRight(box);
				}
				else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'o') {
					CTop(box);
					CTop(box);
					CTop(box);
					Left(box);
					CCTop(box);
					CLeft(box);
				}
				else if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'g') {
					CCTop(box);
					CTop(box);
					Back(box);
					CCTop(box);
					CBack(box);
				}

				break;
			case 'b':
				if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'w') {
					while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
						CTop(box);
						Right(box);
						CCTop(box);
						CRight(box);
					}
				}
				else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'o') {
					CTop(box);
					while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
						CTop(box);
						Left(box);
						CCTop(box);
						CLeft(box);
					}
				}



				break;
			case 'r':
				if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'b') {
					while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
						CTop(box);
						Cfront(box);
						CCTop(box);
						CCfront(box);
					}
				}
				else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'w') {
					CCTop(box);
					while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
						CTop(box);
						Back(box);
						CCTop(box);
						CBack(box);
					}
				}
				break;
			case 'o':
				if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'w') {
					CTop(box);
					while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
						CTop(box);
						Cfront(box);
						CCTop(box);
						CCfront(box);
					}
				}
				else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'g') {
					CCTop(box);
					CCTop(box);

					while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
						CTop(box);
						Left(box);
						CCTop(box);
						CLeft(box);
					}
				}
				break;
			case 'g':
				if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'r') {
					CCTop(box);
					while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
						CTop(box);
						Back(box);
						CCTop(box);
						CBack(box);
					}
				}
				else if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'w') {
					CCTop(box);
					CCTop(box);

					while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
						CTop(box);
						Left(box);
						CCTop(box);
						CLeft(box);
					}
				}
				break;
			default:
				break;
			}
		}
		if (box->up.s[1][1] == 'w' || box->back.s[3][1] == 'w' || box->left.s[1][1] == 'w') {
			CCTop(box);
			CCTop(box);
			switch (box->front.s[1][3])
			{
			case 'w':
				if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'b') {
					CTop(box);
					CTop(box);
					Cfront(box);
					CCTop(box);
					CCfront(box);
				}
				else if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'r') {
					CTop(box);
					Right(box);
					CCTop(box);
					CRight(box);

				}
				else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'o') {
					CTop(box);
					CTop(box);
					CTop(box);
					Left(box);
					CCTop(box);
					CLeft(box);
				}
				else if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'g') {
					CCTop(box);
					CTop(box);
					Back(box);
					CCTop(box);
					CBack(box);
				}

				break;
			case 'b':
				if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'w') {
					while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
						CTop(box);
						Right(box);
						CCTop(box);
						CRight(box);
					}
				}
				else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'o') {
					CTop(box);
					while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
						CTop(box);
						Left(box);
						CCTop(box);
						CLeft(box);
					}
				}
				break;
			case 'r':
				if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'b') {
					while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
						CTop(box);
						Cfront(box);
						CCTop(box);
						CCfront(box);
					}
				}
				else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'w') {
					CCTop(box);
					while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
						CTop(box);
						Back(box);
						CCTop(box);
						CBack(box);
					}
				}
				break;
			case 'o':
				if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'w') {
					CTop(box);
					while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
						CTop(box);
						Cfront(box);
						CCTop(box);
						CCfront(box);
					}
				}
				else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'g') {
					CCTop(box);
					CCTop(box);

					while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
						CTop(box);
						Left(box);
						CCTop(box);
						CLeft(box);
					}
				}
				break;
			case 'g':
				if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'r') {
					CCTop(box);
					while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
						CTop(box);
						Back(box);
						CCTop(box);
						CBack(box);
					}
				}
				else if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'w') {
					CCTop(box);
					CCTop(box);

					while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
						CTop(box);
						Left(box);
						CCTop(box);
						CLeft(box);
					}
				}
				break;
			default:
				break;
			}

		}
		if (box->up.s[1][3] == 'w' || box->back.s[3][3] == 'w' || box->right.s[1][3] == 'w') {
			CTop(box);
			switch (box->front.s[1][3])
			{
			case 'w':
				if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'b') {
					CTop(box);
					CTop(box);
					Cfront(box);
					CCTop(box);
					CCfront(box);


				}
				else if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'r') {
					CTop(box);
					Right(box);
					CCTop(box);
					CRight(box);

				}
				else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'o') {
					CTop(box);
					CTop(box);
					CTop(box);
					Left(box);
					CCTop(box);
					CLeft(box);

				}
				else if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'g') {
					CCTop(box);
					CTop(box);
					Back(box);
					CCTop(box);
					CBack(box);


				}

				break;
			case 'b':
				if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'w') {
					while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
						CTop(box);
						Right(box);
						CCTop(box);
						CRight(box);
					}
				}
				else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'o') {
					CTop(box);
					while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
						CTop(box);
						Left(box);
						CCTop(box);
						CLeft(box);
					}
				}
				break;
			case 'r':
				if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'b') {
					while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
						CTop(box);
						Cfront(box);
						CCTop(box);
						CCfront(box);
					}
				}
				else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'w') {
					CCTop(box);
					while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
						CTop(box);
						Back(box);
						CCTop(box);
						CBack(box);
					}
				}
				break;
			case 'o':
				if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'w') {
					CTop(box);
					while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
						CTop(box);
						Cfront(box);
						CCTop(box);
						CCfront(box);
					}
				}
				else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'g') {
					CCTop(box);
					CCTop(box);

					while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
						CTop(box);
						Left(box);
						CCTop(box);
						CLeft(box);
					}
				}
				break;
			case 'g':
				if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'r') {
					CCTop(box);
					while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
						CTop(box);
						Back(box);
						CCTop(box);
						CBack(box);
					}
				}
				else if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'w') {
					CCTop(box);
					CCTop(box);

					while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
						CTop(box);
						Left(box);
						CCTop(box);
						CLeft(box);
					}
				}
				break;
			default:
				break;
			}
		}
	}


}
//中棱归位
void MedianEdge(Cube* box)				
{
	int counter = 0;
	while (!((box->front.s[2][1] == 'b' && box->front.s[2][3] == 'b')
		&& (box->left.s[2][1] == 'o' && box->left.s[2][3] == 'o')
		&& (box->back.s[2][1] == 'g' && box->back.s[2][3] == 'g')
		&& (box->right.s[2][1] == 'r' && box->right.s[2][3] == 'r')))
	{
		counter++;
		switch (box->front.s[1][2])
		{
		case 'b':
			switch (box->up.s[3][2])
			{
			case 'r':
				CTop(box);
				Right(box);
				CCTop(box);
				CRight(box);
				CCTop(box);
				CCfront(box);
				CTop(box);
				Cfront(box);
				break;
			case 'o':
				CCTop(box);
				CLeft(box);
				CTop(box);
				Left(box);
				CTop(box);
				Cfront(box);
				CCTop(box);
				CCfront(box);
				break;
			default:
				break;
			}
		case 'r':
			switch (box->up.s[3][2])
			{
			case 'g':
				CCTop(box);
				CTop(box);
				Back(box);
				CCTop(box);
				CBack(box);
				CCTop(box);
				CRight(box);
				CTop(box);
				Right(box);
				break;
			case 'b':
				CCTop(box);
				CCTop(box);
				CCfront(box);
				CTop(box);
				Cfront(box);
				CTop(box);
				Right(box);
				CCTop(box);
				CRight(box);
				break;
			default:
				break;
			}
			break;
		case 'g':
			switch (box->up.s[3][2])
			{
			case 'r':
				CTop(box);
				CTop(box);
				CCTop(box);
				CRight(box);
				CTop(box);
				Right(box);
				CTop(box);
				Back(box);
				CCTop(box);
				CBack(box);
				break;
			case 'o':
				CTop(box);
				CTop(box);
				CTop(box);
				Left(box);
				CCTop(box);
				CLeft(box);
				CCTop(box);
				CBack(box);
				CTop(box);
				Back(box);
				break;

			default:
				break;
			}
			break;
		case 'o':
			switch (box->up.s[3][2])
			{
			case 'b':
				CTop(box);
				break;
			case 'g':
				CTop(box);
				CTop(box);
				Cfront(box);
				CCTop(box);
				CCfront(box);
				CCTop(box);
				CLeft(box);
				CTop(box);
				Left(box);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		if ((box->right.s[1][2] == 'r' && box->up.s[2][3] == 'b')
			|| (box->right.s[1][2] == 'r' && box->up.s[2][3] == 'g')
			|| (box->right.s[1][2] == 'b' && box->up.s[2][3] == 'r')
			|| (box->right.s[1][2] == 'b' && box->up.s[2][3] == 'o')
			|| (box->right.s[1][2] == 'o' && box->up.s[2][3] == 'g')
			|| (box->right.s[1][2] == 'o' && box->up.s[2][3] == 'b')
			|| (box->right.s[1][2] == 'g' && box->up.s[2][3] == 'r')
			|| (box->right.s[1][2] == 'g' && box->up.s[2][3] == 'o'))
		{
			CTop(box);
		}
		if ((box->back.s[3][2] == 'r' && box->up.s[1][2] == 'b')
			|| (box->back.s[3][2] == 'r' && box->up.s[1][2] == 'g')
			|| (box->back.s[3][2] == 'b' && box->up.s[1][2] == 'r')
			|| (box->back.s[3][2] == 'b' && box->up.s[1][2] == 'o')
			|| (box->back.s[3][2] == 'o' && box->up.s[1][2] == 'g')
			|| (box->back.s[3][2] == 'o' && box->up.s[1][2] == 'b')
			|| (box->back.s[3][2] == 'g' && box->up.s[1][2] == 'r')
			|| (box->back.s[3][2] == 'g' && box->up.s[1][2] == 'o'))
		{
			CTop(box);
			CTop(box);

		}
		if ((box->left.s[1][2] == 'r' && box->up.s[2][1] == 'b')
			|| (box->left.s[1][2] == 'r' && box->up.s[2][1] == 'g')
			|| (box->left.s[1][2] == 'b' && box->up.s[2][1] == 'r')
			|| (box->left.s[1][2] == 'b' && box->up.s[2][1] == 'o')
			|| (box->left.s[1][2] == 'o' && box->up.s[2][1] == 'g')
			|| (box->left.s[1][2] == 'o' && box->up.s[2][1] == 'b')
			|| (box->left.s[1][2] == 'g' && box->up.s[2][1] == 'r')
			|| (box->left.s[1][2] == 'g' && box->up.s[2][1] == 'o'))
		{
			CCTop(box);
		}
		if (counter > 30)
		{
			if ((box->front.s[2][3] == 'g' && box->right.s[2][1] == 'o')
				|| (box->front.s[2][3] == 'r' && box->right.s[2][1] == 'b')
				|| (box->front.s[2][3] == 'r' && box->right.s[2][1] == 'g')
				|| (box->front.s[2][3] == 'b' && box->right.s[2][1] == 'r')
				|| (box->front.s[2][3] == 'b' && box->right.s[2][1] == 'o')
				|| (box->front.s[2][3] == 'o' && box->right.s[2][1] == 'g')
				|| (box->front.s[2][3] == 'o' && box->right.s[2][1] == 'b')
				|| (box->front.s[2][3] == 'g' && box->right.s[2][1] == 'r'))
			{
				CTop(box);
				Right(box);
				CCTop(box);
				CRight(box);
				CCTop(box);
				CCfront(box);
				CTop(box);
				Cfront(box);
			}

			if ((box->left.s[2][3] == 'g' && box->front.s[2][1] == 'o')
				|| (box->left.s[2][3] == 'r' && box->front.s[2][1] == 'b')
				|| (box->left.s[2][3] == 'r' && box->front.s[2][1] == 'g')
				|| (box->left.s[2][3] == 'b' && box->front.s[2][1] == 'r')
				|| (box->left.s[2][3] == 'b' && box->front.s[2][1] == 'o')
				|| (box->left.s[2][3] == 'o' && box->front.s[2][1] == 'g')
				|| (box->left.s[2][3] == 'o' && box->front.s[2][1] == 'b')
				|| (box->left.s[2][3] == 'g' && box->front.s[2][1] == 'r'))
			{
				CTop(box);
				Cfront(box);
				CCTop(box);
				CCfront(box);
				CCTop(box);
				CLeft(box);
				CTop(box);
				Left(box);
			}
			if ((box->back.s[2][3] == 'g' && box->right.s[2][3] == 'o')
				|| (box->back.s[2][3] == 'r' && box->right.s[2][3] == 'b')
				|| (box->back.s[2][3] == 'r' && box->right.s[2][3] == 'g')
				|| (box->back.s[2][3] == 'b' && box->right.s[2][3] == 'r')
				|| (box->back.s[2][3] == 'b' && box->right.s[2][3] == 'o')
				|| (box->back.s[2][3] == 'o' && box->right.s[2][3] == 'g')
				|| (box->back.s[2][3] == 'o' && box->right.s[2][3] == 'b')
				|| (box->back.s[2][3] == 'g' && box->right.s[2][3] == 'r'))
			{
				CTop(box);
				Back(box);
				CCTop(box);
				CBack(box);
				CCTop(box);
				CRight(box);
				CTop(box);
				Right(box);
			}
			if ((box->back.s[2][1] == 'g' && box->left.s[2][1] == 'o')
				|| (box->back.s[2][1] == 'r' && box->left.s[2][1] == 'b')
				|| (box->back.s[2][1] == 'r' && box->left.s[2][1] == 'g')
				|| (box->back.s[2][1] == 'b' && box->left.s[2][1] == 'r')
				|| (box->back.s[2][1] == 'b' && box->left.s[2][1] == 'o')
				|| (box->back.s[2][1] == 'o' && box->left.s[2][1] == 'g')
				|| (box->back.s[2][1] == 'o' && box->left.s[2][1] == 'b')
				|| (box->back.s[2][1] == 'g' && box->left.s[2][1] == 'r'))
			{
				CTop(box);
				Left(box);
				CCTop(box);
				CLeft(box);
				CCTop(box);
				CBack(box);
				CTop(box);
				Back(box);
			}

		}
	}

}
//顶角十字
void TopCross(Cube* box) {
	while (!(box->up.s[1][2] == 'y' && box->up.s[2][1] == 'y'
		&& box->up.s[2][3] == 'y' && box->up.s[3][2] == 'y'))
	{
		if (box->up.s[1][2] != 'y' && box->up.s[2][1] != 'y' && box->up.s[2][3] != 'y' && box->up.s[3][2] != 'y' && box->front.s[1][2] == 'y' && box->right.s[1][2] == 'y')
		{
			Cfront(box);
			Right(box);
			CTop(box);
			CRight(box);
			CCTop(box);
			CCfront(box);

			Cfront(box);
			Right(box);
			CTop(box);
			CRight(box);
			CCTop(box);
			CCfront(box);
		}
		if (box->up.s[1][2] == 'y' && box->up.s[2][1] == 'y' && box->front.s[1][2] == 'y' && box->right.s[1][2] == 'y')
		{
			Cfront(box);
			Right(box);
			CTop(box);
			CRight(box);
			CCTop(box);
			CCfront(box);

			Cfront(box);
			Right(box);
			CTop(box);
			CRight(box);
			CCTop(box);
			CCfront(box);
		}
		if (box->up.s[2][1] == 'y' && box->up.s[2][3] == 'y' && box->front.s[1][2] == 'y')
		{
			Cfront(box);
			Right(box);
			CTop(box);
			CRight(box);
			CCTop(box);
			CCfront(box);

		}
		if (box->up.s[1][2] == 'y' && box->up.s[3][2] == 'y' && box->right.s[1][2] == 'y')
		{
			CTop(box);
		}
		if (box->up.s[1][2] == 'y' && box->up.s[3][2] == 'y' && box->left.s[1][2] == 'y')
		{
			CCTop(box);
		}
		if (box->up.s[2][1] == 'y' && box->up.s[3][2] == 'y' && box->back.s[3][2] == 'y' && box->right.s[1][2] == 'y')
		{
			CTop(box);
		}
		if (box->up.s[2][3] == 'y' && box->up.s[3][2] == 'y' && box->back.s[3][2] == 'y' && box->left.s[1][2] == 'y')
		{
			CTop(box);
			CTop(box);

		}
		if (box->up.s[2][3] == 'y' && box->up.s[1][2] == 'y' && box->left.s[1][2] == 'y')
		{
			CCTop(box);
		}
		if (box->up.s[2][3] == 'y' && box->up.s[1][2] == 'y' && box->right.s[1][2] == 'y')
		{
			CTop(box);
		}

	}

}

//顶角面
void Vertexface(Cube* box) 
{

	while (!(box->up.s[1][1] == 'y' && box->up.s[1][3] == 'y'
		&& box->up.s[3][1] == 'y' && box->up.s[3][3] == 'y'))
	{
		if (box->up.s[3][1] == 'y' || box->right.s[1][3] == 'y' || box->front.s[1][1] == 'y') {
			Right(box);
			CTop(box);
			CRight(box);
			CTop(box);
			Right(box);
			CTop(box);
			CTop(box);
			CRight(box);
		}
		if (box->up.s[3][3] == 'y' || box->right.s[1][1] == 'y' || box->front.s[1][3] == 'y') {
			CTop(box);
		}
		if (box->up.s[1][3] == 'y' || box->left.s[1][3] == 'y' || box->back.s[3][3] == 'y') {
			CTop(box);
			CTop(box);

		}
		if (box->up.s[1][1] == 'y' || box->left.s[1][1] == 'y' || box->front.s[3][1] == 'y') {
			CCTop(box);
		}


	}

}
//顶角还原
void VertexReduction(Cube* box) {

	while (!((box->front.s[1][1] == 'b' && box->front.s[1][3] == 'b')
		&& (box->left.s[1][1] == 'o' && box->left.s[1][3] == 'o')
		&& (box->back.s[1][1] == 'g' && box->back.s[1][3] == 'g')
		&& (box->right.s[1][1] == 'r' && box->right.s[1][3] == 'r')))
	{
		if (box->right.s[1][1] == box->right.s[1][3]) {
			CTop(box);
			Right(box);
			CBack(box);
			Right(box);
			Cfront(box);
			Cfront(box);
			CRight(box);
			Back(box);
			Right(box);
			Cfront(box);
			Cfront(box);
			Right(box);
			Right(box);

		}
		if (box->left.s[1][1] == box->left.s[1][3]) {
			CCTop(box);
			Right(box);
			CBack(box);
			Right(box);
			Cfront(box);
			Cfront(box);
			CRight(box);
			Back(box);
			Right(box);
			Cfront(box);
			Cfront(box);
			Right(box);
			Right(box);

		}
		if (box->back.s[3][1] == box->back.s[3][3]) {
			CTop(box);
			CTop(box);
			Right(box);
			CBack(box);
			Right(box);
			Cfront(box);
			Cfront(box);
			CRight(box);
			Back(box);
			Right(box);
			Cfront(box);
			Cfront(box);
			Right(box);
			Right(box);

		}
		Right(box);
		CBack(box);
		Right(box);
		Cfront(box);
		Cfront(box);
		CRight(box);
		Back(box);
		Right(box);
		Cfront(box);
		Cfront(box);
		Right(box);
		Right(box);


	}

}


//顶棱还原
void TopEdgeReduction(Cube* box) {

	while (!(box->front.s[1][2] == 'b' && box->left.s[1][2] == 'o'
		&& box->back.s[1][2] == 'g' && box->right.s[1][2] == 'r'))
	{
		if (box->front.s[1][2] == 'b') {
			Left(box);
			CCTop(box);
			Left(box);
			CTop(box);
			Left(box);
			CTop(box);
			Left(box);
			CCTop(box);
			CLeft(box);
			CCTop(box);
			Left(box);
			Left(box);
		}
		else if (box->left.s[1][2] == 'o') {
			Cfront(box);
			CCTop(box);
			Cfront(box);
			CTop(box);
			Cfront(box);
			CTop(box);
			Cfront(box);
			CCTop(box);
			CRight(box);
			CCTop(box);
			Cfront(box);
			Cfront(box);
		}
		else if (box->back.s[1][2] == 'g') {
			Right(box);
			CCTop(box);
			Right(box);
			CTop(box);
			Right(box);
			CTop(box);
			Right(box);
			CCTop(box);
			CRight(box);
			CCTop(box);
			Right(box);
			Right(box);

		}
		else if (box->right.s[1][2] == 'r') {
			Back(box);
			CCTop(box);
			Back(box);
			CTop(box);
			Back(box);
			CTop(box);
			Back(box);
			CCTop(box);
			CBack(box);
			CCTop(box);
			Back(box);
			Back(box);
		}
		else {
			Right(box);
			CCTop(box);
			Right(box);
			CTop(box);
			Right(box);
			CTop(box);
			Right(box);
			CCTop(box);
			CCTop(box);
			CCTop(box);
			Right(box);
			Right(box);
		}

	}

}

