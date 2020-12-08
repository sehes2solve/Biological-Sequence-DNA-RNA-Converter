#include "CodonsTable.h"
#include <bits/stdc++.h>
using namespace std;

CodonsTable::CodonsTable(string codonsFileName)
{
    LoadCodonsFromFile(codonsFileName);
}
void CodonsTable::LoadCodonsFromFile(string codonsFileName)
{
    ifstream codons_data;
	codons_data.open(codonsFileName);
	if(codons_data.fail() == true)
        throw "File Not Found!!";
    else
    {
        int i = 0;
        string reader;
        bool Is_stop_codon = false;
        while(codons_data >> reader)
        {
            if(codons_data.fail() == true)
                throw "Stream corrupted!!";
            if(i == 64)
                break;
            if(i % 2 == 0)
            {
                strcpy(codons[i/2].value,reader.c_str());
                if(reader == "UAA" || reader == "UAG" || reader == "UGA")
                    Is_stop_codon = true;
            }
            else
            {
                if(Is_stop_codon)
                {
                    codons[i/2].AminoAcid = '*';
                    i++;
                    strcpy(codons[i/2].value,reader.c_str());
                    Is_stop_codon = false;
                }
                else
                codons[i/2].AminoAcid = reader[0];
            }
            i++;
        }
        if(i < 64)
            throw "File Data Not Enough !!";
    }
    codons_data.close();

}
Codon CodonsTable::getAminoAcid(char * value)
{
    for(int i = 0 ;i < 64; i++)
    {
		bool x = true;
		for (int j = 0; j < 3; j++)
		{

			if (codons[i].value[j] != value[j])
				x = false;
			if (!x)
				break;
		}
		if (x)
			return codons[i];
    }
    throw "Amino acid Not found!!!";
    return codons[0];

}
void CodonsTable::setCodon(char * value, char AminoAcid, int index)
{
    codons[index].AminoAcid = AminoAcid;
    strcpy(codons[index].value,value);
}
CodonsTable::~CodonsTable()
{
    //dtor
}
