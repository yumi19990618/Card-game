#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//設定參與遊戲的人所擁有的卡牌和賭金儲存的structure
typedef struct node
{
    int card[26];//一副牌最多可遊玩26局(52/2)
    int money;

} NODE;

/*設定讀卡函式*/
void read(int k)
{
    int a,b;
    a=(k%4);
    b=(k%13)+1;


    //讀卡牌花色
    switch(a)
    {
    case 0:
        printf("Spade ");
        break;
    case 1:
        printf("Heart ");
        break;
    case 2:
        printf("Diamand ");
        break;
    case 3:
        printf("Club ");
        break;
    }


//讀卡牌數字
    if(b<11)
    {
        printf("%d",b);
    }
    else
    {
        switch(b)
        {
            case 11:
                printf("J");
                break;
            case 12:
                printf("Q");
                break;
            case 13:
                printf("K");
               break;
        }
    }

    return;
}

/*設定比大小函式，並回傳結果*/
int compare_card(int com,int ply)
{
    int k;//確認最終誰比較大時回傳用的

    if((com%13)<(ply%13))
    {
        k=2;//player較大
    }
    else if((com%13)>(ply%13))
    {
        k=1;//computer較大
    }

    //數字相同，比花色
    else
    {
        if((com%4)<(ply%4))
        {
            k=1;//computer較大
        }
        else if((com%4)>(ply%4))
        {
            k=2;//player較大
        }
        else
        {
            k=3;//平手
        }
    }

    return k;//回傳比大小結果
}


int main()
{
    int card[52]; //儲存卡牌的陣列
    int check_card[52]= {0}; //確認發牌所使用的陣列
    int i=0;
    srand(time(NULL));//使每次回圈的random number不重複

    /*發牌不重複*/
    while(i<52)
    {
        card[i]=rand()%52;
        if(check_card[card[i]]==0)
        {
            check_card[card[i]]=1;
            i++;
        }
    }

    i=0;//將i讀入0以還原初始值

    /*將完成的卡牌代碼讀入deck_card.txt中*/
    FILE*input=fopen("deck_card.txt","w");//開啟deck_card.txt
    while(i<52)
    {
        fprintf(input,"%d\n",card[i]);//將card[i]的數值讀入deck_card 中
        i++;
    }
    fclose(input);//關閉deck_card.txt


    /*設定玩家和電腦遊戲儲存pointer */
    NODE*ply=(NODE*)malloc(sizeof(NODE));
    NODE*com=(NODE*)malloc(sizeof(NODE));


    int k=0;

    int n;//決定比大還是比小
    int r;//比大小結果
    com->money=30,ply->money=30;//設定賭金，玩家語電腦初始皆為30元
    i=1;
    int m;//存取每輪賭金數
    while(i<=26)
    {

        printf("Round %d\n",i);
        printf("You want...?1.High cards win\t2.low card win:");
        scanf("%d",&n);
        //依照順序發牌
        com->card[i]=card[k];

        ply->card[i]=card[k+1];
        k=k+2;
        r=compare_card(com->card[i],ply->card[i]);
        if((com->card[i])%13>(ply->card[i])%13)
        {
            m=(com->card[i])%13-(ply->card[i])%13;
        }

        else if((com->card[i])%13<(ply->card[i])%13)
        {
            m=(ply->card[i])%13-(com->card[i])%13;
        }
        else
        {
            m=10;
        }



        printf("\nComputer's card: ");
        read((com->card[i]));
        printf("\nPlayer's card: ");
        read((ply->card[i]));
        printf("\n\n");

        if(n==1)
        {
            switch(r)
            {
            case 1:
                printf("computer +1!!\n");
                com->money=(com->money)+m;
                ply->money=(ply->money)-m;
                break;
            case 2:
                printf("player +1!!\n");
                com->money=(com->money)-m;
                ply->money=(ply->money)+m;
                break;
            case 3:
                printf("Fair\n");
                break;
            }
        }

        else if(n==2)
        {
            switch(r)
            {
            case 1:
                printf("player +1!!\n");
                com->money=(com->money)-m;
                ply->money=(ply->money)+m;
                break;
            case 2:
                printf("computer +1!!\n");
                com->money=(com->money)+m;
                ply->money=(ply->money)-m;
                break;
            case 3:
                printf("Fair\n");
                break;
            }
        }

        printf("money:\ncomputer:%d\tplayer:%d\n",com->money,ply->money);
        if((com->money)<=0)
        {
            printf("player win!!\n");
            break;
        }
        if((ply->money)<=0)
        {
            printf("computer win!!\n");
            break;
        }
        printf("\n\n");//排版
        m=0;
        i++;

    }
    if(i==26)

    {
        printf("\nAll card had been dealt\n");
        if((ply->money)>(com->money))
        {
            printf("player win!!\n");
        }
        else if((ply->money)<(com->money))
        {
            printf("computer win!!\n");
        }
        else
        {
            printf("Fair\n");
        }
    }

    return 0;
}
