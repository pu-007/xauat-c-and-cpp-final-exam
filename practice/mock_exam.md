# 自编模拟卷：100分，建议90分钟

依据六份资料题型自编。C按C99；除特别指出，变量均已初始化，所需头文件已包含，整数无溢出。

## A 选择（10×2=20分）

1. 哪个合法且不是关键字？A 2a B while C score_2 D a-b
2. `double x=5/2;`的值？A 2.5 B 2.0 C 0 D 编译错误
3. 读double x的正确格式？A scanf("%f",&x) B scanf("%lf",&x) C scanf("%lf",x) D printf("%lf",&x)
4. `int a[3]={1};`，a[2]？A 1 B 不确定 C 0 D 越界
5. `char s[]="ab";`，sizeof s与strlen(s)？A 2,2 B 3,2 C 2,3 D 3,3
6. C99中`int f(void)`？A 返回void B 无参数且返回int C 一个void参数 D 函数指针
7. `int (*p)[4]`？A 四个指针 B 指向4个int数组的指针 C 函数指针 D 二级指针
8. 哪个能修改调用者int？A 在值形参上赋值 B 向指针形参指向的对象赋值 C 改局部指针指向 D 改局部同名变量
9. 哪个循环保证至少一次？A for B while C do-while D 都不保证
10. 判断fscanf读一个int成功？A feof(fp)==0 B fscanf(fp,"%d",&x)==1 C x!=EOF D fp!=NULL

## B 读程序（4×5=20分）

1. `int a=2,b=9; int r=(a>3)&&(b++>0); printf("%d %d",r,b);`
2. `int a[]={2,4,6}; int *p=a; int x=*p++; (*p)++; printf("%d %d %d",x,*p,a[1]);`
3. `int s=0; for(int i=1;i<=5;i++){if(i==3)continue;s+=i;} printf("%d",s);`
4. 函数`int f(void){static int x=0;return ++x;}`；主函数`int a=f();int b=f();printf("%d %d",a,b);`

## C 程序填空（每空5分，共20分）

1. 冒泡排序（升序）：

```c
for(int end=n-1;end>0;--end)
    for(int j=0; ______ ;++j)
        if( ______ ) { int t=a[j];a[j]=a[j+1];a[j+1]=t; }
```

2. 往已有链表首部插入已分配好的p：

```c
p->next=______;
head=______;
```

## D 改错（5处，每处2分，共10分）

目标：读5个整数，输出其平均值。

```c
int a[5],sum;                 /* 1 */
for(int i=1;i<=5;++i) {       /* 2 */
    scanf("%d",a[i]);        /* 3 */
    sum*=a[i];               /* 4 */
}
printf("%.2f",sum/5);       /* 5：包含类型与除法问题 */
```

## E 编程（3×10=30分）

1. 输入0..20的n，输出n!与1!+...+n!。n=0时输出`1 0`。
2. 输入一行长度不超过100的英语字符串，判断是否回文，输出0/1。空串算回文。
3. 输入10个整数，使用自定义函数找出所有素数存入另一个数组，使用冒泡升序排序并输出；重复素数保留，空结果输出空行。

交卷前用0/1、并列、全负、无匹配、边界长度检查自己的解法。
