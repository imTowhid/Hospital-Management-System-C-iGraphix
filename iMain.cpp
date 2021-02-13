#include "iGraphics.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>



typedef struct
{
    int dd,mm,yy;
} date;
typedef struct
{
    int ID;
    char name[21];
    int age;
    char sex;
    char blood[4];
    char address[21];
    char nationality[21];
    char contact[12];
    char dis_cat;
    char dis_des[50];
    int room;
    int bed;
    date dt;
} info;

info patient;

FILE *fp,*src,*rb,*dlt,*tmp,*tfp, *plist, *last, *cINF, *CTA, *tem, *ciin, *roFA, *roFP;

char *cIn = "Check In.txt";
char *cOut = "Check Out.txt";
char *room = "Room.txt";
char *temp = "Temp.txt";
char *cpy = "Copy.txt";
char *id_name = "ID.txt";
char *np = "A.txt";
char *listP = "ListP.txt";


char window=0,mode=0;
char id[]="p",str_id[20];
char pass[] = "p",str_pass[20];
char str[20];
int roomI[15], docP[10], disP[5];
int show, pmtr=0;
int len1,len2,match = 0,s=0,done = 0,count = 0;
char *mem[20];
char lpat[6][100];

char pstr[20][50];
int len[20],check[20];
char found[30][50];


void pass_word(void);
int Gen_id(void);
int id_match(void);
char* strtolower(char *str);
int searching(char *str,char *find);
int update_func(void);
int no_patient,total;
char in_info[100],out_info[100],sum[100];
char Room[18];
char bed[5][1];
int room_show=0;
int bed_show = 0;


void room_check(void)
{
	fp = fopen("Room.txt","r");
	int i,sk=0;
	char ch;
	char rm[3];
	for(i=0;i<18;i++)
	{
		fgets(rm,3,fp);
		if(!strcmp(rm,pstr[10]))
		{
			sk=1;int j=0;
			while((ch=fgetc(fp))!='\n')
			{
				if(ch=='v')
				{
					ch = fgetc(fp);
					bed[j][0] = ch;
					j++;
				}
			}
			fclose(fp);
			break;
		}
		fseek(fp,-3,SEEK_CUR);
		fseek(fp,18,SEEK_CUR);
	}

}
void info_check(void)
{
	fp = fopen(cIn,"r");
	src = fopen(id_name,"r");
	char ch;
	no_patient=0;
	total=0;
	while((ch = fgetc(fp))!=EOF)
	{
		if(ch == '\n')
			no_patient++;
	}
	fclose(fp);
	no_patient = no_patient/13;
	while(1)
	{
		ch = fgetc(src);
		if(ch == 32)
			total++;
		if(ch == EOF)
		{
			fclose(src);
			break;
		}
	}
	itoa(total,sum,10);
	itoa(no_patient,in_info,10);
	itoa(total - no_patient,out_info,10);
}

void roomsI(void)
{
    int ip=0, i, r=0;
    fp = fopen(cIn, "r");
    char ch;
    for(i=0; i<15; i++)
        roomI[i]=0;
    while(1){
        ch = fgetc(fp);
        if(ch==EOF)
            break;
        if(ch=='\n')
            ip++;
        if(ip==13)
            ip=0;
       if(ip==10){
           fseek(fp, -1, SEEK_CUR);
           fscanf(fp, "%d", &r);
           if(r==101)
            roomI[0]++;
           else if(r==102)
            roomI[1]++;
           else if(r==103)
            roomI[2]++;
           else if(r==104)
            roomI[3]++;
           else if(r==105)
            roomI[4]++;
           else if(r==201)
            roomI[5]++;
           else if(r==202)
            roomI[6]++;
           else if(r==203)
            roomI[7]++;
           else if(r==204)
            roomI[8]++;
           else if(r==205)
            roomI[9]++;
           else if(r==301)
            roomI[10]++;
           else if(r==302)
            roomI[11]++;
           else if(r==303)
            roomI[12]++;
           else if(r==304)
            roomI[13]++;
           else if(r==305)
            roomI[14]++;
       }
    }
    fclose(fp);

    int j;
    roFP = fopen("roomP.txt", "w");
    roFA = fopen("roomA.txt", "w");
    for(j=0; j<15; j++){
        fprintf(roFP, "%d\n", roomI[j]);
        fprintf(roFA, "%d\n", 5-roomI[j]);
    }
    fclose(roFA);
    fclose(roFP);

}

void patient_check_in(void)
{
    drawTexture(0,0, cinp);
	iSetColor(1950,1950,1950);
	iText(80,530,"HOME",GLUT_BITMAP_9_BY_15);
	iText(580,600,"PATIENT CHECK IN FORM",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1200,160,"DONE",GLUT_BITMAP_TIMES_ROMAN_24);

	if(match == 3)
	{
		iSetColor(1755,0,0);
		iText(1150,200,"Please fill up all the boxes!!!",GLUT_BITMAP_HELVETICA_18);
	}

	iSetColor(1900,1900,1900);
	iText(250,500,"DATE (dd/mm/yyyy)",GLUT_BITMAP_HELVETICA_18);
	iText(250,460,"NAME",GLUT_BITMAP_HELVETICA_18);
	iText(250,420,"AGE",GLUT_BITMAP_HELVETICA_18);
	iText(250,380,"SEX",GLUT_BITMAP_HELVETICA_18);
	iText(250,340,"BLOOD GROUP",GLUT_BITMAP_HELVETICA_18);
	iText(250,300,"ADDRESS",GLUT_BITMAP_HELVETICA_18);
	iText(250,260,"NATIONALITY",GLUT_BITMAP_HELVETICA_18);;
	iText(250,220,"CONTACT NO.",GLUT_BITMAP_HELVETICA_18);
	iText(250,180,"DISEASE CATAGORY",GLUT_BITMAP_HELVETICA_18);
	iText(250,140,"DESCRIPTION",GLUT_BITMAP_HELVETICA_18);
	iText(250,60,"ROOM",GLUT_BITMAP_HELVETICA_18);
	iText(250,20,"BED",GLUT_BITMAP_HELVETICA_18);
	iText(750,500,"ID",GLUT_BITMAP_HELVETICA_18);


	iText(750,400,"*DISEASE CATEGORY(Click to select)",GLUT_BITMAP_HELVETICA_18);
	iText(750,340,"1. CARDIAC",GLUT_BITMAP_HELVETICA_18);
	iText(750,310,"2. SKIN AND SEX",GLUT_BITMAP_HELVETICA_18);
	iText(750,280,"3. ORTHOPEDICS",GLUT_BITMAP_HELVETICA_18);
	iText(750,250,"4. MEDICINE",GLUT_BITMAP_HELVETICA_18);
	iText(750,220,"5. GYNECOLOGY",GLUT_BITMAP_HELVETICA_18);

	iSetColor(700, 700, 700);
	iRectangle(450,490,200,30);
	iRectangle(450,450,200,30);
	iRectangle(450,410,200,30);
	iRectangle(450,370,200,30);
	iRectangle(450,330,200,30);
	iRectangle(450,290,200,30);
	iRectangle(450,250,200,30);
	iRectangle(450,210,200,30);
	iRectangle(450,170,200,30);
	iRectangle(450,90,200,70);
	iRectangle(450,50,200,30);
	iRectangle(450,10,200,30);
	iRectangle(820,490,200,30);


	iSetColor(275, 238, 0);
	if(mode==12)
	iFilledRectangle(450,490,200,30);
	if(mode==1)
	iFilledRectangle(450,450,200,30);
	if(mode==2)
	iFilledRectangle(450,410,200,30);
	if(mode==3)
	iFilledRectangle(450,370,200,30);
	if(mode==4)
	iFilledRectangle(450,330,200,30);
	if(mode==5)
	iFilledRectangle(450,290,200,30);
	if(mode==6)
    iFilledRectangle(450,250,200,30);
    if(mode==7)
	iFilledRectangle(450,210,200,30);
	if(mode==13)
	iFilledRectangle(450,170,200,30);
	if(mode==9)
	iFilledRectangle(450,90,200,70);
	if(mode==10)
	iFilledRectangle(450,50,200,30);
	if(mode==11)
	iFilledRectangle(450,10,200,30);
	if(mode==8)
	iFilledRectangle(820,490,200,30);

	iSetColor(1900,1900,1900);
	iText(451,500 - 40*0,pstr[12],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*1,pstr[1],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*2,pstr[2],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*3,pstr[3],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*4,pstr[4],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*5,pstr[5],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*6,pstr[6],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*7,pstr[7],GLUT_BITMAP_HELVETICA_18);
	iText(540,500 - 40*8,pstr[8],GLUT_BITMAP_HELVETICA_18);
	iText(451,140,pstr[9],GLUT_BITMAP_HELVETICA_18);
	iText(451,60,pstr[10],GLUT_BITMAP_HELVETICA_18);
	iText(451,20,pstr[11],GLUT_BITMAP_HELVETICA_18);
	iText(828,502,pstr[0],GLUT_BITMAP_HELVETICA_18);

	if(done == 1)
	{
		iSetColor(0,900,0);
		iRectangle(500,300,500,200);
		iSetColor(255,255,255);
		iFilledRectangle(500.5,301,499,198);
		iSetColor(181,166,166);
		iFilledRectangle(499,260,502,40);
		iSetColor(80,116,122);
		iFilledRectangle(700,270,100,20);
		iSetColor(1955,1955,1955);
		iText(742,273,"Ok",GLUT_BITMAP_HELVETICA_18);
		iSetColor(1995,1920,1990);
		iText(530,390,"Checked in successfully! Patient infos recorded.",GLUT_BITMAP_HELVETICA_18);
	}
	if(room_show == 1)
	{
		drawTexture(680,20, textures[1]);
	}
}

void patient_check_out(void)
{
    drawTexture(0,0, coutp);
	iSetColor(1900,1900,1900);
	iText(80,530,"HOME",GLUT_BITMAP_9_BY_15);
	iText(580,600,"PATIENT CHECK OUT",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(250,500,"ID ",GLUT_BITMAP_HELVETICA_18);
	iText(250,420,"NAME :",GLUT_BITMAP_HELVETICA_18);
	iText(250,360,"AGE :",GLUT_BITMAP_HELVETICA_18);
	iText(250,300,"DISEASE CATAGORY :",GLUT_BITMAP_HELVETICA_18);
	iText(250,240,"CONTACT NO :",GLUT_BITMAP_HELVETICA_18);
	iText(750,500,"DATE",GLUT_BITMAP_HELVETICA_18);

	iSetColor(150,0,100);
	iRectangle(350,490,200,30);
	iRectangle(820,490,200,30);

	if(mode==0)
	iFilledRectangle(350,490,200,30);
	if(mode==14)
	iFilledRectangle(820,490,200,30);

	iSetColor(1900,1900,1900);
	iText(355,504,pstr[0],GLUT_BITMAP_HELVETICA_18);
	iSetColor(1900,1900,1900);
	if(match==1)
	{
		iText(455,424,pstr[1],GLUT_BITMAP_HELVETICA_18);
		iText(455,364,pstr[2],GLUT_BITMAP_HELVETICA_18);
		if(!strcmp(pstr[8],"1"))
		{
			iText(455,304,"CARDIAC",GLUT_BITMAP_HELVETICA_18);
		}
		if(!strcmp(pstr[8],"2"))
		{
			iText(455,304,"SKIN AND SEX",GLUT_BITMAP_HELVETICA_18);
		}
		if(!strcmp(pstr[8],"3"))
		{
			iText(455,304,"ORTHOPEDICS",GLUT_BITMAP_HELVETICA_18);
		}
		if(!strcmp(pstr[8],"4"))
		{
			iText(455,304,"MEDICINE",GLUT_BITMAP_HELVETICA_18);
		}
		if(!strcmp(pstr[8],"5"))
		{
			iText(455,304,"GYNECOLOGY",GLUT_BITMAP_HELVETICA_18);
		}
		iText(455,244,pstr[7],GLUT_BITMAP_HELVETICA_18);
	}
	iText(825,504,pstr[14],GLUT_BITMAP_HELVETICA_18);
	iSetColor(1965,1920,1910);
	iText(1200,160,"DONE",GLUT_BITMAP_TIMES_ROMAN_24);

	if(done == 1)
	{
		iSetColor(0,0,0);
		iRectangle(500,300,500,200);
		iSetColor(255,255,255);
		iFilledRectangle(500.5,301,499,198);
		iSetColor(181,166,166);
		iFilledRectangle(499,260,502,40);
		iSetColor(80,116,122);
		iFilledRectangle(700,270,100,20);
		iSetColor(1955,1955,1955);
		iText(742,273,"Ok",GLUT_BITMAP_HELVETICA_18);
		if(check[0] == 0 && check[14]==0)
			iText(640,390,"Please enter ID and Date!",GLUT_BITMAP_HELVETICA_18);
		else if(check[0] == 1 && check[14]==0)
			iText(660,390,"Please enter Date!",GLUT_BITMAP_HELVETICA_18);
		else if(check[0] == 0 && check[14]==1)
			iText(670,390,"Please enter ID!",GLUT_BITMAP_HELVETICA_18);
		else if(match == 2)
		{
		    iText(640,390,"Checked Out successfully!",GLUT_BITMAP_HELVETICA_18);
		}
		else
		{
		    iSetColor(1900, 0, 0);
			iText(650,390,"ID not found in database!",GLUT_BITMAP_HELVETICA_18);
		}
	}
}

void info_draw(void)
{
    iSetColor(4300, 4300, 4300);
    drawTexture(0,0, infop);
    drawTexture(0, 636, top);
	iText(80,530,"HOME",GLUT_BITMAP_9_BY_15);
	iText(400,500,"Number of patient in the hospital         :",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(900,500,in_info,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(400,420,"Number of patient already treated         :",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(900,420,out_info,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(400,340,"Total Number of patient got treatment :",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(900,340,sum,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(400,260,"Number of Doctors                         :",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(900,260,"10",GLUT_BITMAP_TIMES_ROMAN_24);
}

void doc_list(void)
{
    drawTexture(0,0, DOCL);
	iSetColor(2900,2900,2900);
	iText(80,530,"HOME",GLUT_BITMAP_9_BY_15);

	char line[100];
	CTA = fopen("docP.txt", "r");
	fgets(line, 100, CTA);
	iText(1250, 540, line, GLUT_BITMAP_HELVETICA_18);
	fgets(line, 100, CTA);
	iText(1250, 500-10, line, GLUT_BITMAP_HELVETICA_18);
	fgets(line, 100, CTA);
	iText(1250, 450-10, line, GLUT_BITMAP_HELVETICA_18);
	fgets(line, 100, CTA);
	iText(1250, 400-10, line, GLUT_BITMAP_HELVETICA_18);
	fgets(line, 100, CTA);
	iText(1250, 350-10, line, GLUT_BITMAP_HELVETICA_18);
	fgets(line, 100, CTA);
	iText(1250, 300-10, line, GLUT_BITMAP_HELVETICA_18);
	fgets(line, 100, CTA);
	iText(1250, 250-10, line, GLUT_BITMAP_HELVETICA_18);
	fgets(line, 100, CTA);
	iText(1250, 200-10, line, GLUT_BITMAP_HELVETICA_18);
	fgets(line, 100, CTA);
	iText(1250, 150-10, line, GLUT_BITMAP_HELVETICA_18);
	fgets(line, 100, CTA);
	iText(1250, 100-10, line, GLUT_BITMAP_HELVETICA_18);
	fclose(CTA);
}

void update(void)
{
    drawTexture(0,0, upda);
	iSetColor(1700,1700,1750);
	iText(80,530,"HOME",GLUT_BITMAP_9_BY_15);
	iText(580,600,"UPDATE PATIENT INFO",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1200,160,"DONE",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(750,500,"Input ID and Press ENTER",GLUT_BITMAP_HELVETICA_18);

	if(match == 3)
	{
		iSetColor(1755,0,0);
		iText(1150,200,"Please fill up all the boxes!!!",GLUT_BITMAP_HELVETICA_18);
	}

	iSetColor(1700,1750,1700);
	iText(250,500,"ID",GLUT_BITMAP_HELVETICA_18);
	iText(250,460,"NAME",GLUT_BITMAP_HELVETICA_18);
	iText(250,420,"AGE",GLUT_BITMAP_HELVETICA_18);
	iText(250,380,"SEX",GLUT_BITMAP_HELVETICA_18);
	iText(250,340,"BLOOD GROUP",GLUT_BITMAP_HELVETICA_18);
	iText(250,300,"ADDRESS",GLUT_BITMAP_HELVETICA_18);
	iText(250,260,"NATIONALITY",GLUT_BITMAP_HELVETICA_18);;
	iText(250,220,"CONTACT NO.",GLUT_BITMAP_HELVETICA_18);
	iText(250,180,"DISEASE CATAGORY",GLUT_BITMAP_HELVETICA_18);
	iText(250,140,"DESCRIPTION",GLUT_BITMAP_HELVETICA_18);
	iText(250,60,"ROOM",GLUT_BITMAP_HELVETICA_18);
	iText(250,20,"BED",GLUT_BITMAP_HELVETICA_18);

	iText(750,400,"*DISEASE CATEGORY(Click to select)",GLUT_BITMAP_HELVETICA_18);
	iText(750,340,"1. CARDIAC",GLUT_BITMAP_HELVETICA_18);
	iText(750,310,"2. SKIN AND SEX",GLUT_BITMAP_HELVETICA_18);
	iText(750,280,"3. ORTHOPEDICS",GLUT_BITMAP_HELVETICA_18);
	iText(750,250,"4. MEDICINE",GLUT_BITMAP_HELVETICA_18);
	iText(750,220,"5. GYNECOLOGY",GLUT_BITMAP_HELVETICA_18);

	iSetColor(150,0,100);
	iRectangle(450,490,200,30);
	iRectangle(450,450,200,30);
	iRectangle(450,410,200,30);
	iRectangle(450,370,200,30);
	iRectangle(450,330,200,30);
	iRectangle(450,290,200,30);
	iRectangle(450,250,200,30);
	iRectangle(450,210,200,30);
	iRectangle(450,170,200,30);
	iRectangle(450,90,200,70);
	iRectangle(450,50,200,30);
	iRectangle(450,10,200,30);

	iSetColor(150,0,100);
	if(mode==0)
	iFilledRectangle(450,490,200,30);
	if(mode==1)
	iFilledRectangle(450,450,200,30);
	if(mode==2)
	iFilledRectangle(450,410,200,30);
	if(mode==3)
	iFilledRectangle(450,370,200,30);
	if(mode==4)
	iFilledRectangle(450,330,200,30);
	if(mode==5)
	iFilledRectangle(450,290,200,30);
	if(mode==6)
	iFilledRectangle(450,250,200,30);
	if(mode==7)
	iFilledRectangle(450,210,200,30);
	if(mode==8)
	iFilledRectangle(450,170,200,30);
	if(mode==9)
	iFilledRectangle(450,90,200,70);
    if(mode==10)
	iFilledRectangle(450,50,200,30);
	if(mode==11)
	iFilledRectangle(450,10,200,30);

	iSetColor(1700,1700,1700);
	iText(451,500 - 40*0,pstr[0],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*1,pstr[1],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*2,pstr[2],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*3,pstr[3],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*4,pstr[4],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*5,pstr[5],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*6,pstr[6],GLUT_BITMAP_HELVETICA_18);
	iText(451,500 - 40*7,pstr[7],GLUT_BITMAP_HELVETICA_18);
	iText(540,500 - 40*8,pstr[8],GLUT_BITMAP_HELVETICA_18);
	iText(451,140,pstr[9],GLUT_BITMAP_HELVETICA_18);
	iText(451,60,pstr[10],GLUT_BITMAP_HELVETICA_18);
	iText(451,20,pstr[11],GLUT_BITMAP_HELVETICA_18);

	if(done == 1)
	{
		iSetColor(0,0,0);
		iRectangle(500,300,500,200);
		iSetColor(255,255,255);
		iFilledRectangle(500.5,301,499,198);
		iSetColor(181,166,166);
		iFilledRectangle(499,260,502,40);
		iSetColor(80,116,122);
		iFilledRectangle(700,270,100,20);
		iSetColor(1755,1755,1755);
		iText(742,273,"Ok",GLUT_BITMAP_HELVETICA_18);
		iText(530,390,"Updated successfully!",GLUT_BITMAP_HELVETICA_18);
	}
}

void patient_search(void)
{
    if(match!=1)
        drawTexture(0,0, sch1);
    if(match==1)
        drawTexture(0,0, sch2);

    iSetColor(1750,1700,1700);
	iText(80,530,"HOME",GLUT_BITMAP_9_BY_15);

	if(match!=1){
	iText(700,600,"SEARCH",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(300,500,"ID",GLUT_BITMAP_HELVETICA_18);
	iText(300,460,"NAME",GLUT_BITMAP_HELVETICA_18);


	iSetColor(150,0,100);
	iRectangle(500,490,200,30);
	iRectangle(500,450,200,30);

    iSetColor(150,0,100);
    if(mode==0)
	iFilledRectangle(500,490,200,30);
	if(mode==1)
	iFilledRectangle(500,450,200,30);

	iSetColor(1739,1700,1727);
	iText(505,500,pstr[0],GLUT_BITMAP_HELVETICA_18);
	iText(505,460,pstr[1],GLUT_BITMAP_HELVETICA_18);
	}


	if(match == 1)
	{
		count=0;
		iSetColor(26,52,121);
		iText(965,580,"X",GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(1900,1900,1900);
		iText(500,530,"ID               :",GLUT_BITMAP_8_BY_13);
		iText(500,490,"NAME             :",GLUT_BITMAP_8_BY_13);
		iText(500,450,"AGE              :",GLUT_BITMAP_8_BY_13);
		iText(500,410,"SEX              :",GLUT_BITMAP_8_BY_13);
		iText(500,370,"BLOOD GROUP      :",GLUT_BITMAP_8_BY_13);
		iText(500,330,"ADDRESS          :",GLUT_BITMAP_8_BY_13);
		iText(500,290,"NATIONALITY      :",GLUT_BITMAP_8_BY_13);
		iText(500,250,"CONTACT NO       :",GLUT_BITMAP_8_BY_13);
		iText(500,210,"DISEASE CATAGORY :",GLUT_BITMAP_8_BY_13);
		iText(500,170,"DESCRIPTION      :",GLUT_BITMAP_8_BY_13);
		iText(500,130,"ROOM             :",GLUT_BITMAP_8_BY_13);
		iText(500,90,"BED              :",GLUT_BITMAP_8_BY_13);
		iText(500,50,"CHECK IN DATE    :",GLUT_BITMAP_8_BY_13);

		iSetColor(1954,1963,1992);
		iText(700,530,pstr[0],GLUT_BITMAP_HELVETICA_12);
		iText(700,490,pstr[1],GLUT_BITMAP_HELVETICA_12);
		iText(700,450,pstr[2],GLUT_BITMAP_HELVETICA_12);
		iText(700,410,pstr[3],GLUT_BITMAP_HELVETICA_12);
		iText(700,370,pstr[4],GLUT_BITMAP_HELVETICA_12);
		iText(700,330,pstr[5],GLUT_BITMAP_HELVETICA_12);
		iText(700,290,pstr[6],GLUT_BITMAP_HELVETICA_12);
		iText(700,250,pstr[7],GLUT_BITMAP_HELVETICA_12);
		if(!strcmp(pstr[8],"1"))
		{
			iText(700,210,"CARDIAC",GLUT_BITMAP_HELVETICA_12);
		}
		if(!strcmp(pstr[8],"2"))
		{
			iText(700,210,"SKIN AND SEX",GLUT_BITMAP_HELVETICA_12);
		}
		if(!strcmp(pstr[8],"3"))
		{
			iText(700,210,"ORTHOPEDICS",GLUT_BITMAP_HELVETICA_12);
		}
		if(!strcmp(pstr[8],"4"))
		{
			iText(700,210,"MEDICINE",GLUT_BITMAP_HELVETICA_12);
		}
		if(!strcmp(pstr[8],"5"))
		{
			iText(700,210,"GYNAECOLOGY",GLUT_BITMAP_HELVETICA_12);
		}
		iText(700,170,pstr[9],GLUT_BITMAP_HELVETICA_12);
		iText(700,130,pstr[10],GLUT_BITMAP_HELVETICA_12);
		iText(700,90,pstr[11],GLUT_BITMAP_HELVETICA_12);
		iText(700,50,pstr[12],GLUT_BITMAP_HELVETICA_12);
	}
	else if(match == -1)
		iText(750,500,"*Not Found",GLUT_BITMAP_HELVETICA_12);
	if(count>0)
	{
	    iSetColor(1700, 1700, 1700);
	    iFilledRectangle(995,5,490,610);
		iSetColor(200,200,200);
		iFilledRectangle(1000,10,480,600);
		iSetColor(99900,99995,99990);
		iFilledRectangle(1440,580,40,30);
		iSetColor(0,0,0);
		iText(1455,590,"X",GLUT_BITMAP_HELVETICA_12);
		iSetColor(0,600,0);
		iRectangle(1000,10,480,600);
		iSetColor(1700,1700,1700);
		iText(1150,580,"  FOUND IN THIS NAMES",GLUT_BITMAP_HELVETICA_12);
		iText(1150,570,"=======================",GLUT_BITMAP_HELVETICA_12);
		iText(1160,550,"   ID           NAME",GLUT_BITMAP_HELVETICA_12);
		int i;
		iSetColor(1945,1900,1900);
		for(i=0;i<show;i++)
		{
			iText(1135,530-20*(i+1),found[i],GLUT_BITMAP_9_BY_15);
		}
	}
	if(count==-1){
        iSetColor(3300, 0, 0);
		iText(750,460,"*Not Found",GLUT_BITMAP_HELVETICA_18);
	}

}

void draw_login_page(void)
{
   drawTexture(0,0, home);
	iSetColor(900,900,900);
	iRectangle(650,415,400,80);
	iSetColor(600,600,600);
	iFilledRectangle(650,415,400,80);
	iSetColor(900,900,900);
	iRectangle(650,315,400,80);
	iSetColor(600,600,600);
	iFilledRectangle(650,315,400,80);

	iSetColor(1700,1700,1700);
	iText(670,450,str_id,GLUT_BITMAP_HELVETICA_18);
	iText(670,350,str,GLUT_BITMAP_HELVETICA_18);

	if(match == 2)
	{
		iSetColor(1955,9,9);
		iText(713,280,"*ID and Password did not match!",GLUT_BITMAP_HELVETICA_18);
	}

}

void draw_home_page(void)
{
	drawTexture(0,0, textures[0]);
	drawTexture(0,0, textures[2]);
	iSetColor(1750,1700,1700);
	iText(80,530,"HOME",GLUT_BITMAP_9_BY_15);
	iText(80,480,"PATIENT CHECK IN",GLUT_BITMAP_9_BY_15);
	iText(80,430,"PATIENT CHECK OUT",GLUT_BITMAP_9_BY_15);
	iText(80,380,"SEARCH",GLUT_BITMAP_9_BY_15);
	iText(80,330,"UPDATE",GLUT_BITMAP_9_BY_15);
	iText(80,280,"INFO",GLUT_BITMAP_9_BY_15);
	iText(80,230,"DOCTORS LIST",GLUT_BITMAP_9_BY_15);
	iText(80,180,"PATIENTS LIST",GLUT_BITMAP_9_BY_15);
	iText(80,130,"ROOM", GLUT_BITMAP_9_BY_15);
	iText(80,80, "LOG OUT", GLUT_BITMAP_9_BY_15);
	iSetColor(0,0,0);
	iText(1300,590,"USER ID:",GLUT_BITMAP_9_BY_15);
	iText(1400,590,id,GLUT_BITMAP_9_BY_15);
}

void draw_Plist(void)
{
    drawTexture(0,0, pats);
    iSetColor(1750,1750,1750);
	iText(80,530,"HOME",GLUT_BITMAP_9_BY_15);
    int i, am=0;
    char ch;
    plist = fopen(listP, "r");
    char line[200];

    while(1){
        ch = fgetc(plist);
        if(ch==EOF)
            break;
        fseek(plist, -1, SEEK_CUR);
        fgets(line, 200, plist);
        sscanf(line,"%s %s %s %s %s %s", lpat[0], lpat[1], lpat[2], lpat[3], lpat[4], lpat[5]);
        iSetColor(1700, 1700, 1700);
        iText(360, 510-am+pmtr, lpat[0], GLUT_BITMAP_HELVETICA_18);
        iText(560, 510-am+pmtr, lpat[1], GLUT_BITMAP_HELVETICA_18);
        iText(660, 510-am+pmtr, lpat[2], GLUT_BITMAP_HELVETICA_18);
        iText(860, 510-am+pmtr, lpat[3], GLUT_BITMAP_HELVETICA_18);
        iText(1000, 510-am+pmtr, lpat[4], GLUT_BITMAP_HELVETICA_18);
        iText(1140, 510-am+pmtr, lpat[5], GLUT_BITMAP_HELVETICA_18);

        am += 41;
    }
    fclose(plist);
    drawTexture(0, 583, patsr);
    drawTexture(250, 535, patr1);
    iSetColor(0, 1700, 0);
    iFilledRectangle(1418, 300, 20, 70);
}

void draw_room()
{
    drawTexture(0,0, rmst);
    int i=0, a=0, pm=0;
    roFP = fopen("roomP.txt", "r");
    roFA = fopen("roomA.txt", "r");
    char lineA[50], ch, lol[100], lol1[100];

    iSetColor(1750,1750,1750);
	iText(80,530,"HOME",GLUT_BITMAP_9_BY_15);
    char line[200];

    while(1){
        ch = fgetc(roFP);
        if(ch==EOF)
            break;
        fseek(roFP, -1, SEEK_CUR);

        iSetColor(1700, 1700, 1700);
        if(i==0)
            pm = 220;
        fscanf(roFP,"%s", lol);
        iText(170+pm, 520-a, lol, GLUT_BITMAP_HELVETICA_18);

        fscanf(roFA, "%s", lol1);
        iText(170+pm, 460-a, lol1, GLUT_BITMAP_HELVETICA_18);
        if(i==4 || i==9){
            a+=180;
            pm = 0;
        }
        if(i!=4|| i!=9)
            pm+=225;
        i++;
    }
    fclose(roFA);
    fclose(roFP);
}


void iDraw() {
	iClear();

	if(window == 0)
	    draw_login_page();
	if(window == 1)
		draw_home_page();
	if(window == 2)
		patient_check_in();
	if(window == 3)
		patient_check_out();
	if(window == 4)
		patient_search();
	if(window == 5)
		update();
	if(window == 6)
		info_draw();
	if(window == 7)
		doc_list();
    if(window == 8)
    {
        iSetColor(1700,1700,1700);
        draw_Plist();
    }
    if(window==9){
        draw_room();
    }
	iSetColor(250,250,250);
	drawTexture(0, 636, top);
}


void iMouseMove(int mx, int my) {
}

void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(window==0)
		{
		    fp = fopen(temp, "w");
		    fputc('\0', fp);
		    fclose(fp);
		    fp = fopen("T.txt", "w");
		    fputc('\0', fp);
		    fclose(fp);
		    fp = fopen("Found.txt", "w");
		    fputc('\0', fp);
		    fclose(fp);
			if(mx>=718 && mx<= 983 && my>=225 && my<=270)
			{
				pass_word();
				if(match == 1)
				{
					int i;
					for(i=0;i<20;i++)
					{
						str_id[i] = 0;
						str_pass[i] = 0;
		                str[i] = 0;
					}
		            window = 1;
					len1=0;
					len2 =0;

				}
			    mode = 0;
			}
			if(mx>650 && mx<1050 && my>415 && my<495)
			{
				mode =1;
			}
			if(mx>650 && mx<1050 && my>315 && my<395)
			{
				mode = 2;
			}
		}
		if(window == 1)
		{
			if(mx>=40 && mx<=300 && my>=470 && my<=500)
				window = 2;                            //Check In
			if(mx>=40 && mx<=300 && my>=420 && my<=450)
				window = 3;							   //Check Out
			if(mx>=40 && mx<=300 && my>=370 && my<=400)
				window = 4;                            //Search
			if(mx>=40 && mx<=300 && my>=320 && my<=350)
				window = 5;                            //Update
			if(mx>=40 && mx<=300 && my>=270 && my<=300)
			{
				info_check();
				window = 6;                            //Info
			}
			if(mx>=40 && mx<=300 && my>=220 && my<=250)
				window = 7;                            //Doctors List
			if(mx>=40 && mx<=300 && my>=170 && my<=200)
				window = 8;                             //patient list
            if(mx>=40 && mx<=300 && my>=120 && my<=150)
				window = 9;                             //Room
            if(mx>=40 && mx<=300 && my>=70 && my<=100)
                window = 0;                             //Log Out

		}
		if(window != 0)
			if(mx>=40 && mx<=300 && my>=520 && my<=550)
			{
				window = 1;                            //Home
				count =0;
				match = 0;
				int i,j;
				for(i=0;i<20;i++)
				{
					for(j=0;j<50;j++)
						pstr[i][j]=0;
					len[i]=0;
				}
			}
        //check in:
		if(window == 2)
		{
			if(mx>=450 && mx<=650)
			{
				if(my>=490 && my<=520)
					mode = 12;
				if(my>=450 && my<=480)
					mode = 1;
			    if(my>=410 && my<=440)
					mode = 2;
				if(my>=370 && my<=400)
					mode = 3;
				if(my>=330 && my<=360)
					mode = 4;
				if(my>=290 && my<=320)
					mode = 5;
				if(my>=250 && my<=280)
					mode = 6;
				if(my>=210 && my<=240)
					mode = 7;
				if(my>=90 && my<=160)
					mode = 9;
				if(my>=50 && my<=80)
				{
					mode = 10;
					room_show = 1;
				}
				else
					room_show = 0;
				if(my>=10 && my<=40)
					mode = 11;
			}
			if(mx>=820 && mx<=1020 && my>=490 && my<=520)
			{
				int i;
				s = 0;
				for(i=0;i<13;i++)
				{
					printf("check[%d] = %d\n",i,check[i]);
					s = s + check[i];
					mem[i] = pstr[i];
				}
				if(s==12)
				{
					tmp = fopen(temp,"w");
					tfp = fopen("T.txt","w");
					fprintf(tmp,"%s",mem[12]);
					fclose(tmp);
					tmp = fopen(temp,"r");
					fseek(tmp,-2,SEEK_END);
					char ch;
					while(1)
					{
						ch = fgetc(tmp);
						if(ch == EOF)
						{
							break;
						}
						fprintf(tfp,"%c",ch);
					}
					fclose(tmp);
					fp = fopen(temp, "w");
					fputc('\0', fp);
					fclose(fp);
					Gen_id();
					fprintf(tfp,"%s%d",mem[8],patient.ID);
					fclose(tfp);
					tfp = fopen("T.txt","r");
					i=0;
					while(1)
					{
						ch = fgetc(tfp);
						if(ch == EOF)
						{
							break;
						}
						pstr[0][i] = ch;
						i++;
					}
					fclose(tfp);
					remove("T.txt");

					check[0] = 1;
				}

			}

			if(mx>=750 && mx<=840 && my>=340 && my<=350)
			{
				*pstr[8] = '1';
				check[8] = 1;
			}
			if(mx>=750 && mx<=885 && my>=310 && my<=320)
			{
				*pstr[8] = '2';
				check[8] = 1;
			}
			if(mx>=750 && mx<=875 && my>=280 && my<=290)
			{
				*pstr[8] = '3';
				check[8] = 1;
			}
			if(mx>=750 && mx<=845 && my>=250 && my<=260)
			{
				*pstr[8] = '4';
				check[8] = 1;
			}
			if(mx>=750 && mx<=870 && my>=220 && my<=230)
			{
				*pstr[8] = '5';
				check[8] = 1;
			}

			if(mx>=1200 && mx<=1265 && my>=158 && my<=175) //Click on DONE
			{
				int i,j;
				s = 0;
				for(i=0;i<13;i++)
				{
					printf("check[%d] = %d\n",i,check[i]);
					s = s + check[i];
				}

				if(s==13)
				{
					fp = fopen(cIn,"a+");
					for(i=0;i<13;i++)
					{
						mem[i] = pstr[i];
						fprintf(fp,"%s\n",mem[i]);
					}
					fclose(fp);
                    fp = fopen(id_name,"a+");
					fprintf(fp," %d",patient.ID);
					fclose(fp);
					done = 1;
					for(i=0;i<20;i++)
					{
						for(j=0;j<30;j++)
							pstr[i][j] = 0;

						check[i] = 0;
						len[i] = 0;
					}
				}
				else
					match =3;
			}
			if(done==1)
				if(mx>=700 && mx<=800 && my>=270 && my<=290)
				{
					window = 1;
					done = 0;
					match = 0;
				}
		}
		if(window == 3)
		{
			if(mx>=350 && mx<=550 && my>=490 && my<=520)
			{
				mode = 0;
				check[0] = 0;
				match = 0;
			}
			if(mx>=820 && mx<=1020 && my>=490 && my<=520)
				mode = 14;
			if(mx>=1200 && mx<=1265 && my>=158 && my<=175)
			{
				if(match == 1 && check[14]==1)
				{
					match = 2;
					dlt = fopen(cOut,"a+");
					fp = fopen("Found.txt","r");
					char ch;
					while((ch = fgetc(fp)) != EOF)
					{
						fputc(ch,dlt);
					}
					fprintf(dlt,"%s\n",pstr[14]);
					fclose(dlt);
					remove("Found.txt");
					remove("T.txt");
					tem = fopen(temp, "r");
					ciin = fopen(cIn, "w");
					char c;
					while(1)
                    {
                        c = fgetc(tem);
                        if(c==EOF)
                            break;
                        fputc(c, ciin);
                    }
                    fclose(ciin);
                    fclose(tem);
                    tem = fopen(temp, "w");
                    fputc('\0', tem);
                    fclose(tem);

				}
				done = 1;
			}
			if(done==1)
				if(mx>=700 && mx<=800 && my>=270 && my<=290)
				{
					if(match ==2)
					{
						window = 1;
						int i;
						for(i=0;i<30;i++)
						{
							pstr[0][i] = 0;
							pstr[14][i] = 0;
						}
					}
					done = 0;
					match = 0;
				}
		}

		if(window == 4)//Search
		{
		    fp = fopen(temp, "w");
		    fputc('\0', fp);
		    fclose(fp);
			if(mx>=500 && mx<=700 && my>=490 && my<=520)
			{
				mode = 0;
				check[0] = 0;
				match = 0;
				check[1] = 0;
			}
			if(match == 1 && mx>=950 && mx<=1000 && my>=560 && my<=610)
			{
				match = 0;
				int i,j=0;
				for(j=0;j<13;j++)
				for(i=0;i<21;i++)
				{
					pstr[j][i]=0;
					len[j] = 0;
				}
			}
			if(mx>=500 && mx<=700 && my>=450 && my<=480)
			{
				mode = 1;
				check[1] = 0;
				match = 0;
				check[0] = 0;
			}
			if(mx>=1440 && mx<=1480 && my>= 580 && my<=610)
			{
				count = 0;
			}

		}

        if(window!=4){
            fp = fopen(temp, "w");
            fputc('\0', fp);
            fclose(fp);
        }


		if(window==5)
		{
			if(mx>=450 && mx<=650)
			{
				if(my>=490 && my<=520)
					mode = 0;
				else if(my>=450 && my<=480)
					mode = 1;
				else if(my>=410 && my<=440)
					mode = 2;
				else if(my>=370 && my<=400)
					mode = 3;
				else if(my>=330 && my<=360)
					mode = 4;
				else if(my>=290 && my<=320)
					mode = 5;
				else if(my>=250 && my<=280)
					mode = 6;
				else if(my>=210 && my<=240)
					mode = 7;
				else if(my>=90 && my<=160)
					mode = 9;
				else if(my>=50 && my<=80)
					mode = 10;
				else if(my>=10 && my<=40)
					mode = 11;
			}

			if(mx>=1200 && mx<=1265 && my>=158 && my<=175) //Click on DONE
			{
				int i,j;
				char ch;

				if(match==1)
				{
					tmp = fopen(np,"a+");
					for(i=0;i<13;i++)
					{
						mem[i] = pstr[i];
						fprintf(tmp,"%s\n",mem[i]);
					}
					src = fopen("Last.txt","r");
					while((ch = fgetc(src))!=EOF)
					{
						fputc(ch,tmp);
					}
					done = 1;
					for(i=0;i<20;i++)
					{
						for(j=0;j<30;j++)
							pstr[i][j] = 0;

						check[i] = 0;
						len[i] = 0;
					}
					fclose(tmp);
					int ip=0;
					CTA = fopen(np, "r");
					cINF = fopen(cIn, "w");

					while(1){
                        ch = fgetc(CTA);
                        if(ch==EOF)
                            break;
                        if(ch=='\n')
                            ip++;
                        if(ip==13)
                            ip=0;
                        if(ip==0 && ch==0)
                            ip=0;
                        else
                        fputc(ch, cINF);
					}
					fclose(CTA);

					CTA = fopen(np, "w");
					fputc('\0', CTA);
					fclose(CTA);
					fclose(cINF);

					last = fopen("Last.txt", "w");
					fputc('\0', last);
					fclose(last);
					fp = fopen("T.txt", "w");
					fputc('\0', fp);
					fclose(fp);
				}
				else
					match =3;
			}
			if(done==1)
				if(mx>=700 && mx<=800 && my>=270 && my<=290)
				{
					window = 1;
					done = 0;
					match = 0;
				}
		}

        //patlist
		if(window==7)
        {
            int ippp=0, i;
            CTA = fopen(cIn, "r");
            char ch;
            for(i=0; i<5; i++)
                disP[i]=0;
            while(1){
                ch = fgetc(CTA);
                if(ch==EOF)
                    break;


                if(ippp==8){
                    if(ch==49)
                        disP[0] = disP[0]+1;
                    if(ch==50)
                        disP[1] = disP[1]+1;
                    if(ch==51)
                        disP[2]++;
                    if(ch==52)
                        disP[3]++;
                    if(ch==53)
                        disP[4]++;
                }
                if(ch=='\n')
                    ippp++;
                if(ippp==13)
                    ippp=0;
            }
            fclose(CTA);

            docP[0]=disP[0]/2;
            docP[1]=disP[0]-docP[0];
            docP[2]=disP[1]/2;
            docP[3]=disP[1]-docP[2];
            docP[4]=disP[2]/2;
            docP[5]=disP[2]-docP[4];
            docP[6]=disP[3]/2;
            docP[7]=disP[3]-docP[6];
            docP[8]=disP[4]/2;
            docP[9]=disP[4]-docP[8];

            CTA = fopen("docP.txt", "w");
            fprintf(CTA, "%d\n", docP[0]);
            fprintf(CTA, "%d\n", docP[1]);
            fprintf(CTA, "%d\n", docP[2]);
            fprintf(CTA, "%d\n", docP[3]);
            fprintf(CTA, "%d\n", docP[4]);
            fprintf(CTA, "%d\n", docP[5]);
            fprintf(CTA, "%d\n", docP[6]);
            fprintf(CTA, "%d\n", docP[7]);
            fprintf(CTA, "%d\n", docP[8]);
            fprintf(CTA, "%d", docP[9]);
            fclose(CTA);
        }

		if(window==8)
        {
            if(mx>=1420 && mx<= 1440 && my>=0 && my<=298)
			    pmtr+=41;
            if(mx>=1420 && mx<= 1440 && my>=372 && my<=520)
			    pmtr-=41;
            int i=0;
            char ch;
            fp = fopen(cIn, "r");
            plist = fopen(listP, "w");
            while(1){
                ch = fgetc(fp);
                if(ch==EOF)
                    break;
                if(ch!='\n'){
                    if(i==0 || i==1 || i==2 || i== 4 || i==7){
                        fputc(ch, plist);
                    }
                }
                if(ch=='\n'){
                    if(i==0 || i==1 || i==2 || i== 4 || i==7){
                        fputc(32, plist);
                    }
                    i++;
                }
                if(i==13 && ch=='\n'){
                    i=0;
                    fputc('\n', plist);
                    }
                }

            fclose(fp);
            fclose(plist);
        }

        if(window==9)
        {
            roomsI();
        }

	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
	}

}



void iKeyboard(unsigned char key) {
	if(window == 0 && mode ==1)
	{
		if(key == '\r')
		{
			//mode = 0;
			printf("%s\n", str_id);

			//pass_word();
		}
		else if(key == '\b')
		{
			if(len1>0)
			{
				len1--;
				str_id[len1] = 0;
			}
		}
		else
		{
			str_id[len1] = key;
			len1++;
		}
	}
    if(window == 0 && mode ==2)
	{
		if(key == '\r')
		{
		    printf("*****\n");
		}
		else if(key == '\b')
		{
			if(len2>0)
			{
				len2--;
				str_pass[len2] = 0;
				str[len2]= 0;
			}
		}
		else
		{
			str_pass[len2] = key;
			str[len2] = '*';
			len2++;
		}
	}
	if(window == 2)
	{
		if(key == '\r')
		{
			pstr[mode][len[mode]] = '\0';
			if(len[mode]>0)
			{
				check[mode] = 1;
			}

		}
		else if(key == '\b')
		{
			if(len[mode]>0)
			{
				len[mode]--;
				pstr[mode][len[mode]] = 0;
			}
		}
		else
		{
			if(mode != 8)
			pstr[mode][len[mode]] = key;
			if(len[mode]<21)
				len[mode]++;
			else
				pstr[mode][len[mode]] = '\0';
		}
	}

	if(window == 3)
	{
		if(key == '\r')
		{

			pstr[mode][len[mode]] = '\0';
			if(len[mode]>0)
			{
				check[mode] = 1;
			}
			if(check[0] == 1)
			{
				if(id_match()==1)
					match=1;
			}
		}
		else if(key == '\b')
		{
			if(len[mode]>0)
			{
				len[mode]--;
				pstr[mode][len[mode]] = 0;
			}
		}
		else
		{
			pstr[mode][len[mode]] = key;
			if(len[mode]<21)
				len[mode]++;
			else
				pstr[mode][len[mode]] = '\0';
		}
	}

	if(window == 4)              //Search
	{
		if(key == '\r')
		{

			pstr[mode][len[mode]] = '\0';
			if(len[mode]>0)
			{
				check[mode] = 1;
			}
			if(check[0] == 1)
			{
				if(id_match()==1)
				{
					CTA = fopen("Found.txt", "w");
					fputc('\0', CTA);
					fclose(CTA);
					fp = fopen(temp, "w");
					fputc('\0', fp);
					fclose(fp);
					match = 1;
				}
				else
					match = -1;
			}
			if(check[1] == 1)
			{
				fp = fopen(cIn,"r");
				tfp = fopen(temp,"w");
				char c,ch;
				char name[21];
				int i=0,j=0,k,ret;
				count = 0;
				for(i=0;i<30;i++)
					for(j=0;j<50;j++)
						found[i][j] = 0;
				i=0;j=0;
				while(1)
				{
					ch = fgetc(fp);

					if(i<2)fputc(ch,tfp);
					if(i==13)
					{
						fclose(tfp);
						tfp = fopen(temp,"r");
						fseek(tfp,11,SEEK_SET);
						fgets(name,21,tfp);
						ret = searching(name,pstr[1]);
						count += ret;
						if(ret)
						{
							fclose(tfp);
							tfp = fopen(temp,"r");
							k=0;
							while((c=fgetc(tfp))!=EOF)
							{
								if(c=='\n')
								{
									found[j][k] = 32;
									found[j][k+1] = 32;
									found[j][k+2] = 32;
									k=k+2;
								}
								else
								found[j][k] = c;
								k++;
							}
							j++;
						}
						i=0;
						ret = 0;
						fclose(tfp);
						tfp = fopen(temp,"w");
						if(ch == EOF)break;
						fputc(ch,tfp);
					}
					if(ch == '\n')
						i++;
				}
				show = j;
				if(count==0)
                    count = -1;
			}
		}
		else if(key == '\b')
		{
			if(len[mode]>0)
			{
				len[mode]--;
				pstr[mode][len[mode]] = 0;
			}
		}
		else
		{
			pstr[mode][len[mode]] = key;
			if(len[mode]<21)
				len[mode]++;
			else
				pstr[mode][len[mode]] = '\0';
		}
	}

	if(window == 5)
	{
		if(key == '\r')
		{
			pstr[mode][len[mode]] = '\0';
			if(len[mode]>0)
			{
				check[mode] = 1;
			}
			if(check[0] == 1)
			{
				if(update_func()==1)
					match=1;
				int i;
				for(i=1;i<12;i++)
				len[i] = strlen(pstr[i]);
				check[0] = 0;
			}
			printf("%s\n",pstr[mode]);
		}
		else if(key == '\b')
		{
			if(len[mode]>0)
			{
				len[mode]--;
				pstr[mode][len[mode]] = 0;
			}
		}
		else
		{
			pstr[mode][len[mode]] = key;
			if(len[mode]<21)
				len[mode]++;
			else
				pstr[mode][len[mode]] = '\0';
		}
	}

	if (key == 'q') {
		//exit(0);
	}
	//place your codes for other keys here
}



void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	//place your codes for other keys here
}



int main() {
	len1 = len2 = 0;
	mode = 0;
	str[0] = 0;
	char t;
	for(t=0;t<20;t++)
	{

		check[t]=0;
		len[t] = 0;
		mem[t] = pstr[t];
	}
	iInitialize(1500, 720, "Hospital Management System");

	return 0;
}


void pass_word(void)
{
	if(!strcmp(id,str_id) && !strcmp(pass,str_pass))
	{
		match = 1;
	}
	else
	{
		match = 2;
	}

}

int Gen_id(void)
{
	fp = fopen(id_name,"r+");
    fseek(fp,-7,SEEK_END);
    fscanf(fp,"%d",&patient.ID);
    fclose(fp);

    patient.ID = patient.ID + 1;

	return patient.ID;
}

int id_match(void)
{
	fp = fopen(cIn,"r");
	tfp = fopen("T.txt","w");
	src = fopen("Found.txt","w");
	tmp = fopen(temp,"w");

	char ch,c;
	int i=0,j=0,k=0,l=0;
	while(1)
	{
		ch = fgetc(fp);
		if(i==13)
		{
			fclose(tfp);
			tfp = fopen("T.txt","r");
            fgets(pstr[13],10,tfp);
			if(!strcmp(pstr[13],mem[0]))
			{
				fseek(tfp,-9,SEEK_CUR);
				for(j=0;j<13;j++)
				{
					k=0;
					while((c=fgetc(tfp)) != '\n')
					{
						fputc(c,src);
						pstr[j][k] = c;
						k++;
					}
					pstr[j][k] = '\0';
					if(c == '\n')
						fputc(c,src);
				}
				l=1;
			}
			else
			{
				fseek(tfp,-9,SEEK_CUR);
				while((c=fgetc(tfp)) != EOF)
				{
					fputc(c,tmp);
				}
			}
			i=0;
			fclose(tfp);
			tfp = fopen("T.txt","w");
		}
		fputc(ch,tfp);
		if(ch==EOF)
		{
			break;
		}
		if(ch == '\n')
			i++;
	}
	fclose(fp);
	fclose(tfp);
	fclose(tmp);
	fclose(src);
	return l;
}


char* strtolower(char *str)
{
    int len,i;
    len = strlen(str);
    char *nstr;
	nstr=(char*)malloc(sizeof(char)*len);
    for(i=0;i<len;i++)
    {
        nstr[i] = str[i];
    }
    nstr[i] = '\0';
    i=0;
    while(str[i])
    {
        if(str[i]>= 'A' && str[i] <='Z')
            nstr[i] += 32;
        i++;
    }
    return nstr;
}

int searching(char *str,char *find)
{
    int flen = strlen(find);
    int slen = strlen(str);
    char *nstr = (char*)malloc(sizeof(char)*slen);
    char *nfind = (char*)malloc(sizeof(char)*flen);
    char *temp = (char*)malloc(sizeof(char)*flen);
    nstr = strtolower(str);
    nfind = strtolower(find);

    int i=0,j;
    while(nstr[i+flen]!='\0')
    {
        for(j=0; j<flen; j++)
        {
            *(temp+j)=nstr[i+j];
        }
        *(temp+j)='\0';
        if(!strcmp(nfind,temp))
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int update_func(void)
{
	fp = fopen(cIn,"r");
	tfp = fopen("T.txt","w");
	src = fopen("Last.txt","a+");
	tmp = fopen(np,"w");
	dlt = fopen("Faltu.txt","w");

	char ch,c;
	int i=0,j=0,k=0,l=0,sw = 0;
	while(1)
	{
		ch = fgetc(fp);
		if(i==13)
		{
			fclose(tfp);
			tfp = fopen("T.txt","r");
			fgets(pstr[13],10,tfp);
			if(!strcmp(pstr[13],mem[0]))
			{
				fseek(tfp,-9,SEEK_CUR);
				for(j=0;j<13;j++)
				{
					k=0;
					while((c=fgetc(tfp)) != '\n')
					{
						pstr[j][k] = c;
						k++;
					}
					pstr[j][k] = '\0';
				}
				l=1;
			}
			i=0;
			fclose(tfp);
			tfp = fopen("T.txt","r");
			while((c=fgetc(tfp)) != EOF)
			{
				if(l==0 )
					fputc(c,tmp);
		        if(l==1)
				{
					if(sw<13)
					{
						fputc(c,dlt);
						if(c=='\n')
						sw++;
					}
					if(sw==14)
					{
						fputc(c,src);
					}
					if(sw==13)
					{
						c=fgetc(tfp);
						sw=14;
					}
				}
			}
			fclose(tfp);
			tfp = fopen("T.txt","w");
		}
		fputc(ch,tfp);

		if(ch==EOF)
		{
			break;
		}
		if(ch == '\n')
			i++;
	}
	fclose(fp);
	fclose(tfp);
	fclose(tmp);
	fclose(src);
	fclose(dlt);
	remove("Faltu.txt");
	return l;
}
