#define BLOCK_SIZE 8
void matrix_multiplication(int *a, int *b, int *output, int i, int k, int j) {
    for (int x = 0; x < i; x += BLOCK_SIZE) {
        for (int y = 0; y < j; y += BLOCK_SIZE) {
            for (int z = 0; z < k; z += BLOCK_SIZE) {
                
                // BLOCK
                for (int xx = x; xx < x + BLOCK_SIZE && xx < i; xx++) {
                    for (int yy = y; yy < y + BLOCK_SIZE && yy < j; yy++) {
                        int sum = 0;
                        for (int zz = z; zz < z + BLOCK_SIZE && zz < k; zz++) {
                            sum += a[xx * k + zz] * b[zz * j + yy];
                        }
                        output[xx * j + yy] += sum;
                    }
                }
            }
        }
    }
}
