#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int result;
    // A error occurred
    opterr = 0;
    while(( result = getopt(argc, argv, "ab:c::") ) != -1)
    {
        switch (result) {
        case 'a':
            printf("option = a, optopt = %c, optarg = %s\n",optopt, optarg);
            break;
        case 'b':
            printf("option = b, optopt = %c, optarg = %s\n",optopt, optarg);
            break;
        case 'c':
            printf("option = c, optopt = %c, optarg = %s\n",optopt, optarg);
            break;
        default:
            printf("Default result is: %c\n", result);
            break;
        }
        printf("Next option is argv[%d]=%s\n", optind, argv[optind]);
    }
    printf("A error may be occurred which is result = %d", optind);
    //print remainded error.
    for(result = optind; result < argc; result++)
    {
        printf("-------argv[%d] = %s\n", result, argv[result]);
    }

    //print all argc after reordered.
    for(result = 1; result < argc; result++)
    {
        printf("At the end ------ argv[%d] = %s\n", result, argv[result]);
    }
    return 0;
}
