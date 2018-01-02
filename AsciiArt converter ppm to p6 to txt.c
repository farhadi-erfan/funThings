#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int convertP6toP3(char* inputName, char* tempName, char* outputName) {
    FILE *src, *dest;
    char magicNumber[3];
    int height, width, depth;
    unsigned char red, green, blue;
    int i, j, widthCounter = 1;
    src = fopen(inputName, "rb");
    dest = fopen(tempName, "w+");
    fscanf(src, "%s", magicNumber);
    if (strcmp(magicNumber, "P6") != 0) {
        return 0;
	}
    fscanf(src, "\n%d %d\n%d\n", &width, &height, &depth);
    fprintf(dest, "P3\n");
    fprintf(dest, "%d %d\n%d\n", width, height, depth);;
    for (i = 0; i < width * height; i++) {
        for (j = 0;  j < 3; j++) {
            fread(&red, 1, 1, src);
            fread(&green, 1, 1, src);
            fread(&blue, 1, 1, src);
        }
        for (j = 0;  j < 3; j++) {
            fprintf(dest, "%d %d %d ", red, green, blue);
		}
        if (widthCounter == width) {
            fprintf(dest, "\n");
            widthCounter = 1;
        } else {
            widthCounter++;
		}
    }
    fclose(src);
    fclose(dest);
    return 1;
}

int blackAndWhite(char* inputName, char* tempName, char* outputName) {
    FILE *src, *pic;
    char typeChecker[3];
    int width, height, depth;
    int red, green, blue;
    int widthCounter = 1;
    char characters[] = {'#', '$', '@', '%', '&', '?', '!', '+', '=', '*', '<', '>', ':', ',', '^', '_', '-', ' '};
    int length = 16;
    pic = fopen(outputName, "w+");
    src = fopen(tempName, "r");
    fscanf(src, "%s", typeChecker);
    if (strcmp(typeChecker, "P3") != 0) {
        return 0;
    }
    fscanf(src, "\n%d %d\n%d\n", &width, &height, &depth);
// have to handle comments
    int i = 0;
	for (i = 0; i < width * height; ++i) {
        fscanf(src, "%d %d %d", &red, &blue, &green);
        int blackAndWhite = (red + green + blue) / 3;
        int charNum = (int) blackAndWhite / ((depth + 1) / length);
        fprintf(pic, "%c", characters[charNum]);
        if (widthCounter == width) {
            widthCounter = 1;
            fscanf(src, "\n");
            fprintf(pic, "\n");
        } else {
            widthCounter++;
            fscanf(src, " ");
            fprintf(pic, " ");
        }
    }
    fclose(src);
    fclose(pic);
    return 1;
}

int main() {
	char* inputName = malloc (100 * sizeof(char));
	char* outputName = malloc (100 * sizeof(char));
	char* tempName = malloc (100 * sizeof(char));
	scanf("%s", inputName);
	scanf("%s", outputName);
	strcpy(tempName, inputName);
	strcat(inputName, ".ppm");
	strcat(tempName, " p3.ppm");
	strcat(outputName, ".txt");
	if (convertP6toP3(inputName, tempName, outputName) == 1) {
		if (blackAndWhite(inputName, tempName, outputName) == 1) {
			return 1;
		} else {
			printf("error in converting to ascii art");
		}
	} else {
		printf("error in converting to p6");
	}
	return 0;
}
