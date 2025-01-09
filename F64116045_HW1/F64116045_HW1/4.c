#include<stdio.h>
int main()
{ 
    int i = 0;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/4.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);
    
    int *p_x = &x[0];
    int *p_h = &h[0];
    int *p_y = &y[0];
    
    asm volatile(
        "li %[i], 0                      \n\t" // 初始化 i = 0
        "loop1:                          \n\t"
        "  mv t0, %[p_x]                 \n\t" // t0 存儲 p_x
        "  li t3, 0                      \n\t" // 初始化 j = 0
        "  li t4, 0                      \n\t" // 初始化 f = 0
        "loop2:                          \n\t"
        "  mv t1, %[p_h]                 \n\t" // t1 存儲 p_h
        "  li t5, 12			\n\t"
        "  mul t5, t5, %[i]		\n\t"
        "  add t1, t1, t5		\n\t"
        "  li t4, 0                      \n\t" // 初始化 f = 0
        "loop3:                          \n\t"
        "  lw t2, 0(t0)                  \n\t" // *p_x
        "  lw t6, 0(t1)                  \n\t" // *p_h
        "  mul t6, t2, t6                \n\t" // 
        "  lw t5, 0(%[p_y])              \n\t" // 取得 *p_y 的值
        "  add t6, t5, t6                \n\t" // 將 t6 加到 *p_y
        "  sw t6, 0(%[p_y])              \n\t" // 將 t6 存回 *p_y
        "  addi t0, t0, 8                \n\t" // p_x++
        "  addi t1, t1, 4                \n\t" // p_h++
        "  addi t4, t4, 1                \n\t" // f++
        
        "  li t5, 3			\n\t"
        "  bne t4, t5, loop3     \n\t" // 
        "  addi %[p_y], %[p_y], 4        \n\t" // p_y++
        "  mv t0, %[p_x]		\n\t"
        "  addi t0, t0, 4		\n\t"
        "  addi t3, t3, 1                \n\t" // j++
        "  li t5, 2			\n\t"
        "  bne t3, t5, loop2     \n\t" // 
        "  addi %[i], %[i], 1            \n\t" // i++
        "  li t5, 3			\n\t"
        "  bne %[i], t5, loop1  \n\t" // 
        : [p_x] "+r" (p_x), [p_h] "+r" (p_h), [p_y] "+r" (p_y), [i] "+r" (i)
    );

    p_y = &y[0];
    for(i = 0; i < 6; i++)
        printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}
