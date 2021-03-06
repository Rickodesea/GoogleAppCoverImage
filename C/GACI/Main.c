#include <FreeImage.h>
#include <stdio.h>
#include "Main.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

const char* name = "GACI :::: Google App Cover Image";
const char * descript = "generate the required images for assets and for publishings from 1 copy of the cover image";
const char * author = "author(s): Alrick Grandison; updated: February 3, 2018 3:40AM EST";
const int version = 1;
const char *tutorial = "gaci [cover image filename]";

int main(int argc, char **argv){
    FreeImage_Initialise(FALSE);

    FreeImage_SetOutputMessage(errorHandler);

    if(argc < 2){
        printf("%s\n", name);
        printf("- %s\n", descript);
        printf("- %s\n", author);
        printf("- %d+%s\n", version, FreeImage_GetVersion());
        printf("- %s\n", FreeImage_GetCopyrightMessage());

        printf("%s", "\n");

        printf("====> %s\n\n\n", tutorial);
    } else if(argc == 2){

        const char* filename = argv[1];

        const FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(filename);
        const FIBITMAP* pbitmap = FreeImage_Load(fif, filename, 0);

        const char *outputFolder = "output/";
        const char *resFolder = "output/res/";
        const char *publishFolder = "output/publish/";
        const char *folderMDPI = "output/res/drawable-mdpi/";
        const char *folderHDPI = "output/res/drawable-hdpi/";
        const char *folderXHDPI = "output/res/drawable-xhdpi/";
        const char *folderXXHDPI = "output/res/drawable-xxhdpi/";
        const char *folderXXXHDPI = "output/res/drawable-xxxhdpi/";


        const char *res = "ic_launcher";
        const char *resWeb = "ic_launcher-web";
        const char *publishHiRes = "hires-icon";
        const char *publishFeature = "feature-graphic";
        const char *publishPromo = "promo-graphic";
        const char *publishTV = "tv-banner";
        const char *publishDaydream = "daydream-360";

        ///create output folder; it already exists delete it
        struct stat st;

        if( !(stat(outputFolder, &st) == 0 && S_ISDIR(st.st_mode)) ) mkdir(outputFolder, S_IRWXU);
        if( !(stat(resFolder, &st) == 0 && S_ISDIR(st.st_mode)) ) mkdir(resFolder, S_IRWXU);
        if( !(stat(publishFolder, &st) == 0 && S_ISDIR(st.st_mode)) ) mkdir(publishFolder, S_IRWXU);
        if( !(stat(folderMDPI, &st) == 0 && S_ISDIR(st.st_mode)) ) mkdir(folderMDPI, S_IRWXU);
        if( !(stat(folderHDPI, &st) == 0 && S_ISDIR(st.st_mode)) ) mkdir(folderHDPI, S_IRWXU);
        if( !(stat(folderXHDPI, &st) == 0 && S_ISDIR(st.st_mode)) ) mkdir(folderXHDPI, S_IRWXU);
        if( !(stat(folderXXHDPI, &st) == 0 && S_ISDIR(st.st_mode)) ) mkdir(folderXXHDPI, S_IRWXU);
        if( !(stat(folderXXXHDPI, &st) == 0 && S_ISDIR(st.st_mode)) ) mkdir(folderXXXHDPI, S_IRWXU);

        writeImage(fif, pbitmap, outputFolder, resWeb, 512, 512);
        writeImage(fif, pbitmap, folderMDPI, res, 48, 48);
        writeImage(fif, pbitmap, folderHDPI, res, 72, 72);
        writeImage(fif, pbitmap, folderXHDPI, res, 96, 96);
        writeImage(fif, pbitmap, folderXXHDPI, res, 144, 144);
        writeImage(fif, pbitmap, folderXXXHDPI, res, 192, 192);
        writeImage(fif, pbitmap, publishFolder, publishHiRes, 512, 512);
        writeImage(fif, pbitmap, publishFolder, publishFeature, 1024, 500);
        writeImage(fif, pbitmap, publishFolder, publishPromo, 180, 120);
        writeImage(fif, pbitmap, publishFolder, publishTV, 1280, 720);
        writeImage(fif, pbitmap, publishFolder, publishDaydream, 4096, 4096);
    }

    FreeImage_DeInitialise() ;

    return 0;
}


void errorHandler(FREE_IMAGE_FORMAT fif, const char *msg){
    printf("Format [%s] -> ", FreeImage_GetFormatFromFIF(fif));
    printf("%s\n", msg);
}

char *newFilename(const char* folder, const char* name, const char* extension){
    const char* period = ".";
    const int lenFolder = strlen(folder);
    const int lenName = strlen(name);
    const int lenExt = strlen(extension);
    const int lenPeriod = strlen(period);
    const int lenTotal = lenFolder + lenName + lenExt + lenPeriod;

    char* mem = malloc(lenTotal + 1);
    mem[lenTotal] = 0;

    copyMem(mem, 0, lenFolder, folder);
    copyMem(mem, lenFolder, lenName, name);
    copyMem(mem, lenFolder + lenName, lenPeriod, period);
    copyMem(mem, lenFolder + lenName + lenPeriod, lenExt, extension);

    return mem;
}

void copyMem(char *destination, const int index, const int length, const char* source){
    for(int i = 0; i < length; i++){
        destination[i + index] = source[i];
    }
}

void writeImage(const FREE_IMAGE_FORMAT fif, const FIBITMAP* pfib, const char* folder, const char* name, int width, int height){
    char* outFilename;
    FIBITMAP* outPbitmap;

    const char* extension = FreeImage_GetFormatFromFIF(fif);

    outFilename = newFilename(folder, name, extension);
    outPbitmap = FreeImage_Rescale((FIBITMAP*)pfib, width, height, FILTER_CATMULLROM);
    FreeImage_Save(fif, outPbitmap, outFilename, 0);
    free(outFilename);
    FreeImage_Unload(outPbitmap);
}



