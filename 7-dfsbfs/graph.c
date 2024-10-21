#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 11
#define TRUE 1
#define FALSE 0

// �׷��� Ÿ�� ����
typedef struct {
    int n;  // ���� ����
    int adj_mat[MAX_VERTICES][MAX_VERTICES];  // ���� ���
} GraphType;

int visited[MAX_VERTICES];  // �湮 ���� ���

// �׷��� �ʱ�ȭ
void graph_init(GraphType* g) {
    g->n = MAX_VERTICES;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

// ���� ����
void insert_edge(GraphType* g, int start, int end) {
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

// ���� �켱 Ž�� 
int dfs(GraphType* g, int start, int target) {
    int stack[MAX_VERTICES];
    int top = -1;
    int count = 0;  // �湮�� ��� ��

    // ���� �ʱ�ȭ �� ���� ���� push
    stack[++top] = start;

    while (top != -1) {
        int v = stack[top--];  // ���ÿ��� pop
        if (!visited[v]) {
            visited[v] = TRUE;
            printf("%d ", v);  // �湮�� ���� ���
            count++;
            if (v == target) {
                printf("\nŽ�� ����: %d\n�湮�� ����� ��: %d\n", v, count);
                return TRUE;
            }
            // ���� ������ ���ÿ� push
            for (int w = MAX_VERTICES - 1; w >= 0; w--) {
                if (g->adj_mat[v][w] && !visited[w]) {
                    stack[++top] = w;
                }
            }
        }
    }
    printf("\n�������� �ʴ� �������Դϴ�.\n");
    return FALSE;
}

// �ʺ� �켱 Ž�� 
int bfs(GraphType* g, int start, int target) {
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    int count = 0;  // �湮�� ��� ��

    // ť �ʱ�ȭ �� ���� ���� enqueue
    queue[rear++] = start;
    visited[start] = TRUE;

    while (front != rear) {
        int v = queue[front++];  // ť���� dequeue
        printf("%d ", v);  // �湮�� ���� ���
        count++;
        if (v == target) {
            printf("\nŽ�� ����: %d\n�湮�� ����� ��: %d\n", v, count);
            return TRUE;
        }
        // ���� �������� ť�� enqueue
        for (int w = 0; w < MAX_VERTICES; w++) {
            if (g->adj_mat[v][w] && !visited[w]) {
                queue[rear++] = w;
                visited[w] = TRUE;
            }
        }
    }
    printf("\n�������� �ʴ� �������Դϴ�.\n");
    return FALSE;
}

// �湮 ���� �ʱ�ȭ
void reset_visited() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = FALSE;
    }
}

int main() {
    GraphType g;
    graph_init(&g);

    // ���� �߰�
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
        printf("\n�޴� �Է�: ");
        printf("\n1. ���� �켱 Ž��\n");
        printf("2. �ʺ� �켱 Ž��\n");
        printf("3. ���α׷� ����\n");
        printf("����: ");
        scanf("%d", &choice);

        if (choice == 3) {
            printf("���α׷��� �����մϴ�.\n");
            break;
        }

        printf("���� ��ȣ�� Ž���� �� �Է�: ");
        scanf("%d %d", &start, &target);

        reset_visited();  // �湮 ���� �ʱ�ȭ

        if (choice == 1) {
            printf("���� �켱 Ž�� ���: ");
            dfs(&g, start, target);
        }
        else if (choice == 2) {
            printf("�ʺ� �켱 Ž�� ���: ");
            bfs(&g, start, target);
        }
        else {
            printf("�߸��� �����Դϴ�.\n");
        }
    }

    return 0;
}
