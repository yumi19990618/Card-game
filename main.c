#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//�]�w�ѻP�C�����H�Ҿ֦����d�P�M����x�s��structure
typedef struct node
{
    int card[26];//�@�ƵP�̦h�i�C��26��(52/2)
    int money;

} NODE;

/*�]�wŪ�d�禡*/
void read(int k)
{
    int a,b;
    a=(k%4);
    b=(k%13)+1;


    //Ū�d�P���
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


//Ū�d�P�Ʀr
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

/*�]�w��j�p�禡�A�æ^�ǵ��G*/
int compare_card(int com,int ply)
{
    int k;//�T�{�̲׽֤���j�ɦ^�ǥΪ�

    if((com%13)<(ply%13))
    {
        k=2;//player���j
    }
    else if((com%13)>(ply%13))
    {
        k=1;//computer���j
    }

    //�Ʀr�ۦP�A����
    else
    {
        if((com%4)<(ply%4))
        {
            k=1;//computer���j
        }
        else if((com%4)>(ply%4))
        {
            k=2;//player���j
        }
        else
        {
            k=3;//����
        }
    }

    return k;//�^�Ǥ�j�p���G
}


int main()
{
    int card[52]; //�x�s�d�P���}�C
    int check_card[52]= {0}; //�T�{�o�P�ҨϥΪ��}�C
    int i=0;
    srand(time(NULL));//�ϨC���^�骺random number������

    /*�o�P������*/
    while(i<52)
    {
        card[i]=rand()%52;
        if(check_card[card[i]]==0)
        {
            check_card[card[i]]=1;
            i++;
        }
    }

    i=0;//�NiŪ�J0�H�٭��l��

    /*�N�������d�P�N�XŪ�Jdeck_card.txt��*/
    FILE*input=fopen("deck_card.txt","w");//�}��deck_card.txt
    while(i<52)
    {
        fprintf(input,"%d\n",card[i]);//�Ncard[i]���ƭ�Ū�Jdeck_card ��
        i++;
    }
    fclose(input);//����deck_card.txt


    /*�]�w���a�M�q���C���x�spointer */
    NODE*ply=(NODE*)malloc(sizeof(NODE));
    NODE*com=(NODE*)malloc(sizeof(NODE));


    int k=0;

    int n;//�M�w��j�٬O��p
    int r;//��j�p���G
    com->money=30,ply->money=30;//�]�w����A���a�y�q����l�Ҭ�30��
    i=1;
    int m;//�s���C�������
    while(i<=26)
    {

        printf("Round %d\n",i);
        printf("You want...?1.High cards win\t2.low card win:");
        scanf("%d",&n);
        //�̷Ӷ��ǵo�P
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
        printf("\n\n");//�ƪ�
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
