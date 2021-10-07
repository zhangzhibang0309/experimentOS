#include <stdio.h>
#include <stdlib.h>

struct jincheng_type {
    int pid;
    int priority;
    int size;
    int status; //��־����״̬��0 Ϊ�����ڴ棬1 Ϊ���ڴ棬2 Ϊ����
    char info[10];
};
struct jincheng_type neicun[20];
int counter = 0, guaqi = 0, pid, flag = 0;

// ��������
void create() {
    if (counter >= 20) {
        printf("�ڴ����������Ȼ�������ɱ�����̡�");
    } else {
        for (int i = 0; i < 20; i++) {
            if (neicun[i].status == 1)
                break;
            printf("\n�������µĽ���pid\n");
            scanf("%d", &(neicun[i].pid));

            // ����ǰ����ڴ�鿴�Ƿ������ͬ�Ľ���
            for (int j = 0; j < i; j++) {
                if (neicun[i].pid == neicun[j].pid) {
                    printf("�����Ѿ�����");
                    return;
                }
            }
            // ��д���̵ĸ�����Ϣ
            printf("����д�������ȼ�");
            scanf("%d", &neicun[i].priority);
            printf("����д���̴�С");
            scanf("%d", &neicun[i].size);
            printf("����д��������");
            scanf("%d", &neicun[i].info);
            // �������� ������Ϊ1
            neicun[i].status = 1;
            counter++;
        }
    }
}
// �鿴�������еĽ���
void run() {
    for (int i = 0; i < 20; i++) {
        if (neicun[i].status == 1) {
            //������н��̵ĸ�������ֵ
            printf("\n pid= %d", neicun[i].pid);
            printf(" youxian= %d", neicun[i].priority);
            printf(" daxiao= %d", neicun[i].size);
            printf(" zhuangtai= %d", neicun[i].status);
            printf(" info= %s", neicun[i].info);
            flag = 1;
        }
    }
    if (!flag)
        printf("\n ��ǰû�����н���\n");
}
// ɱ��ĳ������
void kill() {
    if (!counter) {
        printf("��ǰû�����н���\n");
        return;
    }
    printf("\n ����ɱ�����̵� ID ֵ");
    scanf("%d", &pid);
    for (int i = 0; i < 20; i++) {
        //��λ���ҵ���Ҫɱ���Ľ��̣�������״̬����Ӧ����
        if (pid == neicun[i].pid) {
            if (neicun[i].status == 1) {
                neicun[i].status = 0;
                counter--;
                printf("\n �ѳɹ�ɱ������\n");
            } else if (neicun[i].status == 0)
                printf("\n Ҫɱ���Ľ��̲�����\n");
            else
                printf("\n Ҫɱ���Ľ����ѱ�����\n");
            flag = 1;
            break;
        }
    }
    //�Ҳ�������˵�����̲�����
    if (!flag)
        printf("\n Ҫɱ���Ľ��̲�����\n");
}
// ����
void huanchu() {
    if (!counter) {
        printf("��ǰû���������еĽ���");
    }
    printf("\n��������Ҫ�������̵�ID");
    scanf("%d", &pid);
    for (int i = 0; i < 20; ++i) {
        if (pid == neicun[i].pid) {
            if (neicun[i].status == 1) {
                neicun[i].status = 2;// ����
                guaqi++;
                printf("����%d���ɹ�����", neicun[i].pid);
            } else if(neicun[i].status == 0) {
                printf("������%d���ǹ���״̬", neicun[i].pid);
            } else{
                printf("����%d�����ڴ��� killed", neicun[i].pid);
            }
            flag = 1;
            break;
        }
    }
    if(flag == 0) {
        printf("��������Ľ��̲�����");
    }
}
// ����
void huanxing() {
    if(!counter)
        printf("��ǰû���������еĽ���");
    if(!guaqi)
        printf("��ǰû�б�����Ľ���");
    printf("��������Ҫ���ѵĽ���idֵ");
    scanf("%d",&pid);
    for (int i = 0; i < 20; ++i) {
        if(neicun[i].pid == pid) {
            flag = 0;
            if(neicun[i].status == 2) {
                guaqi--;
                neicun[i].status = 1;
                printf("����%d�Ѿ���������",neicun[i].pid);
            }else if(neicun[i].status == 1)
                printf("����%d������ǻ���״̬",neicun[i].pid);
            else
                printf("�ڴ�%d���̲����ڴ� killed");
            break;
        }
    }
    if(flag) {
        printf("��������Ľ��̲����ڣ�");
    }
}

int main() {
    int n = 1;
    int num;
    //һ��ʼ���н��̶������ڴ���
    for (int i = 0; i < 20; i++)
        neicun[i].status = 0;
    while (n) {
        printf("\n********************************************");
        printf("\n* ������ʾϵͳ *");
        printf("\n********************************************");
        printf("\n 1.�����µĽ��� 2.�鿴���н��� ");
        printf("\n 3.����ĳ������ 4.ɱ�����н��� ");
        printf("\n 5.����ĳ������ 6.�˳�ϵͳ ");
        printf("\n********************************************");
        printf("\n ��ѡ��(1��6)\n");
        scanf("%d", &num);
        switch (num) {
            case 1:
                create();
                break;
            case 2:
                run();
                break;
            case 3:
                huanchu();
                break;
            case 4:
                kill();
                break;
            case 5:
                huanxing();
                break;
            case 6:
                exit(0);
            default:
                n = 0;
        }
        flag = 0; //�ָ����
    }
}