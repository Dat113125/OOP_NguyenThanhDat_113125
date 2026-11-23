#include<iostream>
#include<string>
#include<iomanip>
#include<sstream>
#include<cctype>

using namespace std;

class Khachhang{
	private:
		string Hoten;
		string soDt;
		string Diachi;
	public:
		Khachhang();
		Khachhang(string Hoten, string soDt, string Diachi);
		string layHoten() const;
		string laysoDt() const;
		string layDiachi() const;
		void hienthi() const;
};

Khachhang::Khachhang(){
	Hoten = "";
	soDt = "";
	Diachi = "";
}

Khachhang::Khachhang(string Ten, string Dt, string diachi){
	Hoten = Ten;
	soDt = Dt;
	Diachi = diachi;
}

string Khachhang::layHoten() const{
	return Hoten;
}

string Khachhang::laysoDt() const{
	return soDt;
}

string Khachhang::layDiachi() const{
	return Diachi;
}

void Khachhang::hienthi() const{
	cout<<"Ho ten khach hang: "<<Hoten<<endl;
	cout<<"DT: "<<soDt<<endl;
	cout<<"Dia chi: "<<Diachi<<endl;
}

class Sanpham{
	private:
		string Tensp;
		string Donvitinh;
		double Dongia;
	public:
		Sanpham();
		Sanpham(string Tensp, string Donvitinh, double Dongia);
		string layTensp() const;
		string layDonvitinh() const;
		double layDongia() const;
		void nhap();
		void Hienthi() const;
};

Sanpham::Sanpham(){
	Tensp = "";
	Donvitinh = "";
	Dongia = 0;
}

Sanpham::Sanpham(string Ten, string Donvi, double dongia){
	Tensp = Ten;
	Donvitinh = Donvi;
	Dongia = dongia;
}

string Sanpham::layTensp() const{
	return Tensp;
}

string Sanpham::layDonvitinh() const{
	return Donvitinh;
}

double Sanpham::layDongia() const{
	return Dongia;
}

void Sanpham::nhap(){
	cout<<"Nhap ten sp: "; cin.ignore(); getline(cin, Tensp);
	cout<<"Nhap don vi tinh: "; getline(cin, Donvitinh);
	cout<<"Nhap don gia: "; cin>>Dongia;
}

void Sanpham::Hienthi() const{
	cout<<"Ten hang hoa va quy cach san pham: "<<Tensp<<endl;
	cout<<"Don vi tinh: "<<Donvitinh<<endl;
	cout<<"Don gia: "<<Dongia<<endl;
}

class Hoadon{
	private:
		Khachhang kh;
		static int smh;
		Sanpham *a;
		string maSo;
		int Soluong;
	public:
		Hoadon();
		Hoadon(Khachhang kh, Sanpham *a, string maSo, int Soluong);
		int laySmh() const;
		string layMaso() const;
		int laySoluong() const;
		double Thanhtien(int Soluong, Sanpham *a) const;
		void Hienthihoadon();
		void runmenu();
};

int Hoadon::smh = 0;

Hoadon::Hoadon(){
	maSo = "";
	Soluong = 0;
}

Hoadon::Hoadon(Khachhang kh, Sanpham *a, string ms, int sl){
	maSo = ms;
	Soluong = sl;
}

int Hoadon::laySmh() const{
	return smh;
}

string Hoadon::layMaso() const{
	return maSo;
}

int Hoadon::laySoluong() const{
	return Soluong;
}

double Hoadon::Thanhtien(int Soluong, Sanpham *a) const{
	return Soluong * (a->layDongia());
}

void Hoadon::Hienthihoadon(){
	cout<<"Ma so: "<<maSo<<endl;
	cout<<"So mat hang: "<<smh<<endl;
	cout<<"So luong: "<<Soluong<<endl;
	cout<<"Thanh tien: "<<Thanhtien(Soluong, a)<<endl;
}

void Hoadon::runmenu(){
	int chon, kt;
	do{
		cout<<"1. Khoi tao hoa don"<<endl;
		cout<<"2. Thoat"<<endl;
		cout<<"Moi ban nhap lua chon: ";
		cin>>chon;
		
		switch(chon){
			case 1:
				{
					string ten, dt, dc, ms;
					int sl;
					cin.ignore();
					cout<<"Moi nhap ten khach hang: "; getline(cin, ten);
					cout<<"Moi nhap so dien thoai: "; getline(cin, dt);
					cout<<"Moi ban nhap dia chi: "; getline(cin, dc);
					Khachhang kh = Khachhang(ten,dt,dc);
					
					cout<<"Moi ban nhap ma so hoa don: "; cin.ignore(); getline(cin, ms);
					cout<<"Moi ban nhap so luong san pham: "; cin>>sl;
					
					Sanpham *sp = new Sanpham[sl];
					
					for(int i = 0; i<sl; i++){
						cout<<"San pham thu "<<i+1<<":"<<"\n";
						sp[i].nhap();
						smh++;
					}
					
					Hoadon hd = Hoadon(kh, sp, ms, sl);
					
					cout<<"Hoa don cua ban"<<endl;
					kh.hienthi();
					sp->Hienthi();
					hd.Hienthihoadon();
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
	Hoadon hd;
	hd.runmenu();
	return 0;
}
