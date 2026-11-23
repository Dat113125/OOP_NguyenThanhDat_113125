#include<iostream>
#include<string>
#include<iomanip>
#include<sstream>
#include<cctype>

using namespace std;

class SinhVien{
	private:
		string Hoten;
		int maSV;
		string ngaySinh;
		string Lop;
		double diem;
	public:
		SinhVien();
		SinhVien(string Hoten, int maSV, string ngaySinh, string Lop, double diem);
		string layHoten();
		int layMasv();
		string layNgaysinh();
		string layLop();
		double layDiem();
		void nhap();
		void hienthi();
};

SinhVien::SinhVien(){
	Hoten = "";
	maSV = 0;
	ngaySinh = "";
	Lop = "";
}

SinhVien::SinhVien(string ht, int ma, string ngay, string lp, double d){
	Hoten = ht;
	maSV = ma;
	ngaySinh = ngay;
	Lop = lp;
	diem = d;
}

string SinhVien::layHoten(){
	return Hoten;
}

int SinhVien::layMasv(){
	return maSV;
}

string SinhVien::layNgaysinh(){
	return ngaySinh;
}

string SinhVien::layLop(){
	return Lop;
}

double SinhVien::layDiem(){
	return diem;
}

void SinhVien::nhap(){
	cout<<"Nhap ho ten: "; cin.ignore(); getline(cin, Hoten);
	cout<<"Nhap ma sinh vien"; cin>>maSV;
	cout<<"Nhap ngay sinh: "; cin.ignore(); getline(cin, ngaySinh);
	cout<<"Nhap lop: "; getline(cin, Lop);
	cout<<"Nhap diem: "; cin>>diem;
}

void SinhVien::hienthi(){
	cout<<"Ho ten: "<<Hoten<<endl;
	cout<<"Ma sinh vien: "<<maSV<<endl;
	cout<<"Ngay sinh: "<<ngaySinh<<endl;
	cout<<"Lop: "<<Lop<<endl;
	cout<<"Diem: "<<diem<<endl;
}

class HocPhan{
	private:
		string tenHP;
		string nhomHP;
		int sotin;
	public:
		HocPhan();
		HocPhan(string tenHP, string nhomHP, int soTin);
		string layTenHP();
		string layNhomHP();
		int laysoTin();
		void hienthi();	
};

HocPhan::HocPhan(){
	tenHP = "";
	nhomHP = "";
	sotin = 0;
}

HocPhan::HocPhan(string ten, string nhom, int tin){
	tenHP = ten;
	nhomHP = nhom;
	sotin = tin;
}

string HocPhan::layTenHP(){
	return tenHP;
}

string HocPhan::layNhomHP(){
	return nhomHP;
}

int HocPhan::laysoTin(){
	return sotin;
}

void HocPhan::hienthi(){
	cout<<"Ten hoc phan: "<<tenHP<<endl;
	cout<<"NHom hoc phan: "<<nhomHP<<endl;
	cout<<"So tin chi: "<<sotin<<endl;
}

class LichThi{
	private:
		HocPhan hp;
		static int sbd;
		SinhVien *sv;
		int soLuong;
	public:
		LichThi();
		LichThi(HocPhan hp, int soLuong, SinhVien *sv);
		int laysoLuong();
		void hienthi();
		void runmenu();
};

int LichThi::sbd = 0;

LichThi::LichThi(){
	soLuong = 0;
}

LichThi::LichThi(HocPhan hp, int soLuong, SinhVien *sv){
	soLuong = soLuong;
}

int LichThi::laysoLuong(){
	return soLuong;
}

void LichThi::hienthi(){
	cout<<"So bao danh: "<<sbd<<endl;
}

void LichThi::runmenu(){
	int chon, kt;
	do{
		cout<<"1. Khoi tao lich thi"<<endl;
		cout<<"2. Thoat"<<endl;
		cout<<"Moi ban nhap lua chon: ";
		cin>>chon;
		
		switch(chon){
			case 1:
				{
					string ten, ngay, lop, tenhp, nhom;
					int ma, sotin, sl;
					double diem;
					
					cout<<"Moi ban nhap ten hoc phan: "; cin.ignore(); getline(cin, tenhp);
					cout<<"Moi ban nhap nhom hoc phan: "; getline(cin, nhom);
					cout<<"Moi ban nhap so tin chi: "; cin>>sotin;
					HocPhan hp = HocPhan(tenhp,nhom, sotin);
					
					cout<<"Moi ban nhap so luong sinh vien: "; cin>>sl;
					
					SinhVien *sv = new SinhVien[sl];
					for(int i = 0; i<sl; i++){
						cout<<"Sinh vien thu "<<i+1<<":"<<"\n";
						sv[i].nhap();
						sbd++;
					}
					
					LichThi lt = LichThi(hp,sl,sv);
					hp.hienthi();
					sv->hienthi();
					lt.hienthi();
				}
				break;
			case 2:
				{
					cout<<"Dang thoat chuong trinh..."<<endl;
					kt++;
				}
				break;
		}
	}while(kt==0);
}

int main(){
	LichThi lt;
	lt.runmenu();
	return 0;
}
