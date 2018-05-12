/* prime.c
 */

int prime (int x)
{
    int i;

    for(i = 2; i < x; i++) {
        if(x % i == 0)    /* x 不是质数 */
            return 0;
    }
    return 1;             /* x 是质数 */
}
