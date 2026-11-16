#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

class phuong_tien{
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

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg){
	ma_xe = ma;
	loai_xe = loai;
	gio_vao = gio;
	tg_do = tg;
}

int phuong_tien::lay_ma_xe() const{
	return ma_xe;
}

string phuong_tien::lay_loai_xe() const{
	return loai_xe;
}

string chuanhoaten(string loai){
		string lower = loai;
		if(lower == "car") return "Car";
		if(lower == "motorcycle") return "Motorcycle";
		if(lower == "bicycle") return "Bicycle";
		return loai;
	}


double phuong_tien::tinh_phi()const{
	    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else       tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi()const{
	double phi = tinh_phi();
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
    static const int xetoida = 3;
    phuong_tien phuongtien[xetoida];
    int demphuongtienhientai;
    int suc_chua() const;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma_bai() const;
    int lay_dem()const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
};

bai_xe::bai_xe(){
	ma_bai = 0;
	kich_thuoc = 'S';
	demphuongtienhientai = 0;
}

bai_xe::bai_xe(int ma, char kt){
	ma = ma_bai;
	kt = kich_thuoc;
	demphuongtienhientai = 0;
}

int bai_xe::lay_ma_bai() const{
	return ma_bai;
}

int bai_xe::lay_dem()const {
	return demphuongtienhientai;
}

bool bai_xe::them(phuong_tien v) {
    int chuatoida = (kich_thuoc == 'S' ? 1: (kich_thuoc == 'M' ? 2 : 3));
    if(demphuongtienhientai >= chuatoida) return false;
    phuongtien[demphuongtienhientai] = v;
    demphuongtienhientai++;
    return true;
}


bool bai_xe::xoa(int ma_xe) {
    for(int i = 0; i < demphuongtienhientai; i++){
		if(phuongtien[i].lay_ma_xe() == ma_xe){
			phuongtien[i] = phuongtien[i+1];
			demphuongtienhientai--;
		}
		return true;
	}
	return false;
}

int bai_xe::suc_chua() const{
	return (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
}


bool bai_xe::chua(int ma_xe) const {
    for(int i = 0; i < demphuongtienhientai; i++){
		if(phuongtien[i].lay_ma_xe() == ma_xe)
		return true;
	}
    return false;
}


void bai_xe::hien_thi() const {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    int so_xe = demphuongtienhientai;
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_xe << "/" << cap << " xe\n";
    for(int i = 0; i < demphuongtienhientai; i++){
		phuongtien[i].hien_thi();
	}
}


bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    for(int i = 0; i < demphuongtienhientai; i++){
    	if(phuongtien[i].lay_loai_xe() == loai){
    		dem++;
    		tong+=phuongtien[i].tinh_phi();
		}
	}
    return dem > 0;
}


class SystemInterface {
private:
    static const int baitoida = 10;
    bai_xe baixe[baitoida];
    int dembaidohientai;
    
    int timbai(int ma) const;
    int timxe(int ma) const;

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface(){
	dembaidohientai = 0;
}

int SystemInterface::timbai(int ma) const{
	for(int i = 0; i<dembaidohientai; i++)
		if(baixe[i].lay_ma_bai() == ma) return i;
	return -1;
}

int SystemInterface::timxe(int ma) const{
	for(int i = 0; i<dembaidohientai; i++)
		if(baixe[i].chua(ma)) return i;
	return -1;
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
        
        switch(chon){
		case 1:
			{
				int ma; char kt;
	            if(dembaidohientai >= baitoida){
	            	cout<<"He thong da dat gioi han"<<endl;
	            	break;
				}
				cout << "Ma bai: "; cin >> ma;
				
				if(timbai(ma) != -1){
					cout<<"Ma bai da ton tai"<<endl;
					break;
				}
	            cout << "Kich thuoc (S/M/L): "; cin >> kt;
	            kt = (char)toupper((unsigned char) kt);
	            if(kt!='S' && kt!='M' && kt!='L'){
	            	cout<<"Kich thuoc khong hop le";
	            	break;
				}
	            	baixe[dembaidohientai] = bai_xe(ma, kt);
	            	dembaidohientai++;
	            	cout << "Da tao bai " << ma << "\n";
	            	break;
			}
            break;
		
		case 2:
			{
				int ma, gio, tg; string loai;
				int demphuongtienhientai = baixe[baitoida].lay_dem();
				
				if(demphuongtienhientai >= 3){
	            	cout<<"He thong da dat gioi han"<<endl;
	            	return;
	    		}
	    		
	            cout << "Ma xe: "; cin >> ma;
	            if(timxe(ma) != -1){
	            	cout<<"Ma xe da ton tai"<<endl;
					break;
				}
				
	            cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai;
	            loai = chuanhoaten(loai);
	            
	            if(loai == ""){
	            	cout<<"Loai xe khong hop le"<<endl;
	            	break;
				}
				
	            cout << "Gio vao (0-23): "; cin >> gio;
	            cout << "Thoi luong (1-23): "; cin >> tg;
	            if(gio < 0 || gio > 23 || tg < 1 || tg > 23){
	            	cout<<"Gio vao hoac thoi luong khong hop le"<<endl;
	            	break;
				}
	            phuong_tien phuongtien(ma, loai, gio, tg);
	            bool ok = false;
	            for(int i = 0; i < dembaidohientai && !ok; i++){
	            	ok = baixe[i].them(phuongtien);
	            	if(ok) cout<<"Da them xe "<<ma<<"| Phi: $"<<fixed<<setprecision(2)<<phuongtien.tinh_phi()<<"\n";
	            	else cout<<"Tat ca cac bai da day"<<endl;
	            	break;
				}
			}
			
            break;
	        
		case 3:
			{
				int ma;
	            cout << "Ma bai can xoa: "; cin >> ma;
	            int vt = timbai(ma);
	            if(vt == -1){
	            	cout<<"Khong tim thay bai "<<ma<<"\n";
	            	break;
				}
	            for(int j = vt; j<dembaidohientai-1; j++)
	            	baixe[j] = baixe[j+1];
	            dembaidohientai--;
				cout<<"Da xoa bai "<<ma<<"\n";
				break;
			}
        case 4:
        	{
	        	int ma;
	            cout << "Ma xe can lay ra: "; cin >> ma;
	            bool ok = false;
	            for(int i = 0; i<dembaidohientai; i++){
	            	if(baixe[i].chua(ma)){
	            		baixe[i].xoa(ma);
	            		ok = true;
					}
				}
	            cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
			}
        	
            break;
        case 5:
        	{
        		if(dembaidohientai == 0)
        		cout<<"Chua co bai do nao"<<endl;
	        	for(int i = 0; i<dembaidohientai; i++){
	        		baixe[i].hien_thi();
				}
			}
        	
        	break;
        case 6:
        	{
	        	int ma;
	            cout << "Ma bai: "; cin >> ma;
	            int vt = timbai(ma);
	            if(vt != -1) baixe[vt].hien_thi();
	            else cout<<"Khong tim thay bai "<<ma<<endl;
	            break;
			}
            break;
        case 7:
        	{
	        	string loai;
	            cout << "Loai xe: "; cin >> loai;
	            loai = chuanhoaten(loai);
	            int dem; double tong;
	            bool timthay = false;
	            for(int i = 0; i<dembaidohientai; i++){
	            	if(baixe[i].co_loai(loai, dem, tong)){
	            		baixe[i].hien_thi();
	            		timthay = true;
					}	
				}
				if(!timthay) cout<<"Khong co xe loai "<<loai<<endl;
				break;
			}
            break;
        case 8:
        	{
        		int demphuongtienhientai = baixe[baitoida].lay_dem();
	        	string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
	            for (int t = 0; t < 3; ++t) {
	                int dem = 0; double tong = 0;
	                int d; double s;
	                for(int i = 0; i<dembaidohientai; i++){
	                	if(baixe[i].co_loai(loai_arr[i], dem, tong)){
	                		dem+=d;
	                		tong+=s;
						}
					}
	                cout << loai_arr[t] << ": ";
	                if (dem == 0) cout << "khong co xe\n";
	                else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
	            }
			}
        	
            break;
        case 9:
        	cout<<"Dang thoat chuong trinh..."<<endl;
        	break;
        default:
        	cout<<"Lua chon khong hop le"<<endl;
        	break;
		}
	}
	
}

int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
