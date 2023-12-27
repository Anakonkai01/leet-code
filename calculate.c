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