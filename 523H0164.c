#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
// rain la tra ve so nep moi hay so nep cu

const double PI = 3.1415926535;
FILE *fileInput;
FILE *fileOutput;


void invalidInput(const int n);
void checkInput(const int n,const int dc,const int dg,const int ld,const char w[]);
double soNep_BanhChung(const int dc);
double soNep_BanhGiay(const int dg);
void Wind(const int n,const int dc,const int dg,const int ld);
void Sun(const int n,const int dc,const int dg,const int ld);
void Fog(const int n,int dc,int dg,const int ld);
void Cloud(const int n,const int dc,const int dg,const int ld);
void Rain(const int n,const int dc,const int dg,const int ld);
int calculate_Banh_Chung(double *n, int dc,int dg, int *ld,int *check);
int calculate_Banh_Giay_Cloud(double *n, int dc,int dg, int *ld,int *check);
int calculate_Banh_Giay(double *n, int dc,int dg, int *ld);
int calculate_Banh_Chung_Cloud(double *n, int dc,int dg, int *ld);
int calculate_Banh_Chung_Rain(double *n, int dc,int dg, int *ld);
int calculate_Banh_Giay_Rain(double *n, int dc,int dg, int *ld);
int CheckFibonacci(int x);
int CheckSoBanBe(const int x,const int y);
int check_chon_banh_chung(int n,int dc,int dg,int ld);
int check_chon_banh_giay(int n,int dc,int dg,int ld);
int check_so_la_dong_Rain(const int dc,const int dg, int BanhChung, int BanhGiay,int ld_con_lai);


int main(){
    fileInput = fopen("input.inp", "r");
    fileOutput = fopen("output.out", "w");
    if (fileInput == NULL || fileOutput == NULL) {
        return 1;
    }

    int n,dc,dg,ld;
    char w[10];
    int check  = fscanf(fileInput,"%d %d %d %d %s",&n,&dc,&dg,&ld,w);
    if (check == 5){
        checkInput(n,dc,dg,ld,w); 
    }
    else{
        invalidInput(n); 
        fclose(fileInput);   
        fclose(fileOutput);
        return 0;
    }
    fclose(fileInput);
    fclose(fileOutput);
    return 0;
}


void checkInput(const int n,const int dc,const int dg,const int ld,const char w[]){
    if (1 > n || n> 2000)
    {
        invalidInput(n);
        return;
    }
    if (ld > 600 || ld < 1)
    {
        invalidInput(n);
        return;
    }
    if (dc == 0 && dg ==0)
    {
        invalidInput(n);
        return;
    }
    if (dc < 0 || dg < 0 )
    {
        invalidInput(n);
        return;
    }
    
    

    if (strcmp(w,"Rain") == 0){
        Rain(n,dc,dg,ld);
    }  
    else if (strcmp(w,"Wind") == 0){
        Wind(n,dc,dg,ld);
    }
    else if (strcmp(w,"Sun") == 0){
        Sun(n,dc,dg,ld);
    }
    else if (strcmp(w,"Fog") == 0){
        Fog(n,dc,dg,ld);
    }
    else if (strcmp(w,"Cloud") == 0){
        Cloud(n,dc,dg,ld);
    }
    else{
        invalidInput(n);
        return;
    }
    
    
}


double soNep_BanhChung(const int dc){
    return pow(dc,2)*sqrt(dc);
}
double soNep_BanhGiay(const int dg){    
    return (pow(dg,2)*PI)/3;
}


void Wind(const int n,const int dc,const int dg,const int ld){
    
    int ld_con_lai = ld;
    double so_nep_banh_chung = soNep_BanhChung(dc);
    double so_nep_banh_Giay = soNep_BanhGiay(dg);
    double so_Nep_Du = n;
    int check = 0;

    int so_Banh_Chung = calculate_Banh_Chung(&so_Nep_Du,dc,dg,&ld_con_lai,&check);
    int so_Banh_Giay = calculate_Banh_Giay(&so_Nep_Du,dc,dg,&ld_con_lai);
    if (so_Banh_Chung == -2)
    {
        double Nep_Du_Moi = n;
        int ld_con_lai_moi = ld;

        double temp_Nep_Du_1 = n;
        int temp_ld_con_lai_1 = ld;
        so_Banh_Giay = calculate_Banh_Giay(&temp_Nep_Du_1,dc,dg,&temp_ld_con_lai_1);
        so_Banh_Chung = calculate_Banh_Chung(&temp_Nep_Du_1,dc,dg,&temp_ld_con_lai_1,&check);

        double temp_Nep_Du_2 = n;
        int temp_ld_con_lai_2 = ld;
        so_Banh_Chung = calculate_Banh_Chung(&temp_Nep_Du_2,dc,dg,&temp_ld_con_lai_2,&check);
        so_Banh_Giay = calculate_Banh_Giay(&temp_Nep_Du_2,dc,dg,&temp_ld_con_lai_2);

        if ((temp_Nep_Du_1>temp_ld_con_lai_2))
        {
            so_Banh_Chung = calculate_Banh_Chung(&Nep_Du_Moi,dc,dg,&ld_con_lai_moi,&check);
            so_Banh_Giay = calculate_Banh_Giay(&Nep_Du_Moi,dc,dg,&ld_con_lai_moi);
        }
        else{
            so_Banh_Giay = calculate_Banh_Giay(&Nep_Du_Moi,dc,dg,&ld_con_lai_moi);
            so_Banh_Chung = calculate_Banh_Chung(&Nep_Du_Moi,dc,dg,&ld_con_lai_moi,&check);
            
        }
        
        so_Nep_Du = Nep_Du_Moi;
    }

    fprintf(fileOutput,"%d %d %.3lf",so_Banh_Chung,so_Banh_Giay,so_Nep_Du);
}
int calculate_Banh_Chung(double *n, int dc,int dg, int *ld,int *check){
    if (dc <= 0 || *ld == 0)
    {
        return 0;
    }
    
    int La_Dong = *ld;
    double Nep_Du = *n;
    int BanhChung = Nep_Du/soNep_BanhChung(dc);
    *n = fmod(Nep_Du,soNep_BanhChung(dc));

    if (dc < 8)
    {
        if (BanhChung > La_Dong)
        {
            if (dg > dc && *check == 0)
            {
                (*check)++;
                return -2;
            }
            
            *n = (BanhChung - La_Dong)*soNep_BanhChung(dc) + *n;
            BanhChung = La_Dong;
            *ld = 0;
        }
        else
        {
            *ld = *ld - BanhChung;
        }
        return BanhChung;
    }
    else
    {
        if (BanhChung*2 > La_Dong)
        {
            if (dg > dc && *check == 0)
            {
                (*check)++;
                return -2;
            }
            
            *n = (BanhChung - La_Dong/2)*soNep_BanhChung(dc) + *n;
            BanhChung = (La_Dong)/2;
            *ld = *ld - BanhChung*2;
        }
        else
        {
            *ld = *ld - BanhChung*2;
        }
        return BanhChung;
    }
}
int calculate_Banh_Giay(double *n, int dc,int dg, int *ld){
    if (dg <= 0 || *ld == 0)
    {
        return 0;
    }
    
    int La_Dong = *ld;
    double Nep_Du = *n;
    int BanhGiay = Nep_Du/soNep_BanhGiay(dg);
    *n = fmod(Nep_Du,soNep_BanhGiay(dg));

    if (dg < 5)
    {
        if (BanhGiay > La_Dong)
        {
            *n = (BanhGiay - La_Dong)*soNep_BanhGiay(dg) + *n;
            BanhGiay = La_Dong;
            *ld = 0;
        }
        else
        {
            *ld = *ld - BanhGiay;
        }
        return BanhGiay;
    }
    else
    {
        if (BanhGiay*2 > La_Dong)
        {
            *n = (BanhGiay - La_Dong/2)*soNep_BanhGiay(dg) + *n;
            BanhGiay = (La_Dong)/2;
            *ld = *ld - BanhGiay*2;
        }
        else
        {
            *ld = *ld - BanhGiay*2;
        }
        return BanhGiay;
    }
}


void Rain(const int n,const int dc,const int dg,const int ld){ // chua xong 
    int ld_con_lai = ld;
    double so_nep_banh_chung = soNep_BanhChung(dc);
    double so_nep_banh_Giay = soNep_BanhGiay(dg);
    double so_Nep_Du = n;
    double n1, n2;
    double temp = so_nep_banh_chung/so_nep_banh_Giay + 1;
    n2 = (double)n/temp;
    n1 =  n - n2;


    int so_Banh_Chung = n1/so_nep_banh_chung;
    int so_Banh_Giay = n2/so_nep_banh_Giay;
    int ld_can_dung_CB = check_so_la_dong_Rain(dc,dg,so_Banh_Chung,so_Banh_Giay,ld_con_lai);
    if(ld_can_dung_CB == -2){
         
        if (check_chon_banh_chung(n,dc,dg,ld) > check_chon_banh_giay(n,dc,dg,ld))
        {
            so_Banh_Giay = calculate_Banh_Giay_Rain(&so_Nep_Du,dc,dg,&ld_con_lai);
            so_Banh_Chung = calculate_Banh_Chung_Rain(&so_Nep_Du,dc,dg,&ld_con_lai);
        }
        else
        {
            so_Banh_Chung = calculate_Banh_Chung_Rain(&so_Nep_Du,dc,dg,&ld_con_lai);
            so_Banh_Giay = calculate_Banh_Giay_Rain(&so_Nep_Du,dc,dg,&ld_con_lai);
        }
        
    }
    else{
        so_Nep_Du = fmod(n1,so_nep_banh_chung) + fmod(n2,so_nep_banh_Giay);
        double temp_Nep_Du_1 = so_Nep_Du;
        double temp_Nep_Du_2 = so_Nep_Du;
        int temp_ld_con_lai_1 = ld - ld_can_dung_CB;
        int temp_ld_con_lai_2 = ld - ld_can_dung_CB;

        int BanhChung_Them_1 = calculate_Banh_Chung_Rain(&temp_Nep_Du_1,dc,dg,&temp_ld_con_lai_1);
        int BanhGiay_Them_1 = calculate_Banh_Giay_Rain(&temp_Nep_Du_1,dc,dg,&temp_ld_con_lai_1);
        int BanhChung_Them_2 = calculate_Banh_Chung_Rain(&temp_Nep_Du_2,dc,dg,&temp_ld_con_lai_2);
        int BanhGiay_Them_2 = calculate_Banh_Giay_Rain(&temp_Nep_Du_2,dc,dg,&temp_ld_con_lai_2);

        int temp_Banh_Chung_1 = so_Banh_Chung + BanhChung_Them_1;
        int temp_Banh_Giay_1 = so_Banh_Giay + BanhGiay_Them_1;
        int temp_Banh_Chung_2 = so_Banh_Chung + BanhChung_Them_2;
        int temp_Banh_Giay_2 = so_Banh_Giay + BanhGiay_Them_2;
        int th1 = abs(temp_Banh_Chung_1 - temp_Banh_Giay_1);
        int th2 = abs(temp_Banh_Chung_2 - temp_Banh_Giay_2);

        if ( th1 < th2 )
        {
            so_Banh_Chung = temp_Banh_Chung_1;
            so_Banh_Giay = temp_Banh_Giay_1;
            so_Nep_Du = temp_Nep_Du_1;
        }
        else{
            so_Banh_Chung = temp_Banh_Chung_2;
            so_Banh_Giay = temp_Banh_Giay_2;
            so_Nep_Du = temp_Nep_Du_2;
        }
        
    }


    fprintf(fileOutput,"%d %d %.3lf",so_Banh_Chung,so_Banh_Giay,so_Nep_Du);
}
int check_so_la_dong_Rain(const int dc,const int dg, int BanhChung, int BanhGiay,int ld_con_lai){
    int ld_BanhChung = BanhChung;
    int ld_BanhGiay = BanhGiay;
    if (dc >= 8)
    {
        ld_BanhChung = ld_BanhChung*2;
    }
    if (dg >= 5)
    {
        ld_BanhGiay = ld_BanhGiay*2;
    }
    int ld_CanDung = ld_BanhChung + ld_BanhGiay;

    if (ld_CanDung > ld_con_lai)
    {
        return -2;
    }
    else{
        return ld_CanDung;
    }
}
int check_chon_banh_chung(int n,int dc,int dg,int ld){
    double Nep_Du = n;
    int ld_con_lai = ld;
    int so_Banh_Chung = calculate_Banh_Chung_Rain(&Nep_Du,dc,dg,&ld_con_lai);
    int so_Banh_Giay = calculate_Banh_Giay_Rain(&Nep_Du,dc,dg,&ld_con_lai);
    return Nep_Du;
}
int check_chon_banh_giay(int n,int dc,int dg,int ld){
    double Nep_Du = n;
    int ld_con_lai = ld;
    int so_Banh_Giay = calculate_Banh_Giay_Rain(&Nep_Du,dc,dg,&ld_con_lai);
    int so_Banh_Chung = calculate_Banh_Chung_Rain(&Nep_Du,dc,dg,&ld_con_lai);
    return Nep_Du;
}
int calculate_Banh_Chung_Rain(double *n, int dc,int dg, int *ld){
    if (dc <= 0)
    {
        return 0;
    }
    
    int La_Dong = *ld;
    double Nep_Du = *n;
    int BanhChung = Nep_Du/soNep_BanhChung(dc);
    *n = fmod(Nep_Du,soNep_BanhChung(dc));

    if (dc < 8)
    {
        if (BanhChung > La_Dong)
        {
            
            *n = (BanhChung - La_Dong)*soNep_BanhChung(dc) + *n;
            BanhChung = La_Dong;
            *ld = 0;
        }
        else
        {
            *ld = *ld - BanhChung;
        }
        return BanhChung;
    }
    else
    {
        if (BanhChung*2 > La_Dong)
        {
            
            *n = (BanhChung - La_Dong/2)*soNep_BanhChung(dc) + *n;
            BanhChung = (La_Dong)/2;
            *ld = *ld - BanhChung*2;
        }
        else
        {
            *ld = *ld - BanhChung*2;
        }
        return BanhChung;
    }
}
int calculate_Banh_Giay_Rain(double *n, int dc,int dg, int *ld){
    if (dg <= 0 || *ld == 0)
    {
        return 0;
    }
    
    int La_Dong = *ld;
    double Nep_Du = *n;
    int BanhGiay = Nep_Du/soNep_BanhGiay(dg);
    *n = fmod(Nep_Du,soNep_BanhGiay(dg));

    if (dg < 5)
    {
        if (BanhGiay > La_Dong)
        {
            *n = (BanhGiay - La_Dong)*soNep_BanhGiay(dg) + *n;
            BanhGiay = La_Dong;
            *ld = 0;
        }
        else
        {
            *ld = *ld - BanhGiay;
        }
        return BanhGiay;
    }
    else
    {
        if (BanhGiay*2 > La_Dong)
        {
            *n = (BanhGiay - La_Dong/2)*soNep_BanhGiay(dg) + *n;
            BanhGiay = (La_Dong)/2;
            *ld = *ld - BanhGiay*2;
        }
        else
        {
            *ld = *ld - BanhGiay*2;
        }
        return BanhGiay;
    }
}


void Sun(const int n,const int dc,const int dg,const int ld){
    const int X[5][6] ={{5,7,10,12,15,20},
                        {20,5,7,10,12,15},
                        {15,20,5,7,10,12},
                        {12,15,20,5,7,10},
                        {10,12,15,20,5,7}
    };

    int ld_con_lai = ld;
    double so_nep_banh_chung = soNep_BanhChung(dc);
    double so_nep_banh_Giay = soNep_BanhGiay(dg);
    double so_Nep_Du = n;

    int G = dc%6;
    int H = ld_con_lai%5;

    so_Nep_Du = so_Nep_Du + so_Nep_Du*0.01*X[H][G];
    ld_con_lai = ld_con_lai - X[H][G];

    if(so_Nep_Du <= 0 || ld_con_lai <= 0){
        invalidInput(n);
        return ;
    }
    
    if ((dc + dg)%3 == 0)
    {
        Rain(so_Nep_Du,dc,dg,ld_con_lai);
    }
    else if ((dc + dg)%3 == 1)
    {
        Wind(so_Nep_Du,dc,dg,ld_con_lai);
    }
    else if((dc + dg)%3 == 2)
    {
        Cloud(so_Nep_Du,dc,dg,ld_con_lai);
    }
}


void Fog(const int n, int dc, int dg,const int ld){
    int ld_con_lai = ld;
    double so_nep_banh_chung = soNep_BanhChung(dc);
    double so_nep_banh_Giay = soNep_BanhGiay(dg);
    double so_Nep_Du = n;
    if(CheckFibonacci(dc) == 1 && CheckFibonacci(dg) == 1)
    {
        dc = dc/2;
        dg = dg/2;  
    }
    else
    {   
        dc = dc*2;
        dg = dg*2;
    }

    if(dc == 0 && dg == 0){
        invalidInput(n);
        return;
    }


    double tempNepDu = n;
    int check = 1;
    int tempLd = ld;
    int so_Banh_Chung = calculate_Banh_Chung(&tempNepDu,dc,dg,&tempLd,&check);
    tempNepDu = n;
    tempLd = ld;
    int so_Banh_Giay = calculate_Banh_Giay(&tempNepDu,dc,dg,&tempLd);


    if (so_Banh_Giay < so_Banh_Chung)
    {
        so_Banh_Giay = calculate_Banh_Giay(&so_Nep_Du,dc,dg,&ld_con_lai);
        so_Banh_Chung = calculate_Banh_Chung(&so_Nep_Du,dc,dg,&ld_con_lai,&check);
    }
    else
    {
        so_Banh_Chung = calculate_Banh_Chung(&so_Nep_Du,dc,dg,&ld_con_lai,&check);
        so_Banh_Giay = calculate_Banh_Giay(&so_Nep_Du,dc,dg,&ld_con_lai);
    }
    
    fprintf(fileOutput,"%d %d %.3lf",so_Banh_Chung,so_Banh_Giay,so_Nep_Du);
}

int CheckFibonacci(int x)
{
    int n1 = 0;
    int n2 = 1;
    int n3 = 0;
    if (x == 0 || x == 1)
    {
        return 1;
    }
    for(;;) {
        n3 = n1 + n2;
        n1 = n2;
        n2 = n3;
        if (n3 == x)
        {
            return 1;
        }
        else if (n3 >= x) 
        {
            return 0;
        }
    }
}



void Cloud(const int n,const int dc,const int dg,const int ld){
    int ld_con_lai = ld;
    double so_nep_banh_chung = soNep_BanhChung(dc);
    double so_nep_banh_Giay = soNep_BanhGiay(dg);
    double so_Nep_Du = n;

    if (CheckSoBanBe(n,ld) == 1)
    {
        fprintf(fileOutput,"%d %d %.3lf",0,0,so_Nep_Du);
        return;
    }
    else
    {
        int check = 0;
        int so_Banh_Giay = calculate_Banh_Giay_Cloud(&so_Nep_Du,dc,dg,&ld_con_lai,&check);
        int so_Banh_Chung = calculate_Banh_Chung_Cloud(&so_Nep_Du,dc,dg,&ld_con_lai);
        if (so_Banh_Giay == -2)
        {
            double Nep_Du_Moi = n;
            int ld_con_lai_moi = ld;

            so_Banh_Chung = calculate_Banh_Chung_Cloud(&Nep_Du_Moi,dc,dg,&ld_con_lai_moi);
            so_Banh_Giay = calculate_Banh_Giay_Cloud(&Nep_Du_Moi,dc,dg,&ld_con_lai_moi,&check);
            so_Nep_Du = Nep_Du_Moi;
        }
        fprintf(fileOutput,"%d %d %.3lf",so_Banh_Chung,so_Banh_Giay,so_Nep_Du);
    }
}
int CheckSoBanBe(const int x,const int y){
    int sum_x = 0, sum_y = 0;
    for (size_t i = 1; i < x; i++)
    {
        if (x % i == 0)
        {
            sum_x = sum_x + i;  
        }
    }
    if (sum_x == y)
    {
        for (size_t i = 1; i < y; i++)
        {
            if (y % i == 0)
            {
                sum_y = sum_y + i;
            }
        }
        if (sum_y == x)
        {
            return 1;
        }
    }
    else{
        return 0;
    }
}
int calculate_Banh_Giay_Cloud(double *n, int dc,int dg, int *ld,int *check){
    if (dg <= 0 || *ld == 0)
    {
        return 0;
    }
    
    int La_Dong = *ld;
    double Nep_Du = *n;
    int BanhGiay = Nep_Du/soNep_BanhGiay(dg);
    *n = fmod(Nep_Du,soNep_BanhGiay(dg));
    if (dg < 5)
    {
        if (BanhGiay > La_Dong)
        {
            if (dc > dg && *check == 0)
            {
                (*check)++;
                return -2;
            }
            
            *n = (BanhGiay - La_Dong)*soNep_BanhGiay(dg) + *n;
            BanhGiay = La_Dong;
            *ld = 0;
        }
        else
        {
            *ld = *ld - BanhGiay;
        }
        return BanhGiay;
    }
    else
    {
        if (BanhGiay*2 > La_Dong)
        {
            if (dc > dg && *check == 0)
            {
                (*check)++;
                return -2;
            }
            *n = (BanhGiay - La_Dong/2)*soNep_BanhGiay(dg) + *n;
            BanhGiay = (La_Dong)/2;
            *ld = *ld - BanhGiay*2;
        }
        else
        {
            *ld = *ld - BanhGiay*2;
        }
        return BanhGiay;
    }
}
int calculate_Banh_Chung_Cloud(double *n, int dc,int dg, int *ld){
    if (dc <= 0 || *ld == 0)
    {
        return 0;
    }
    
    int La_Dong = *ld;
    double Nep_Du = *n;
    int BanhChung = Nep_Du/soNep_BanhChung(dc);
    *n = fmod(Nep_Du,soNep_BanhChung(dc));

    if (dc < 8)
    {
        if (BanhChung > La_Dong)
        {
            *n = (BanhChung - La_Dong)*soNep_BanhChung(dc) + *n;
            BanhChung = La_Dong;
            *ld = 0;
        }
        else
        {
            *ld = *ld - BanhChung;
        }
        return BanhChung;
    }
    else
    {
        if (BanhChung*2 > La_Dong)
        {
            *n = (BanhChung - La_Dong/2)*soNep_BanhChung(dc) + *n;
            BanhChung = (La_Dong)/2;
            *ld = *ld - BanhChung*2;
        }
        else
        {
            *ld = *ld - BanhChung*2;
        }
        return BanhChung;
    }
}


void invalidInput(int n){
    fprintf(fileOutput,"-1 -1 %d",n);
    return;
}
