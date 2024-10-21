#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 11
#define TRUE 1
#define FALSE 0

// 그래프 타입 정의
typedef struct {
    int n;  // 정점 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];  // 인접 행렬
} GraphType;

int visited[MAX_VERTICES];  // 방문 상태 기록

// 그래프 초기화
void graph_init(GraphType* g) {
    g->n = MAX_VERTICES;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

// 간선 삽입
void insert_edge(GraphType* g, int start, int end) {
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

// 깊이 우선 탐색 
int dfs(GraphType* g, int start, int target) {
    int stack[MAX_VERTICES];
    int top = -1;
    int count = 0;  // 방문한 노드 수

    // 스택 초기화 및 시작 정점 push
    stack[++top] = start;

    while (top != -1) {
        int v = stack[top--];  // 스택에서 pop
        if (!visited[v]) {
            visited[v] = TRUE;
            printf("%d ", v);  // 방문한 정점 출력
            count++;
            if (v == target) {
                printf("\n탐색 성공: %d\n방문한 노드의 수: %d\n", v, count);
                return TRUE;
            }
            // 인접 정점들 스택에 push
            for (int w = MAX_VERTICES - 1; w >= 0; w--) {
                if (g->adj_mat[v][w] && !visited[w]) {
                    stack[++top] = w;
                }
            }
        }
    }
    printf("\n존재하지 않는 데이터입니다.\n");
    return FALSE;
}

// 너비 우선 탐색 
int bfs(GraphType* g, int start, int target) {
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    int count = 0;  // 방문한 노드 수

    // 큐 초기화 및 시작 정점 enqueue
    queue[rear++] = start;
    visited[start] = TRUE;

    while (front != rear) {
        int v = queue[front++];  // 큐에서 dequeue
        printf("%d ", v);  // 방문한 정점 출력
        count++;
        if (v == target) {
            printf("\n탐색 성공: %d\n방문한 노드의 수: %d\n", v, count);
            return TRUE;
        }
        // 인접 정점들을 큐에 enqueue
        for (int w = 0; w < MAX_VERTICES; w++) {
            if (g->adj_mat[v][w] && !visited[w]) {
                queue[rear++] = w;
                visited[w] = TRUE;
            }
        }
    }
    printf("\n존재하지 않는 데이터입니다.\n");
    return FALSE;
}

// 방문 상태 초기화
void reset_visited() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = FALSE;
    }
}

int main() {
    GraphType g;
    graph_init(&g);

    // 간선 추가
    insert_edge(&g, 0, 2);
    insert_edge(&g, 0, 4);
    insert_edge(&g, 0, 5);
    insert_edge(&g, 0, 6);
    insert_edge(&g, 0, 9);
    insert_edge(&g, 1, 4);
    insert_edge(&g, 1, 5);
    insert_edge(&g, 1, 7);
    insert_edge(&g, 1, 10);
    insert_edge(&g, 2, 3);
    insert_edge(&g, 2, 4);
    insert_edge(&g, 3, 4);
    insert_edge(&g, 3, 5);
    insert_edge(&g, 4, 6);
    insert_edge(&g, 4, 7);
    insert_edge(&g, 6, 8);
    insert_edge(&g, 8, 9);
    insert_edge(&g, 8, 10);

    int choice, start, target;
    while (TRUE) {
        printf("\n메뉴 입력: ");
        printf("\n1. 깊이 우선 탐색\n");
        printf("2. 너비 우선 탐색\n");
        printf("3. 프로그램 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        if (choice == 3) {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        printf("시작 번호와 탐색할 값 입력: ");
        scanf("%d %d", &start, &target);

        reset_visited();  // 방문 상태 초기화

        if (choice == 1) {
            printf("깊이 우선 탐색 결과: ");
            dfs(&g, start, target);
        }
        else if (choice == 2) {
            printf("너비 우선 탐색 결과: ");
            bfs(&g, start, target);
        }
        else {
            printf("잘못된 선택입니다.\n");
        }
    }

    return 0;
}
