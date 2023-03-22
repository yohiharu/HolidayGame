#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define QUIZ_NUMBER 8
#define NEW_QUIZ_NUMBER 2

//=============================================
// あらかじめ作成してあるクイズ(グローバル変数)
//=============================================
char quiz[QUIZ_NUMBER][100] = {"11月に祝日は何日ある？", "２月１１日は何の日", "みどりの日は何月何日？", "１１月２３日は何日？", "祝日がない月は？", "スポーツの日は１０月の第何月曜日？", "敬老の日は９月の第何月曜日？", "８月にある祝日は？"};
char option[QUIZ_NUMBER][100] = {"1:１日  2:２日  3:３日","1:天皇誕生日  2:昭和の日  3:建国記念の日", "1:５月３日  2:５月４日  3:５月５日", "1:勤労感謝の日 2:敬老の日  3:憲法記念日",
                                 "1:６月と１２月  2: ４月と１２月 3:４月と６月","1:第二月曜日  2:第三月曜日  3:第一月曜日", "1:第二月曜日  2:第三月曜日  3:第一月曜日", "1:山の日  2:海の日  3:スポーツの日"};
int answer[QUIZ_NUMBER] = {2, 3, 2, 1, 1, 1, 2, 1};

int answer_order[QUIZ_NUMBER] = {0, 1, 2, 3, 4, 5, 6, 7};

//=============================================
// 関数プロトタイプ宣言
//=============================================
void shuffle_order(void);
void create_quiz(int * month, int * day);
int get_answer(int month, int day);

//=============================================
// 主処理
//=============================================
int main(void){
    int yourAnswer;
    int correct_answer_count = 0;
    int month, day;
    int quiz_counter = 1;
    shuffle_order();
    system("cls");  //ターミナル画面をクリア (LinuxまたはmacOSの場合は、clrscr()をsystem("clear")に置き換えます)
    printf("\t祝日クイズ ~ ２０２３年ver ~  \n\n");
    Sleep(2000);
    system("cls");
    printf("\tスタート!\n\n");
    Sleep(2000);
    system("cls");
    puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < QUIZ_NUMBER; i++){
        printf("\t第%d問\n\n", quiz_counter);
        quiz_counter++;
        printf("\tQ,%s\n\n\t%s", quiz[answer_order[i]], option[answer_order[i]]);
        printf("\t\tあなたの解答:"); scanf("%d", &yourAnswer);
        if (yourAnswer == answer[answer_order[i]]){
            printf("\n\t正解!\n");
            correct_answer_count++;
        }
        else{
            printf("\n\t不正解!\n");
        }
        Sleep(700);
        system("cls");
        puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    create_quiz(&month, &day);
    for (int j = 0; j < NEW_QUIZ_NUMBER; j++){
        printf("\t第%d問\n\n", quiz_counter);
        quiz_counter++;
        printf("\t%d月%d日は祝日(西暦に関係なく祝日である月日に限ります)？\n", month, day);
        printf("\t1:祝日である  2:祝日ではない");
        printf("\t\t\tあなたの解答:"); scanf("%d", &yourAnswer);
        if (yourAnswer == get_answer(month, day)){
            printf("\n\t正解!\n");
            correct_answer_count++;
        }
        else{
            printf("\n\t不正解!\n");
        }
        Sleep(700);
        system("cls"); 
        create_quiz(&month, &day);
        puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    printf("\n\n\t\t%d問中%d問正解しました。\n\n\n", QUIZ_NUMBER + NEW_QUIZ_NUMBER, correct_answer_count);
    printf("\n\n\t\t正答率は%.0lf%%です。\n\n", ( (double) correct_answer_count / (QUIZ_NUMBER + NEW_QUIZ_NUMBER) ) * 100);
    Sleep(3000);
    system("cls");
    if (correct_answer_count >= QUIZ_NUMBER + NEW_QUIZ_NUMBER-1){          
        printf("\n\n\n\t\tおめでとうございます。\n\n\t\tあなたは[祝日マスター]です！\n\n\n\n\n\n\n\n");
    }
    else{
        printf("\n\n\n\t\t残念ながらあなたは[祝日マスター]ではありません。\n\n\n\n\n\n\n\n\n");
    }

    return 0;
}

//=============================================
// 固定問題の順番シャッフル (１００回)
//=============================================
void shuffle_order(void){
    int random1, random2;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 100; i++){
        random1 = rand() % QUIZ_NUMBER;
        random2 = rand() % QUIZ_NUMBER;
        int temp = answer_order[random1];
        answer_order[random1] = answer_order[random2];
        answer_order[random2] = temp;
    }
    return;
}

//=============================================
// ランダム月日クイズ(祝日or祝日ではない)
//=============================================
void create_quiz(int * p_month, int * p_day){
    int month, day;
    srand((unsigned int)time(NULL));
    do{
        *p_month = rand() % 12 + 1;
        *p_day = rand() % 31 + 1;
    } while ( ( (month == 2 || month == 4 || month == 6 || month == 9 || month == 11) && (day == 31)) || (month == 2 && day >= 29) );
}

//=============================================
// ランダム月日クイズの正誤判定
//=============================================
int get_answer(int month, int day){
    if ((month == 1 && day == 1) || (month == 2 && (day == 11 || day == 23)) || (month == 4 && day == 29) || (month == 5 && (day == 3 || day == 4 || day == 5)) || (month == 8 && day == 11) || (month == 11 && (day == 3 || day == 23))){
        return 1;
    }
    return 2;
}

