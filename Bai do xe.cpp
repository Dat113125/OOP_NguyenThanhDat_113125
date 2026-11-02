#include<iostream>
#include<string>

using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien(){
	ma_xe = 0;
	loai_xe = "";
	gio_vao = 0;
	tg_do = 0;
}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg) const{
	ma_xe = ma;
	loai_xe = loai;
	gio_vao = gio;
	tg_do = tg;
}

void phuong_tien::lay_ma_xe() const{
	return ma_xe;
}

string phuongtien::lay_loai_xe() const{
	return loai_xe;
}

string chuanhoaten(string loai){
		string lower = loai;
		if(lower == "car") return "Car";
		if(lower == "motorcycle") return "Motorcycle";
		if(lower == "bicycle") return "Bicycle";
		return loai;


double phuong_tien::tinh_phi(tg_do){
	float phi2hdau, phitiep;
	if(loai_xe == "Car"){
		if(tg_do <= 2){
			if(giovao >= 6 && gio_vao <=9 || gio_vao >= 15 && gio_vao <= 18){
				phi2hdau = tg_do*(6+6*0.3);
			}
			else{
				phi2hdau = tg_do*(6-6*0.05);
			}
		}
		else{
			phisau = (tg_do - 2) * (6-6*0.1);
		}	
	}
	
	if(loai_xe == "Motorcycle"){
		if(tg_do <= 2){
			if(giovao >= 6 && gio_vao <=9 || gio_vao >= 15 && gio_vao <= 18){
				phi2hdau = tg_do*(4+4*0.3);
			}
			else{
				phi2hdau = tg_do*(4-4*0.05);
			}
		}
		else{
			phisau = (tg_do - 2) * (4-4*0.1);
		}	
	}
	
	if(loai_xe == "Cycle"){
		if(tg_do <= 2){
			if(giovao >= 6 && gio_vao <=9 || gio_vao >= 15 && gio_vao <= 18){
				phi2hdau = tg_do*(2+2*0.3);
			}
			else{
				phi2hdau = tg_do*(2-2*0.05);
			}
		}
		else{
			phisau = (tg_do - 2) * (2-2*0.1);
		}	
	}
	
	return phi2hdau + phisau;
}

void phuong_tien::hien_thi(){
	double phi = tinh_phi(tg_do)
	cout<<"Ma phuong tien"<<ma_xe<<endl;
	cout<<"Loai phuong tien"<<loai_xe<<endl;
	cout<<"Gio vao"<<gio_vao<<endl;
	cout<<"Thoi gian do xe"<<tg_do<<endl;
	cout<<"Phi do xe"<<phi<<" VND"<<endl;
}


class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    phuong_tien pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
};

bai_xe::bai_xe(){
	ma_bai = 0;
	kich_thuoc = "";
	co1 = false;
	co2 = false;
	co3 = false;
}

bai_xe::bai_xe(int ma, char kt){
	ma = ma_bai;
	kt = kich_thuoc;
	co1 = false;
	co2 = false;
	co3 = false;
}

int bai_xe::lay_ma() const{
	return ma_xe;
}

bool bai_xe::them(phuong_tien v) {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    if (cap >= 1 && !co1) { pt1 = v; co1 = true; return true; }
    if (cap >= 2 && !co2) { pt2 = v; co2 = true; return true; }
    if (cap >= 3 && !co3) { pt3 = v; co3 = true; return true; }
    return false;
}


bool bai_xe::xoa(int ma_xe) {
    if (co1 && pt1.lay_ma_xe() == ma_xe) {
        if (co2) {
            pt1 = pt2;
            if (co3) { pt2 = pt3; co3 = false; }
            else co2 = false;
        } else co1 = false;
        return true;
    }
    if (co2 && pt2.lay_ma_xe() == ma_xe) {
        if (co3) { pt2 = pt3; co3 = false; }
        else co2 = false;
        return true;
    }
    if (co3 && pt3.lay_ma_xe() == ma_xe) {
        co3 = false;
        return true;
    }
    return false;
}


bool bai_xe::chua(int ma_xe) const {
    if (co1 && pt1.lay_ma_xe() == ma_xe) return true;
    if (co2 && pt2.lay_ma_xe() == ma_xe) return true;
    if (co3 && pt3.lay_ma_xe() == ma_xe) return true;
    return false;
}


void bai_xe::hien_thi() const {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    int so_xe = co1 + co2 + co3;
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_xe << "/" << cap << " xe\n";
    if (co1) pt1.hien_thi();
    if (co2) pt2.hien_thi();
    if (co3) pt3.hien_thi();
}


bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    if (co1 && pt1.lay_loai_xe() == loai) { ++dem; tong += pt1.tinh_phi(); }
    if (co2 && pt2.lay_loai_xe() == loai) { ++dem; tong += pt2.tinh_phi(); }
    if (co3 && pt3.lay_loai_xe() == loai) { ++dem; tong += pt3.tinh_phi(); }
    return dem > 0;
}


class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;
    bool co1, co2, co3; 

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface(){
	co1 = false;
	co2 = false;
	co3 = false;
}

bool trungbai(int mabai){
			if(co1 && bai1.lay_ma_bai() == mabai) return true;
			if(co2 && bai2.lay_ma_bai() == mabai) return true;
			if(co3 && bai3.lay_ma_bai() == mabai) return true;
			return false;
		}
		
bool trungphuongtien(int mapt){
		if(co1 && bai1.chua(mapt) == mapt) return true;
		if(co2 && bai2.chua(mapt) == mapt) return true;
		if(co3 && bai3.chua(mapt) == mapt) return true;
		return false;
	}


void SystemInterface::runMenu(){
	int chon;
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        cin >> chon;
	}
	switch(chon){
		case 1:
			if(co1 && co2 && co3){
				cout<<"Da dat gioi han toi da 3 bai xe"<<endl;
			}
			int mabai;
			char kt;
			cout<<"Moi ban nhap ma bai do: ";
			cin>>mabai;
			if(trungbai(mabai)) 
				cout<<"Trung ma bai do xe, vui long nhap lai"<<endl;
			
			cout<<"Moi ban nhap kich thuoc bai: "
			cin>>kt;
			kt = toupper(kt);
			if( kt != 'S' || kt != 'M' || kt != 'L') 
				cout<<"Kich thuoc bai do khong hop le, vui long nhap lai"<<endl;
			
			if(co1 == false){
				bai1 = bai_xe(mabai, kt)
				co1 = true;
			}
			
			else if(co2 == false){
				bai2 = bai_xe(mabai, kt)
				co2 = true;
			}
			
			else if(co3 == false){
				bai3 = bai_xe(mabai, kt)
				co3 = true;
			}
			
			cout<<"Tao bai do thanh cong"<<endl;
			break;
		
		case 2:
			if(!co1 && !co2 && !co3)
				cout<<"Chua co bai xe nao, vui long tao bai do"<<endl;
				
			int mapt, gio_vao, tg_do;
	}
}
