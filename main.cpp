#include <stdio.h>
#include <stdlib.h>

struct jincheng_type {
    int pid;
    int priority;
    int size;
    int status; //标志进程状态，0 为不在内存，1 为在内存，2 为挂起
    char info[10];
};
struct jincheng_type neicun[20];
int counter = 0, guaqi = 0, pid, flag = 0;

// 创建进程
void create() {
    if (counter >= 20) {
        printf("内存已满，请先换出或者杀死进程。");
    } else {
        for (int i = 0; i < 20; i++) {
            if (neicun[i].status == 1)
                break;
            printf("\n请输入新的进程pid\n");
            scanf("%d", &(neicun[i].pid));

            // 遍历前面的内存查看是否存在相同的进程
            for (int j = 0; j < i; j++) {
                if (neicun[i].pid == neicun[j].pid) {
                    printf("进程已经存在");
                    return;
                }
            }
            // 填写进程的各种信息
            printf("请填写进程优先级");
            scanf("%d", &neicun[i].priority);
            printf("请填写进程大小");
            scanf("%d", &neicun[i].size);
            printf("请填写进程内容");
            scanf("%d", &neicun[i].info);
            // 创建进程 将其标记为1
            neicun[i].status = 1;
            counter++;
        }
    }
}
// 查看正在运行的进程
void run() {
    for (int i = 0; i < 20; i++) {
        if (neicun[i].status == 1) {
            //输出运行进程的各个属性值
            printf("\n pid= %d", neicun[i].pid);
            printf(" youxian= %d", neicun[i].priority);
            printf(" daxiao= %d", neicun[i].size);
            printf(" zhuangtai= %d", neicun[i].status);
            printf(" info= %s", neicun[i].info);
            flag = 1;
        }
    }
    if (!flag)
        printf("\n 当前没有运行进程\n");
}
// 杀死某个进程
void kill() {
    if (!counter) {
        printf("当前没有运行进程\n");
        return;
    }
    printf("\n 输入杀死进程的 ID 值");
    scanf("%d", &pid);
    for (int i = 0; i < 20; i++) {
        //定位，找到所要杀死的进程，根据其状态做相应处理
        if (pid == neicun[i].pid) {
            if (neicun[i].status == 1) {
                neicun[i].status = 0;
                counter--;
                printf("\n 已成功杀死进程\n");
            } else if (neicun[i].status == 0)
                printf("\n 要杀死的进程不存在\n");
            else
                printf("\n 要杀死的进程已被挂起\n");
            flag = 1;
            break;
        }
    }
    //找不到，则说明进程不存在
    if (!flag)
        printf("\n 要杀死的进程不存在\n");
}
// 换出
void huanchu() {
    if (!counter) {
        printf("当前没有正在运行的进程");
    }
    printf("\n请输入想要换出进程的ID");
    scanf("%d", &pid);
    for (int i = 0; i < 20; ++i) {
        if (pid == neicun[i].pid) {
            if (neicun[i].status == 1) {
                neicun[i].status = 2;// 挂起
                guaqi++;
                printf("进程%d被成功换出", neicun[i].pid);
            } else if(neicun[i].status == 0) {
                printf("！进程%d已是挂起状态", neicun[i].pid);
            } else{
                printf("进程%d不在内存中 killed", neicun[i].pid);
            }
            flag = 1;
            break;
        }
    }
    if(flag == 0) {
        printf("您所输入的进程不存在");
    }
}
// 唤醒
void huanxing() {
    if(!counter)
        printf("当前没有正在运行的进程");
    if(!guaqi)
        printf("当前没有被挂起的进程");
    printf("请输入想要唤醒的进程id值");
    scanf("%d",&pid);
    for (int i = 0; i < 20; ++i) {
        if(neicun[i].pid == pid) {
            flag = 0;
            if(neicun[i].status == 2) {
                guaqi--;
                neicun[i].status = 1;
                printf("进程%d已经被唤醒了",neicun[i].pid);
            }else if(neicun[i].status == 1)
                printf("进程%d本身就是唤醒状态",neicun[i].pid);
            else
                printf("内存%d进程不在内存 killed");
            break;
        }
    }
    if(flag) {
        printf("你所输入的进程不存在！");
    }
}

int main() {
    int n = 1;
    int num;
    //一开始所有进程都不在内存中
    for (int i = 0; i < 20; i++)
        neicun[i].status = 0;
    while (n) {
        printf("\n********************************************");
        printf("\n* 进程演示系统 *");
        printf("\n********************************************");
        printf("\n 1.创建新的进程 2.查看运行进程 ");
        printf("\n 3.换出某个进程 4.杀死运行进程 ");
        printf("\n 5.唤醒某个进程 6.退出系统 ");
        printf("\n********************************************");
        printf("\n 请选择(1～6)\n");
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
        flag = 0; //恢复标记
    }
}