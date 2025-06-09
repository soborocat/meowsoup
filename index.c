#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define ROOM_WIDTH 14
#define HOME_POS 1
#define BOWL_POS (ROOM_WIDTH - 2)
#define MAX_NAME_LENGTH 20
#define MAX_FRIENDSHIP 4
#define MAX_MOOD 3

char catName[MAX_NAME_LENGTH];
int catPosX = 0;
int catPrevX = 0;
int catMood = 3;
int friendshipPoint = 2;
int soupCount = 0;
int toyScratchingPost = -1;
int toyCatTower = -1;

static void initGame() {
    srand((unsigned int)time(NULL));
    catPosX = 0;
    catPrevX = 0;
    catMood = 3;
    friendshipPoint = 2;
    soupCount = 0;
    toyScratchingPost = -1;
    toyCatTower = -1;
}

static void displayTitle() {
    printf("****야옹이와 수프****\n\n");
    printf("      /\\_/\\\n");
    printf(" /\\  / o o \\\n");
    printf("//\\\\ \\~(*)~/\n");
    printf("`  \\/   ^ /\n");
    printf("   | \\|| ||\n");
    printf("   \\ '|| ||\n");
    printf("    \\)()-())\n\n");
}

static void printMoodDescription(int mood) {
    switch (mood) {
    case 0: printf("기분이 매우 나쁩니다.\n"); break;
    case 1: printf("심심해합니다.\n"); break;
    case 2: printf("식빵을 굽습니다.\n"); break;
    case 3: printf("골골송을 부릅니다.\n"); break;
    }
}

static void printFriendshipDescription(int friendship) {
    switch (friendship) {
    case 0: printf("곁에 오는 것조차 싫어합니다.\n"); break;
    case 1: printf("간식 자판기 취급입니다.\n"); break;
    case 2: printf("그럭저럭 쓸 만한 집사입니다.\n"); break;
    case 3: printf("훌륭한 집사로 인정 받고 있습니다.\n"); break;
    case 4: printf("집사 껌딱지입니다.\n"); break;
    }
}

static void displayStatus() {
    printf("================ 현재 상태 ================\n");
    printf("현재까지 만든 수프: %d개\n", soupCount);
    printf("%s의 기분(0~3) : %d\n  ", catName, catMood);
    printMoodDescription(catMood);
    printf("집사와의 관계(0~4): %d\n  ", friendshipPoint);
    printFriendshipDescription(friendshipPoint);
    printf("===========================================\n\n");
}

static void renderRoom() {
    for (int i = 0; i < ROOM_WIDTH; i++) {
        printf("#");
    }
    printf("\n#");

    for (int i = 0; i < BOWL_POS; i++) {
        if (i == 0) {
            printf("H");
        }
        else if (i == toyScratchingPost - 1) {
            printf("S");
        }
        else if (i == toyCatTower - 1) {
            printf("T");
        }
        else if (i == BOWL_POS - 1) {
            printf("B");
        }
        else {
            printf(" ");
        }
    }
    printf("#\n#");

    for (int i = 0; i < BOWL_POS; i++) {
        if (i == catPosX) {
            printf("C");
        }
        else if (i == catPrevX) {
            printf(".");
        }
        else {
            printf(" ");
        }
    }
    printf("#\n");

    for (int i = 0; i < ROOM_WIDTH; i++) {
        printf("#");
    }
    printf("\n\n");
}

static int rollDice() {
    return rand() % 6 + 1;
}

static void makeSoup() {
    soupCount++;
    int soupType = rand() % 3;

    if (soupType == 0) {
        printf("%s이(가) 감자 수프를 만들었습니다!\n\n", catName);
    }
    else if (soupType == 1) {
        printf("%s이(가) 양송이 수프를 만들었습니다!\n\n", catName);
    }
    else {
        printf("%s이(가) 브로콜리 수프를 만들었습니다!\n\n", catName);
    }

    printf("현재까지 만든 수프: %d개\n", soupCount);
}

static void handleMoodChange() {
    printf("6-2: 주사위 눈이 4이하이면 그냥 기분이 나빠집니다.\n");
    printf("주사위를 굴립니다. 또르륵...\n");

    int dice = rollDice();
    printf("%d이(가) 나왔습니다!\n", dice);

    if (dice < 6 - friendshipPoint && catMood > 0) {
        printf("%s의 기분이 나빠집니다: %d->%d\n", catName, catMood, catMood - 1);
        catMood--;
    }
}

static int getValidInput(int min, int max) {
    int input;
    do {
        printf(">> ");
        scanf("%d", &input);
    } while (input < min || input > max);
    return input;
}

static void handleInteraction() {
    printf("어떤 상호작용을 하시겠습니까?\n  0. 아무것도 하지 않음.\n  1. 긁어 주기\n");

    int select = getValidInput(0, 1);
    int dice = rollDice();

    switch (select) {
    case 0:
        printf("아무것도 하지 않습니다.\n4/6의 확률로 친밀도가 떨어집니다.\n");
        printf("%d이(가) 나왔습니다!\n", dice);

        if (dice <= 4 && friendshipPoint > 0) {
            printf("친밀도가 떨어집니다.\n");
            friendshipPoint--;
        }
        else {
            printf("다행히 친밀도가 떨어지지 않았습니다.\n");
        }
        break;

    case 1:
        printf("%s의 턱을 긁어주었습니다.\n", catName);
        printf("2/6의 확률로 친밀도가 높아집니다.\n");
        printf("주사위를 굴립니다. 또르륵...\n");
        printf("%d이(가) 나왔습니다!\n", dice);

        if (dice <= 2 && friendshipPoint < MAX_FRIENDSHIP) {
            printf("친밀도가 높아집니다.\n");
            friendshipPoint++;
        }
        else {
            printf("친밀도가 그대로입니다.\n");
        }
        break;
    }

    printf("현재 친밀도: %d\n", friendshipPoint);
}

int main(void) {
    initGame();
    displayTitle();

    printf("야옹이의 이름을 지어 주세요: ");
    scanf("%19s", catName);  // 버퍼 오버플로우 방지
    printf("야옹이의 이름은 %s 입니다.\n", catName);

    Sleep(1000);
    system("cls");

    while (1) {
        displayStatus();
        Sleep(500);

        renderRoom();
        handleMoodChange();
        Sleep(500);
        
        if (catPosX == 0) {
            printf("%s은(는) 자신의 집에서 편안함을 느낍니다.\n\n", catName);
        }
        else if (catPosX == BOWL_POS - 1) {
            makeSoup();
        }

        Sleep(500);

        handleInteraction();

        catPrevX = catPosX;
        Sleep(2500);
        system("cls");
    }

    return 0;
}
