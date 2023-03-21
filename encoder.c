#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char encodeChar(char letter, int offset, int isAddition);
static void invalidParamError(char *param);
static void openFileError(char *fileName);

int main(int argc, char **argv)
{
    int debug = 0;
    int encoderMode = 1;
    int indexIncrement = 0;
    char *firstCharOfIndex = "0";
    FILE *output = stdout;
    FILE *input = stdin;

    // Part 1
    for (int i = 1; i < argc; i++)
    {

        char first = argv[i][0];
        char second = argv[i][1];
        switch (first)
        {
        case '+':
            switch (second)
            {
            case 'D':
                debug = 1;
                break;
            case 'e':
                if (argv[i][2] != '\0')
                    firstCharOfIndex = &argv[i][2];
                break;

            default:
                invalidParamError(argv[i]);
            }
            break;
        case '-':
            switch (second)
            {
            case 'D':
                debug = 0;
                break;
            case 'e':
                if (argv[i][2] != '\0')
                    firstCharOfIndex = &argv[i][2];
                encoderMode = 0;
                break;
            case 'i':
                if ((input = fopen(&argv[i][2], "r")) == NULL)
                    openFileError(&argv[i][2]);
                break;
            case 'o':
                output = fopen(&argv[i][2], "w");
                break;
            default:
                invalidParamError(argv[i]);
            }
            break;

        default:
            invalidParamError(argv[i]);
        }

        if (debug)
            fprintf(stderr, "%s\n", argv[i]);
    }

    // Part 2
    char letter;

    while ((letter = fgetc(input)) != EOF)
    {
        char key = firstCharOfIndex[indexIncrement];
        if (key == '\0')
        {
            key = *firstCharOfIndex;
            indexIncrement = 0;
        }
        indexIncrement++;

        int offset = key - 48;
        fputc(encodeChar(letter, offset, encoderMode), output);
    }

    if (output != stdout)
        fclose(output);

    return 0;
}

static char encodeChar(char letter, int offset, int isAddition)
{
    int charValue = isAddition == 1 ? letter + offset : letter - offset;
    int modulo10 = isAddition == 1 ? -10 : 10;
    int modulo26 = isAddition == 1 ? -26 : 26;

    if (48 <= letter && letter <= 57)
        return charValue < 48 || charValue > 57 ? charValue + modulo10 : charValue;
    if (65 <= letter && letter <= 90)
        return charValue < 65 || charValue > 90 ? charValue + modulo26 : charValue;
    if (97 <= letter && letter <= 122)
        return charValue < 97 || charValue > 122 ? charValue + modulo26 : charValue;

    return letter;
}

static void invalidParamError(char *param)
{
    fprintf(stderr, "Invalid parameter -> %s\n", param);
    exit(0);
}

static void openFileError(char *fileName)
{
    fprintf(stderr, "Couldn't open file named: %s\n", fileName);
    exit(0);
}
