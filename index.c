#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define ROOM_WIDTH 20
#define HOME_POS 1
#define BOWL_POS (ROOM_WIDTH - 2)
#define MAX_NAME_LENGTH 100
#define MAX_FRIENDSHIP 4
#define MAX_MOOD 3

char catName[MAX_NAME_LENGTH];
int catPosX = 1;
int catPrevX = 1;
int catMood = 3;
int friendshipPoint = 2;
int soupCount = 0;
int cutePoints = 0;
int turn = 1;

int toyMouse = 0;
int toyLaser = 0;
int toyScratchingPost = 0;
int scratcherPos = 0;
int toyCatTower = 0;
int catTowerPos = 0;

static void initGame() {
    srand((unsigned int)time(NULL));
    catPosX = 1;
    catPrevX = 1;
    catMood = 3;
    friendshipPoint = 2;
    soupCount = 0;
    cutePoints = 0;
    turn = 1;
    toyMouse = 0;
    toyLaser = 0;
    toyScratchingPost = 0;
    scratcherPos = 0;
    toyCatTower = 0;
    catTowerPos = 0;
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
    printf("CP: %d 포인트\n", cutePoints);
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

    for (int i = 1; i < ROOM_WIDTH - 1; i++) {
        if (i == HOME_POS) {
            printf("H");
        }
        else if (i == BOWL_POS) {
            printf("B");
        }
        else if (toyScratchingPost && i == scratcherPos) {
            printf("S");
        }
        else if (toyCatTower && i == catTowerPos) {
            printf("T");
        }
        else {
            printf(" ");
        }
    }
    printf("#\n#");

    for (int i = 1; i < ROOM_WIDTH - 1; i++) {
        if (i == catPosX) {
            printf("C");
        }
        else if (i == catPrevX && i != catPosX) {
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
    printf("6-%d: 주사위 눈이 %d이하이면 그냥 기분이 나빠집니다.\n", friendshipPoint, 6 - friendshipPoint);
    printf("주사위를 굴립니다. 또르륵...\n");

    int dice = rollDice();
    printf("%d이(가) 나왔습니다!\n", dice);

    if (dice <= 6 - friendshipPoint && catMood > 0) {
        printf("%s의 기분이 나빠집니다: %d->%d\n", catName, catMood, catMood - 1);
        catMood--;
    }
    else {
        printf("다행히 기분이 나빠지지 않았습니다.\n");
    }
}

static void moveCatByMood() {
    catPrevX = catPosX;

    switch (catMood) {
    case 0:
        if (catPosX > HOME_POS) {
            catPosX--;
            printf("기분이 매우 나쁜 %s은(는) 집으로 향합니다.\n\n", catName);
        }
        else {
            printf("기분이 매우 나쁜 %s은(는) 집에서 대기합니다.\n\n", catName);
        }
        break;

    case 1:
    {
        int closestToy = -1;
        int minDistance = ROOM_WIDTH;

        if (toyScratchingPost) {
            int distance = abs(catPosX - scratcherPos);
            if (distance < minDistance) {
                minDistance = distance;
                closestToy = scratcherPos;
            }
        }

        if (toyCatTower) {
            int distance = abs(catPosX - catTowerPos);
            if (distance < minDistance) {
                minDistance = distance;
                closestToy = catTowerPos;
            }
        }

        if (closestToy != -1) {
            if (catPosX < closestToy) {
                catPosX++;
                printf("%s은(는) 심심해서 스크래처 쪽으로 이동합니다.\n\n", catName);
            }
            else if (catPosX > closestToy) {
                catPosX--;
                printf("%s은(는) 심심해서 스크래처 쪽으로 이동합니다.\n\n", catName);
            }
            else {
                printf("%s은(는) 심심해서 놀이기구에서 대기합니다.\n\n", catName);
            }
        }
        else {
            printf("놀 거리가 없어서 기분이 매우 나빠집니다.\n\n");
            catMood--;
            if (catMood < 0) catMood = 0;
        }
    }
    break;

    case 2:
        printf("%s은(는) 기분좋게 식빵을 굽고 있습니다.\n\n", catName);
        break;

    case 3:
        if (catPosX < BOWL_POS) {
            catPosX++;
            printf("%s은(는) 골골송을 부르며 수프를 만들러 갑니다.\n\n", catName);
        }
        else {
            printf("%s은(는) 냄비 앞에서 골골송을 부릅니다.\n\n", catName);
        }
        break;
    }

    if (catPosX < 1) catPosX = 1;
    if (catPosX >= BOWL_POS) catPosX = BOWL_POS;
}

static void handleLocationEvents() {
    if (catPosX == HOME_POS && catPosX == catPrevX) {
        if (catMood < MAX_MOOD) {
            catMood++;
            printf("%s은(는) 자신의 집에서 편안함을 느낍니다.\n", catName);
            printf("기분이 좋아졌습니다: %d\n", catMood);
        }
    }
    else if (catPosX == BOWL_POS) {
        makeSoup();
    }
    else if (toyScratchingPost && catPosX == scratcherPos) {
        printf("%s이(가) 스크래처에서 기분을 풀고 있습니다.\n", catName);
        if (catMood < MAX_MOOD) {
            catMood++;
            printf("기분이 조금 좋아졌습니다: %d\n", catMood);
        }
    }
    else if (toyCatTower && catPosX == catTowerPos) {
        printf("%s이(가) 캣타워에서 날아다닙니다.\n", catName);
        catMood += 2;
        if (catMood > MAX_MOOD) catMood = MAX_MOOD;
        printf("기분이 제법 좋아졌습니다: %d\n", catMood);
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
    printf("어떤 상호작용을 하시겠습니까?\n");
    printf("  0. 아무것도 하지 않음\n");
    printf("  1. 긁어 주기\n");

    int maxOption = 1;

    if (toyMouse) {
        printf("  %d. 장난감 쥐로 놀아 주기\n", ++maxOption);
    }
    if (toyLaser) {
        printf("  %d. 레이저 포인터로 놀아 주기\n", ++maxOption);
    }

    int select = getValidInput(0, maxOption);
    int dice = rollDice();

    switch (select) {
    case 0:
        printf("아무것도 하지 않습니다.\n");
        printf("%s의 기분이 나빠졌습니다: %d->%d\n", catName, catMood, (catMood - 1 < 0 ? 0 : catMood - 1));
        printf("5/6의 확률로 친밀도가 떨어집니다.\n");
        printf("주사위를 굴립니다. 또르륵...\n");
        printf("%d이(가) 나왔습니다!\n", dice);

        if (dice <= 5 && friendshipPoint > 0) {
            printf("집사와의 관계가 나빠집니다.\n");
            friendshipPoint--;
        }
        else {
            printf("다행히 친밀도가 떨어지지 않았습니다.\n");
        }

        catMood--;
        if (catMood < 0) catMood = 0;
        break;

    case 1:
        printf("%s의 턱을 긁어주었습니다.\n", catName);
        printf("%s의 기분은 그대로입니다: %d\n", catName, catMood);
        printf("2/6의 확률로 친밀도가 높아집니다.\n");
        printf("주사위를 굴립니다. 또르륵...\n");
        printf("%d이(가) 나왔습니다!\n", dice);

        if (dice >= 5 && friendshipPoint < MAX_FRIENDSHIP) {
            printf("친밀도가 높아집니다.\n");
            friendshipPoint++;
        }
        else {
            printf("친밀도가 그대로입니다.\n");
        }
        break;

    case 2:
        if (toyMouse && !toyLaser) {
            printf("장난감 쥐로 %s와 놀아 주었습니다.\n", catName);
            printf("%s의 기분이 조금 좋아졌습니다: %d->%d\n", catName, catMood, (catMood + 1 > MAX_MOOD ? MAX_MOOD : catMood + 1));
            catMood++;
            if (catMood > MAX_MOOD) catMood = MAX_MOOD;

            printf("%d이(가) 나왔습니다!\n", dice);
            if (dice >= 4 && friendshipPoint < MAX_FRIENDSHIP) {
                printf("친밀도가 높아집니다.\n");
                friendshipPoint++;
            }
            else {
                printf("친밀도는 그대로입니다.\n");
            }
        }
        else if (toyLaser && !toyMouse) {
            printf("레이저 포인터로 %s와 신나게 놀아 주었습니다.\n", catName);
            printf("%s의 기분이 꽤 좋아졌습니다: %d->%d\n", catName, catMood, (catMood + 2 > MAX_MOOD ? MAX_MOOD : catMood + 2));
            catMood += 2;
            if (catMood > MAX_MOOD) catMood = MAX_MOOD;

            printf("%d이(가) 나왔습니다!\n", dice);
            if (dice >= 2 && friendshipPoint < MAX_FRIENDSHIP) {
                printf("친밀도가 높아집니다.\n");
                friendshipPoint++;
            }
            else {
                printf("친밀도는 그대로입니다.\n");
            }
        }
        else if (toyMouse && toyLaser) {
            printf("장난감 쥐로 %s와 놀아 주었습니다.\n", catName);
            printf("%s의 기분이 조금 좋아졌습니다: %d->%d\n", catName, catMood, (catMood + 1 > MAX_MOOD ? MAX_MOOD : catMood + 1));
            catMood++;
            if (catMood > MAX_MOOD) catMood = MAX_MOOD;

            printf("%d이(가) 나왔습니다!\n", dice);
            if (dice >= 4 && friendshipPoint < MAX_FRIENDSHIP) {
                printf("친밀도가 높아집니다.\n");
                friendshipPoint++;
            }
            else {
                printf("친밀도는 그대로입니다.\n");
            }
        }
        break;

    case 3:
        if (toyMouse && toyLaser) {
            printf("레이저 포인터로 %s와 신나게 놀아 주었습니다.\n", catName);
            printf("%s의 기분이 꽤 좋아졌습니다: %d->%d\n", catName, catMood, (catMood + 2 > MAX_MOOD ? MAX_MOOD : catMood + 2));
            catMood += 2;
            if (catMood > MAX_MOOD) catMood = MAX_MOOD;

            printf("%d이(가) 나왔습니다!\n", dice);
            if (dice >= 2 && friendshipPoint < MAX_FRIENDSHIP) {
                printf("친밀도가 높아집니다.\n");
                friendshipPoint++;
            }
            else {
                printf("친밀도는 그대로입니다.\n");
            }
        }
        break;
    }

    printf("현재 친밀도: %d\n", friendshipPoint);
}

static void generateCP() {
    int earnedCP = (catMood > 0 ? catMood - 1 : 0) + friendshipPoint;
    cutePoints += earnedCP;
    printf("%s의 기분과 친밀도에 따라서 CP가 %d 포인트 생산되었습니다.\n", catName, earnedCP);
    printf("보유 CP: %d 포인트\n", cutePoints);
}

static void handleShop() {
    printf("상점에서 물건을 살 수 있습니다.\n");
    printf("어떤 물건을 구매할까요?\n");
    printf("  0. 아무 것도 사지 않는다.\n");
    printf("  1. 장난감 쥐: 1 CP ");
	if (toyMouse) {
		printf("(품절)\n");
	}
	else {
		printf("\n");
	}

    printf("  2. 레이저 포인터: 2 CP ");
    if (toyLaser) {
        printf("(품절)\n");
    }
    else {
		printf("\n");
    }

    printf("  3. 스크래처: 4 CP ");
    if (toyScratchingPost) {
		printf(" (품절)\n");
    }
    else {
        printf("\n");
    }

    printf("  4. 캣타워: 6 CP ");
    if (toyCatTower) {
		printf("(품절)\n");
    }
    else {
        printf("\n");
    }

    int choice = getValidInput(0, 4);

    switch (choice) {
    case 0:
        printf("아무 것도 사지 않습니다.\n");
        break;
    case 1:
        if (toyMouse) {
            printf("장난감 쥐를 이미 구매했습니다.\n");
        }
        else if (cutePoints >= 1) {
            printf("장난감 쥐를 구매했습니다.\n");
            cutePoints -= 1;
            printf("보유 CP %d 포인트\n", cutePoints);
            toyMouse = 1;
        }
        else {
            printf("CP가 부족합니다.\n");
        }
        break;
    case 2:
        if (toyLaser) {
            printf("레이저 포인터를 이미 구매했습니다.\n");
        }
        else if (cutePoints >= 2) {
            printf("레이저 포인터를 구매했습니다.\n");
            cutePoints -= 2;
            printf("보유 CP %d 포인트\n", cutePoints);
            toyLaser = 1;
        }
        else {
            printf("CP가 부족합니다.\n");
        }
        break;
    case 3:
        if (toyScratchingPost) {
            printf("스크래처를 이미 구매했습니다.\n");
        }
        else if (cutePoints >= 4) {
            printf("스크래처를 구매했습니다.\n");
            cutePoints -= 4;
            printf("보유 CP %d 포인트\n", cutePoints);
            toyScratchingPost = 1;
            do {
                scratcherPos = rand() % (ROOM_WIDTH - 2) + 1;
            } while (scratcherPos == HOME_POS || scratcherPos == BOWL_POS);
        }
        else {
            printf("CP가 부족합니다.\n");
        }
        break;
    case 4:
        if (toyCatTower) {
            printf("캣타워를 이미 구매했습니다.\n");
        }
        else if (cutePoints >= 6) {
            printf("캣타워를 구매했습니다.\n");
            cutePoints -= 6;
            printf("보유 CP %d 포인트\n", cutePoints);
            toyCatTower = 1;
            do {
                catTowerPos = rand() % (ROOM_WIDTH - 2) + 1;
            } while (catTowerPos == HOME_POS || catTowerPos == BOWL_POS || catTowerPos == scratcherPos);
        }
        else {
            printf("CP가 부족합니다.\n");
        }
        break;
    }
}

static int handleRandomQuest() {
    if (turn % 3 == 0) {
        printf("돌발 퀘스트가 발생했습니다!\n");
        printf("도전? (1: 예, 0: 아니오)\n");

        int challenge = getValidInput(0, 1);

        if (challenge == 1) {
            int num1 = rand() % 10;
            int num2 = rand() % 10;
            int answ;
            printf("%d + %d = ?\n", num1, num2);
            int answer = num1 + num2;
            printf("\n>> ");
            scanf("%d", &answ);

            if (answ == answer) {
                printf("정답입니다!\n");
                return 1;
            }
            else {
                printf("틀렸습니다!\n");
            }
        }
        else {
            printf("돌발 퀘스트를 포기합니다.\n");
        }
        printf("게임을 계속 진행합니다.\n");
    }
    return 0;
}

int main(void) {
    initGame();
    displayTitle();

    printf("야옹이의 이름을 지어 주세요: ");
    scanf("%99s", catName);
    printf("야옹이의 이름은 %s 입니다.\n", catName);

    Sleep(1000);
    system("cls");

    while (1) {
        displayStatus();
        Sleep(500);

        handleMoodChange();
        moveCatByMood();
        renderRoom();
        Sleep(500);

        handleLocationEvents();
        Sleep(500);

        handleInteraction();
        printf("\n");
        Sleep(500);

        generateCP();
        Sleep(500);

        handleShop();
        Sleep(2500);
        system("cls");

        turn++;
        Sleep(500);
        system("cls");
    }

    return 0;
}
