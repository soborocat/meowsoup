#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define ROOM_WIDTH 10
#define HME_POS 1
#define BWL_PO (ROOM_WIDTH - 2)

int main(void) {
	printf("****야옹이와 수프****\n\n");
    printf("      /\\_/\\\n");
    printf(" /\\  / o o \\\n");
    printf("//\\\\ \\~(*)~/\n");
    printf("`  \\/   ^ /\n");
    printf("   | \\|| ||\n");
    printf("   \\ '|| ||\n");
    printf("    \\)()-())\n\n");

    char name[10];
    int CPosX = 0;
    int dice;
    int friendshipPoint = 2;
    int soupCount = 0;
    printf("야옹이의 이름을 지어 주세요: ");
    scanf("%s", &name);
    printf("야옹이의 이름은 %s 입니다.\n", name);
    Sleep(1000);
    system("cls");
    while (1) {

        printf("================ 현재 상태 ================\n");
        printf("현재까지 만든 수프: %d\n", soupCount);
        printf("집사와의 관계(0~4): %d\n", friendshipPoint);

        switch (friendshipPoint) {
            case 0: printf("곁에 오는 것조차 싫어합니다.\n");break;
            case 1: printf("간식 자판기 취급입니다.\n"); break;
            case 2: printf("그럭저럭 쓸 만한 집사입니다.\n"); break;
            case 3: printf("훌륭한 집사로 인정 받고 있습니다.\n"); break;
            case 4: printf("집사 껌딱지입니다.\n"); break;
        }

        printf("===========================================\n\n");
        Sleep(500);
        printf("%s 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n", name);
        printf("주사위 눈이 %d 이상이면 냄비 쪽으로 이동합니다.\n", 6-friendshipPoint);
        printf("주사위를 굴립니다. 또르륵...\n");
        dice = rand() % 5 + 1;

        printf("%d이(가) 나왔습니다!\n", dice);

        if (dice >= 6 - friendshipPoint) {
            printf("냄비 쪽으로 움직입니다.\n\n");
            CPosX++;
        }
        if (CPosX == 0) {
            printf("%s은(는) 자신의 집에서 편안함을 느낍니다.\n\n");
        }
        // Render Room
        for (int i = 0; i < ROOM_WIDTH; i++) {
            printf("#");
        } // 0 Brick
        printf("\n#");
        for (int i = 0; i < BWL_PO; i++) {
            if (i == 0) {
                printf("H");
            }
            else if (i == BWL_PO - 1) {
                printf("B");
            }
            else {
                printf(" ");
            }
        } // 1 Items
        printf("#");

        printf("\n#");
        for (int i = 0; i < BWL_PO; i++) {
            if (i < CPosX) {
                printf(".");
            }
            else if (i == CPosX) {
                printf("C");
            }
            else {
                printf(" ");
            }
        } // 2 Cat
        printf("#\n");

        for (int i = 0; i < ROOM_WIDTH; i++) {
            printf("#");
        } // 3 Brick
        printf("\n\n");
        // End Render Room

        int select;
        printf("어떤 상호작용을 하시겠습니까?\t0. 아무것도 하지 않음.\t1. 긁어 주기\n");
        while (1) {
            printf(">> ");
            scanf("%d", &select);
            if (0 <= select && select <= 1) {
                break;
            }
        }
        switch (select) {
            case 0:
                printf("아무것도 하지 않습니다.\n4/6의 확률로 친밀도가 떨어집니다.\n");
                Sleep(500);
                dice = rand() % 5 + 1;
                printf("%d이(가) 나왔습니다!\n", dice);

                if (dice <= 4) {
                    printf("친밀도가 떨어집니다.\n");
                    if (friendshipPoint > 0) friendshipPoint--;
                } else {
                    printf("다행히 친밀도가 떨어지지 않았습니다.\n");
                }

                printf("현재 친밀도: %d\n", friendshipPoint);
                break;
            case 1:
                printf("%s의 턱을 긁어주었습니다.\n", name);
                printf("2/6의 확률로 친밀도가 높아집니다.\n");
                printf("주사위를 굴립니다. 또르륵...\n");
                Sleep(500);

                dice = rand() % 5 + 1;
                printf("%d이(가) 나왔습니다!\n", dice);
                if (dice <= 2) {
                    printf("친밀도가 높아집니다.\n");
                    if (friendshipPoint < 4) friendshipPoint++;
                }
                else {
                    printf("친밀도가 그대로입니다.\n");
                    printf("현재 친밀도: %d\n", friendshipPoint);
                }
                break;

        }
        Sleep(2500);
        system("cls");
	}
}
