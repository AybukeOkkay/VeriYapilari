#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class DinamikDizi {
public :
	DinamikDizi() {
		m_boyut = 5;
		m_adres = new int[m_boyut];
		m_kullanilan = 0;
	}
	~DinamikDizi() {
		delete[] m_adres;
	}
	int getir(int sira) const {

		if (sira<0||sira>=m_kullanilan)
		{
			throw exception("getir sinir problemi"); //istisna yapmak için kullanılanır
		}
		return m_adres[sira];
	}
	int boyut()const {
		return m_boyut;
	}
	int kullanilan()const {
		return m_kullanilan;
	}
	void cikar(int sira)
	{
		if (sira >= 0 &&
			m_kullanilan > 0 &&
			sira < m_kullanilan)
		{
			for (int i = sira; i < m_kullanilan-1; i++)
			{
				m_adres[i] = m_adres[i + 1];
				m_kullanilan--;
			}
		}
		else
		{
			throw exception("cikar():sira hatasi");
		}
	}
	void sonaEkle(int yeniSayi)
	{
		arayaEkle(m_kullanilan, yeniSayi);
	}
	void genislet(int ekBoyut)
	{
		int * yeniAdres=new int[m_boyut + ekBoyut];
		for (int i = 0; i < m_kullanilan; i++)
			yeniAdres[i] = m_adres[i];

		delete[] m_adres;

		m_adres = yeniAdres;

		m_boyut += ekBoyut;
	}
	void arayaEkle(int sira, int veri)
	{
		if (sira >= 0 && sira <= m_kullanilan)
		{
			if (m_kullanilan >= m_boyut)
				genislet(m_boyut);

			for (int i = m_kullanilan-1; i >=sira ; i--)
				m_adres[i + 1] = m_adres[i]; 

			m_adres[sira] = veri;
			m_kullanilan++;
		}
		else
		{
			throw exception("sira hatasi");
		}
	}

	friend ostream& operator<<(ostream& os, const DinamikDizi& dizi)//friend İşlev, bir sınıfın üyesi olmayan ancak sınıfın özel ve korumalı üyelerine erişimi olan bir işlevdir.
	{
		os << "|";
		for (int i = 0; i < dizi.boyut(); i++)
			os << setw(3) << i << setw(1) << "|";
		os << endl << "|";

		for (int i = 0; i < dizi.boyut(); i++)
			os << setw(3) << "---" << setw(1) << "|"; //setw -> yazilan veya okunan bloklarin boylarini sabitlemeye yarar
		os << endl << "|";
		for (int i = 0; i < dizi.kullanilan(); i++)
		{
			os << setw(3) << dizi.getir(i) << setw(1) << "|";
		}
		for (int i = dizi.kullanilan(); i < dizi.boyut(); i++)
		{
			os << setw(3) << "bos" << setw(1) << "|";
		}
		os << endl << endl;
		return os;
	}
private:
	int m_boyut;
	int m_kullanilan;
	int* m_adres;
};
int main()
{
	DinamikDizi dizi;
	while (true)
	{
		system("cls");
		cout << dizi;

		cout << "1..sona ekle" << endl;
		cout << "2..araya ekle" << endl;
		cout << "3..cikar" << endl;
		cout << "4..cikis" << endl;
		int secim;
		cin >> secim;
		if (secim == 1)
		{
			dizi.sonaEkle(rand() % 100);
		}
		else if (secim == 2)
		{
			int sira;
			cout << "sira: ";
			cin >> sira;
			dizi.arayaEkle(sira, rand() % 100);
		}
		else  if (secim==3)
		{
			int sira;
			cout << "sira: ";
			cin >> sira;
			dizi.cikar(sira);
			
		}
		else if (secim == 4)
		{
			break;
		}
	}
}
