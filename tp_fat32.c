#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define phy_disk "/dev/sdb"
FILE *file;
//------------------------------------------------------
    unsigned int sectorSize;
    unsigned int sectorPerCluster;
    unsigned int reservedSectors;
    unsigned int fatTablesNumber;
    unsigned int fatSize;
    unsigned int rootCluster;
    unsigned int rootAdr;
//------------------------------------------------------

struct tfile{
    char file_name[256];
    int size;
    int first_cluster;
    char type;
};

void getParameters(){
    unsigned char buffer[512];
    fread(buffer, 1, 512, file);
    sectorSize = buffer[11] | buffer[12]<<8;
    sectorPerCluster = buffer[13];
    reservedSectors = buffer[14] | buffer[15]<<8;
    fatTablesNumber = buffer[16];
    fatSize = buffer[36] | buffer[37]<<8 | buffer[38]<<16 | buffer[39]<<24;
    rootCluster = buffer[44] | buffer[45]<<8 | buffer[46]<<16 | buffer[47]<<24;
    rootAdr = (reservedSectors + fatTablesNumber * fatSize) * sectorSize;
    printf("--------------------------------------------------\n");
    printf("SECTOR SIZE:%d\nSECTORPERCLUSTER:%d\nRESERVEDSECTORS:%d\n",sectorSize,sectorPerCluster,reservedSectors);
    printf("FATNUMBER:%d\nFATSIZE:%d\nROOTCLUSTER:%d\nROOTADR:%d\n",fatTablesNumber,fatSize,rootCluster,rootAdr);
    printf("--------------------------------------------------\n");
}

int readFromFile(unsigned char *buffer, unsigned int *pcluster, int *poffset){
    unsigned int fatAdr  = reservedSectors * sectorSize;
    if (*poffset == sectorSize * sectorPerCluster){
        fseek(file, fatAdr + (*pcluster) * 4, SEEK_SET);
        fread(pcluster,1, 4, file);
        if (*pcluster >= 0x0FFFFFF8 && *pcluster <= 0x0FFFFFFF) return 0;
        fseek(file, rootAdr + (*pcluster - rootCluster) * sectorPerCluster * sectorSize, SEEK_SET);
        (*poffset) = 0;
    }
        fread(buffer, 1, 32, file);
        *poffset = *poffset + 32;
    return 1;
}

void getFileInfo(struct tfile* fs, int *pcluster, int *poffset, int count, int LFN){
    unsigned char buffer[32];
    if(LFN){
        while(count > 0){
            if(!readFromFile(buffer, pcluster, poffset)){
                printf("Error in getFileInfo!");
                exit(1);
            }
            fs->file_name[(count - 1)*13 + 0] = buffer[1];
            fs->file_name[(count - 1)*13 + 1] = buffer[3];
            fs->file_name[(count - 1)*13 + 2] = buffer[5];
            fs->file_name[(count - 1)*13 + 3] = buffer[7];
            fs->file_name[(count - 1)*13 + 4] = buffer[9];
            fs->file_name[(count - 1)*13 + 5] = buffer[14];
            fs->file_name[(count - 1)*13 + 6] = buffer[16];
            fs->file_name[(count - 1)*13 + 7] = buffer[18];
            fs->file_name[(count - 1)*13 + 8] = buffer[20];
            fs->file_name[(count - 1)*13 + 9] = buffer[22];
            fs->file_name[(count - 1)*13 + 10] = buffer[24];
            fs->file_name[(count - 1)*13 + 11] = buffer[28];
            fs->file_name[(count - 1)*13 + 12] = buffer[30];
            count--;     
        }   
    }

    if(!readFromFile(buffer, pcluster, poffset)){
            printf("Error in getFileInfo!");
            exit(1);
    }
    fs->size = buffer[28] | buffer[29]<<8 | buffer[30]<<16 | buffer[31]<<24;
    fs->first_cluster = buffer[26] | buffer[27] <<8 | buffer[20]<<16 | buffer[21]<<24;
    if(!LFN){
        fs->file_name[11] = 0x00;
        int i = 10;
        while(buffer[i] == 0x20) fs->file_name[i--] = 0x00;
        while(i >= 0) {fs->file_name[i] = buffer[i]; i--;}
        
    }
}

void search_file_in_directory(struct tfile* fs, int cluster, char* filename){
    unsigned int address = rootAdr + (cluster - rootCluster) * sectorPerCluster * sectorSize;
    unsigned char buffer[32];
    unsigned int offset = 0;
    fseek(file, address, SEEK_SET);
    while(readFromFile(buffer,&cluster,&offset)){
        if(buffer[0] == 0x00) break;
        if(buffer[0] != 0xE5){
            fseek(file, -32, SEEK_CUR); offset -= 32;
            int count = 0; int LFN = 0;
            if(buffer[11] == 0X0F) {LFN = 1; count = buffer[0] & 0X0F;} 
            getFileInfo(fs, &cluster, &offset, count, LFN);
            printf("=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=\n\n");
            printf("[+] File Name:%s\n",fs->file_name);
            printf("[+] File Size:%d\n",fs->size);
            printf("[+] File Cluster:%d\n",fs->first_cluster);
            printf("=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=\n\n");
            //if(strcmp(fs->file_name, filename) == 0) return;
        }
    };
}

void search_file_in_disk(){
    char* path[3];
    path[0] = "Folder1";
    path[1] = "Folder1.1";
    path[2] = "SecretFile";
    int j, cluster = 2;
    struct tfile fs;
    for (j = 0; j < 3; j++){
        search_file_in_directory(&fs, cluster, path[j]);
        cluster = fs.first_cluster;
    }
    printf("=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=\n");
    printf("[+] File Name:%s\n",fs.file_name);
    printf("[+] File Size:%d\n",fs.size);
    printf("[+] File Cluster:%d\n",fs.first_cluster);
    printf("=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=\n");

    unsigned int tmp_cluster = fs.first_cluster;
    while(tmp_cluster < 0x0FFFFFF8){
        printf("%d -- ",tmp_cluster);
        fseek(file, reservedSectors * sectorSize + tmp_cluster * 4, SEEK_SET);
        fread(&tmp_cluster, 1, 4, file);
    }
    printf("\n");

}
int main(){
    file = fopen(phy_disk, "rb");
    struct tfile fs;
    if (file == NULL){
        printf("Error while opening file!\n");
    }
    getParameters();

    search_file_in_directory(&fs, 3, "");
    //search_file_in_disk();
    fclose(file);

    return 0;
}