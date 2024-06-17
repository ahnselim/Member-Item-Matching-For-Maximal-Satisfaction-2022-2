#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random_selection(int score_table[][20])
{
    srand((unsigned)time(NULL));
    int total = 0;
    int m = rand() % 20;
    int mark_member[20] = { 0, };
    int mark_item[20] = { 0, };
    int count = 0;
    int k = 0;
    for (int i = 0; i < 20; i++) {
        int max_score = 0;
        // 중복이 없을 때까지 랜덤 추첨
        while (true) {
            if (mark_member[m] == 1) {
                m = rand() % 20; // 랜덤 추첨
            }
            else {
                mark_member[m] = 1;
                count += 1;
                break;
            }
        }

        for (int j = 0; j < 20; j++) {
            if (mark_item[j] != 1) {
                if (max_score < score_table[m][j]) {
                    max_score = score_table[m][j];
                    k = j;
                }
            }
        }
        mark_item[k] = 1;
        total += max_score;
    }

    return total;
}



int main()
{
    FILE* fp;
    fp = fopen("satisfaction.txt", "r");

    int item = 0;
    int member = 0;
    int score = 0;
    int epoch = 0;
    int n = 0, s = 0;
    int max_score = 0;
    int score_table[20][20] = { 0, };
    char temp[100];
    int result;
    int store_data[100];

    printf("Please enter n : ");
    scanf("%d", &n);

    printf("Please enter s : ");
    scanf("%d", &s);


    fscanf(fp, "%s %s %s\n", &temp, &temp, &temp);

    while (!feof(fp))
    {
        //공백으로 분리된 파일 읽기
        fscanf(fp, "%d %d %d\n", &member, &item, &score);
        printf("Member %d is satisfied for item %d with satisfaction score %d\n", member, item, score);

        score_table[member - 1][item - 1] = score;
    }

    fclose(fp);

    for (epoch = 0; epoch < n; epoch++) {
        result = random_selection(score_table);
        store_data[epoch] = result;
        if (result > max_score) {
            max_score = result;
        }
        if (max_score > s)
            break;
    }

    printf("result: %d\n", max_score);


    return 0;
}