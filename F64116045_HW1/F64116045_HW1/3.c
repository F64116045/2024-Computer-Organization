#include<stdio.h>
int main()
{ 
    int f, i, j;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/3.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);
    int *p_x = &x[0] ;
    int *p_h = &h[0] ;
    int *p_y = &y[0] ;
    for (i = 0; i < 3; i++){ 
        for (j = 0; j < 2; j++){        	
            for (f = 0; f < 3; f++)
                asm volatile(
                "beq %[j], zero, case_1\n\t"
                "slli t6, %[f], 3\n\t"
                "mv t0, %[p_x]\n\t"
                "addi t0, t0, 4\n\t"
                "add t0, t0, t6\n\t"
                "mv t1 ,%[p_h]\n\t"
                "li t6 ,12\n\t"
                "mul t6, %[i], t6\n\t"
                "add t1, t1, t6\n\t"
                "beq x0, zero, continue\n\t"
		
		"case_1:\n\t"
		"slli t6, %[f], 3\n\t"
                "mv t0, %[p_x]\n\t"
                "add t0, t0, t6\n\t"
                "mv t1, %[p_h]\n\t"
                "li t6 ,12\n\t"
                "mul t6, %[i], t6\n\t"
                "add t1, t1, t6\n\t"
                "beq x0, zero, continue\n\t"
                
		"continue:\n\t"
		"li t6, 4\n\t"
		"mul t6, t6, %[f]\n\t"
		"add t1, t1, t6\n\t"
		
		"lw t2, 0(t0)\n\t"
                "lw t3, 0(t1)\n\t"
                "mul t4, t2, t3 \n\t"

                
		"lw t5, 0(%[p_y])\n\t"
		"add t5, t5, t4\n\t"
		"sw t5, 0(%[p_y])\n\t"
		"li t5, 2\n\t"
                "beq %[f], t5, move_y\n\t"
                "beq x0,zero, exit\n\t"
                
                "move_y:\n\t"
                "addi %[p_y], %[p_y], 4\n\t"
                
                "exit:\n\t"   
                :[p_x] "+r" (p_x), [p_y] "+r" (p_y), [p_h] "+r" (p_h)
                :[j] "r" (j), [f] "r" (f), [i] "r" (i)
                :"t0", "t1", "t2", "t3", "t4", "t5", "t6"
                );
	}
    }
    p_y = &y[0];
    for(i = 0; i < 6; i++)
    printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}
