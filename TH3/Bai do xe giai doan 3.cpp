#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <limits>

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

phuong_tien::phuong_tien() {
    ma_xe = 0;
    loai_xe = "";
    gio_vao = 0;
    tg_do = 0;
}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg) {
    ma_xe = ma;
    loai_xe = loai;
    gio_vao = gio;
    tg_do = tg;
}

int phuong_tien::lay_ma_xe() const {
    return ma_xe;
}

string phuong_tien::lay_loai_xe() const {
    return loai_xe;
}

string chuanhoaten(string loai) {
    for (char& c : loai) {
        c = (char)tolower((unsigned char)c);
    }
    if (loai == "car") return "Car";
    if (loai == "motorcycle") return "Motorcycle";
    if (loai == "bicycle") return "Bicycle";
    return "";
}

double phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else       tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi() const {
    double phi = tinh_phi();
    cout << "  Ma phuong tien: " << ma_xe << endl;
    cout << "  Loai phuong tien: " << loai_xe << endl;
    cout << "  Gio vao: " << gio_vao << endl;
    cout << "  Thoi gian do xe: " << tg_do << endl;
    cout << "  Phi do xe: " << fixed << setprecision(2) << phi << " VND" << endl;
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    int succhua;
    int demphuongtienhientai;
    phuong_tien** phuongtien;

    void saochepsau(const bai_xe& other) {
        ma_bai = other.ma_bai;
        kich_thuoc = other.kich_thuoc;
        succhua = other.succhua;
        demphuongtienhientai = other.demphuongtienhientai;
        phuongtien = new phuong_tien*[succhua];
        for (int i = 0; i < succhua; i++) {
            if (i < demphuongtienhientai && other.phuongtien[i] != nullptr) {
                phuongtien[i] = new phuong_tien(*(other.phuongtien[i]));
            } else {
                phuongtien[i] = nullptr;
            }
        }
    }

    void giaiphongbonho() {
        if (phuongtien != nullptr) {
            for (int i = 0; i < succhua; i++) {
                if (phuongtien[i] != nullptr) {
                    delete phuongtien[i];
                    phuongtien[i] = nullptr;
                }
            }
            delete[] phuongtien;
            phuongtien = nullptr;
        }
    }

public:
    bai_xe();
    bai_xe(int ma, char kt);
    ~bai_xe();
    bai_xe(const bai_xe& other);
    bai_xe& operator=(const bai_xe& other);

    int lay_ma_bai() const;
    int lay_dem() const;
    int lay_suc_chua() const;
    int timchiso(int ma_phuongtien) const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
    void timtheoloai(string loai, bool& tim) const;
};

bai_xe::bai_xe() {
    ma_bai = -1;
    kich_thuoc = 'S';
    succhua = 1;
    demphuongtienhientai = 0;
    phuongtien = new phuong_tien*[succhua];
    phuongtien[0] = nullptr;
}

bai_xe::bai_xe(int ma, char kt) {
    ma_bai = ma;
    kich_thuoc = (char)toupper((unsigned char)kt);
    if (kich_thuoc == 'S') succhua = 1;
    else if (kich_thuoc == 'M') succhua = 2;
    else succhua = 3;
    demphuongtienhientai = 0;
    phuongtien = new phuong_tien*[succhua];
    for (int i = 0; i < succhua; i++) {
        phuongtien[i] = nullptr;
    }
}

bai_xe::~bai_xe() {
    giaiphongbonho();
}

bai_xe::bai_xe(const bai_xe& other) {
    phuongtien = nullptr;
    saochepsau(other);
}

bai_xe& bai_xe::operator=(const bai_xe& other) {
    if (this != &other) {
        giaiphongbonho();
        saochepsau(other);
    }
    return *this;
}

int bai_xe::lay_ma_bai() const {
    return ma_bai;
}

int bai_xe::lay_dem() const {
    return demphuongtienhientai;
}

int bai_xe::lay_suc_chua() const {
    return succhua;
}

int bai_xe::timchiso(int ma_phuongtien) const {
    for (int i = 0; i < demphuongtienhientai; i++) {
        if (phuongtien[i] != nullptr && phuongtien[i]->lay_ma_xe() == ma_phuongtien) {
            return i;
        }
    }
    return -1;
}

bool bai_xe::them(phuong_tien v) {
    if (demphuongtienhientai >= succhua) {
        return false; // Bai da day
    }
    phuongtien[demphuongtienhientai] = new phuong_tien(v);
    demphuongtienhientai++;
    return true;
}

bool bai_xe::xoa(int ma_xe) {
    int chiso = timchiso(ma_xe);
    if (chiso == -1) return false;

    delete phuongtien[chiso];
    phuongtien[chiso] = nullptr;

    for (int i = chiso; i < demphuongtienhientai - 1; i++) {
        phuongtien[i] = phuongtien[i + 1];
        phuongtien[i + 1] = nullptr;
    }
    phuongtien[demphuongtienhientai - 1] = nullptr;
    demphuongtienhientai--;
    return true;
}

bool bai_xe::chua(int ma_xe) const {
    return timchiso(ma_xe) != -1;
}

void bai_xe::hien_thi() const {
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << demphuongtienhientai << "/" << succhua << " xe\n";
    for (int i = 0; i < demphuongtienhientai; i++) {
        phuongtien[i]->hien_thi();
    }
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    bool tim_thay = false;
    for (int i = 0; i < demphuongtienhientai; i++) {
        if (phuongtien[i] != nullptr && phuongtien[i]->lay_loai_xe() == loai) {
            tong += phuongtien[i]->tinh_phi();
            dem++;
            tim_thay = true;
        }
    }
    return tim_thay;
}

void bai_xe::timtheoloai(string loai, bool& tim) const {
    for (int i = 0; i < demphuongtienhientai; i++) {
        if (phuongtien[i] != nullptr && phuongtien[i]->lay_loai_xe() == loai) {
            cout << "  - Tim thay tai Bai ma: " << ma_bai << "\n";
            phuongtien[i]->hien_thi();
            tim = true;
        }
    }
}

class SystemInterface {
private:
    int succhuabai;
    int dembaidohientai;
    bai_xe** baixe;

    void saochepsau(const SystemInterface& other) {
        succhuabai = other.succhuabai;
        dembaidohientai = other.dembaidohientai;
        baixe = new bai_xe*[succhuabai];
        for (int i = 0; i < succhuabai; i++) {
            if (i < dembaidohientai && other.baixe[i] != nullptr) {
                baixe[i] = new bai_xe(*(other.baixe[i]));
            } else {
                baixe[i] = nullptr;
            }
        }
    }

    void giaiphongbonho() {
        if (baixe != nullptr) {
            for (int i = 0; i < succhuabai; i++) {
                if (baixe[i] != nullptr) {
                    delete baixe[i];
                    baixe[i] = nullptr;
                }
            }
            delete[] baixe;
            baixe = nullptr;
        }
    }

    bool timbai(int mabai) const;
    bool timxe(int maxe) const;
    int timchisobaitheomabai(int mabai) const;

public:
    SystemInterface();
    ~SystemInterface();
    SystemInterface(const SystemInterface& other);
    SystemInterface& operator=(const SystemInterface& other);
    void succhuabaimoi(int succhuabaimoi);
    void runMenu();
};

SystemInterface::SystemInterface() {
    succhuabai = 5;
    dembaidohientai = 0;
    baixe = new bai_xe*[succhuabai];
    for (int i = 0; i < succhuabai; i++) {
        baixe[i] = nullptr;
    }
}

bool SystemInterface::timbai(int mabai) const {
    for (int i = 0; i < dembaidohientai; i++)
        if (baixe[i] != nullptr && baixe[i]->lay_ma_bai() == mabai) return true;
    return false;
}

bool SystemInterface::timxe(int maxe) const {
    for (int i = 0; i < dembaidohientai; i++)
        if (baixe[i] != nullptr && baixe[i]->chua(maxe)) return true;
    return false;
}

int SystemInterface::timchisobaitheomabai(int mabai) const {
    for (int i = 0; i < dembaidohientai; i++)
        if (baixe[i] != nullptr && baixe[i]->lay_ma_bai() == mabai) return i;
    return -1;
}

SystemInterface::~SystemInterface() {
    giaiphongbonho();
}

SystemInterface::SystemInterface(const SystemInterface& other) {
    baixe = nullptr;
    saochepsau(other);
}

SystemInterface& SystemInterface::operator=(const SystemInterface& other) {
    if (this != &other) {
        giaiphongbonho();
        saochepsau(other);
    }
    return *this;
}

void SystemInterface::succhuabaimoi(int succhuabaimoi) {
    if (succhuabaimoi <= succhuabai) return;
    bai_xe** baimoi = new bai_xe*[succhuabaimoi];
    for (int i = 0; i < succhuabaimoi; i++) {
        baimoi[i] = nullptr;
    }
    for (int i = 0; i < dembaidohientai; i++) {
        baimoi[i] = baixe[i];
    }
    delete[] baixe;
    baixe = baimoi;
    succhuabai = succhuabaimoi;
}

void SystemInterface::runMenu() {
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

        if (!(cin >> chon)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Vui long nhap so!\n";
            continue;
        }

        switch (chon) {
        case 1: {
            int ma;
            char kt;
            if (dembaidohientai >= succhuabai) {
                succhuabaimoi(succhuabai * 2);
            }
            cout << "Ma bai: ";
            cin >> ma;

            if (timbai(ma)) {
                cout << "Ma bai da ton tai" << endl;
                break;
            }
            cout << "Kich thuoc (S/M/L): ";
            cin >> kt;
            kt = (char)toupper((unsigned char)kt);
            if (kt != 'S' && kt != 'M' && kt != 'L') {
                cout << "Kich thuoc khong hop le\n";
                break;
            }
            baixe[dembaidohientai] = new bai_xe(ma, kt);
            dembaidohientai++;
            cout << "Da tao bai " << ma << "\n";
            break;
        }

        case 2: {
            int ma, gio, tg;
            string loai;

            if (dembaidohientai == 0) {
                cout << "Chua co bai xe nao. Vui long tao bai xe truoc\n";
                break;
            }

            cout << "Ma xe: ";
            cin >> ma;
            if (timxe(ma)) {
                cout << "Ma xe da ton tai" << endl;
                break;
            }

            cout << "Loai (Car/Motorcycle/Bicycle): ";
            cin >> loai;
            loai = chuanhoaten(loai);

            if (loai == "") {
                cout << "Loai xe khong hop le" << endl;
                break;
            }

            cout << "Gio vao (0-23): ";
            cin >> gio;
            if (gio < 0 || gio > 23) {
                cout << "Gio vao khong hop le\n";
                break;
            }
            cout << "Thoi luong (1-23): ";
            cin >> tg;
            if (tg < 1 || tg > 23) {
                cout << "Thoi luong khong hop le" << endl;
                break;
            }
            phuong_tien pt(ma, loai, gio, tg);

            bool da_them = false;
            for (int i = 0; i < dembaidohientai; i++) {
                if (baixe[i]->them(pt)) {
                    cout << "Them xe thanh cong vao bai co ma: " << baixe[i]->lay_ma_bai() << "\n";
                    da_them = true;
                    break;
                }
            }
            if (!da_them) {
                cout << "Tat ca bai do xe deu da day!\n";
            }
            break;
        }

        case 3: {
            int ma;
            if (dembaidohientai == 0) {
                cout << "Khong co bai do xe nao\n";
                break;
            }
            cout << "Ma bai can xoa: ";
            cin >> ma;
            int vt = timchisobaitheomabai(ma);
            if (vt == -1) {
                cout << "Khong tim thay bai " << ma << "\n";
                break;
            }
            if (baixe[vt]->lay_dem() > 0) {
                cout << "Khong the xoa bai do vi con xe ben trong\n";
                break;
            }

            delete baixe[vt];
            baixe[vt] = nullptr;
            for (int j = vt; j < dembaidohientai - 1; j++) {
                baixe[j] = baixe[j + 1];
                baixe[j + 1] = nullptr;
            }
            baixe[dembaidohientai - 1] = nullptr;
            dembaidohientai--;
            cout << "Da xoa bai " << ma << "\n";
            break;
        }

        case 4: {
            int ma;
            if (dembaidohientai == 0) {
                cout << "Khong co bai do nao trong he thong\n";
                break;
            }
            cout << "Ma xe can lay ra: ";
            cin >> ma;
            bool ok = false;
            for (int i = 0; i < dembaidohientai; i++) {
                if (baixe[i] != nullptr && baixe[i]->chua(ma)) {
                    baixe[i]->xoa(ma);
                    ok = true;
                    break;
                }
            }
            cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
            break;
        }

        case 5: {
            if (dembaidohientai == 0)
                cout << "Chua co bai do nao" << endl;
            for (int i = 0; i < dembaidohientai; i++) {
                if (baixe[i] != nullptr) {
                    baixe[i]->hien_thi();
                }
            }
            break;
        }

        case 6: {
            int ma;
            if (dembaidohientai == 0) {
                cout << "Chua co bai do xe nao\n";
                break;
            }
            cout << "Ma bai: ";
            cin >> ma;
            int vt = timchisobaitheomabai(ma);
            if (vt != -1 && baixe[vt] != nullptr) {
                baixe[vt]->hien_thi();
            } else {
                cout << "Khong tim thay bai " << ma << endl;
            }
            break;
        }

        case 7: {
            string loai;
            if (dembaidohientai == 0) {
                cout << "Chua co bai do xe nao\n";
                break;
            }
            cout << "Loai xe: ";
            cin >> loai;
            loai = chuanhoaten(loai);
            if (loai == "") {
                cout << "Loai xe khong hop le\n";
                break;
            }
            bool timthay = false;
            for (int i = 0; i < dembaidohientai; i++) {
                if (baixe[i] != nullptr) {
                    baixe[i]->timtheoloai(loai, timthay);
                }
            }
            if (!timthay) cout << "Khong co xe loai " << loai << endl;
            break;
        }

        case 8: {
            string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
            for (int t = 0; t < 3; ++t) {
                int dem = 0;
                double tong = 0;
                for (int i = 0; i < dembaidohientai; i++) {
                    if (baixe[i] != nullptr) {
                        baixe[i]->co_loai(loai_arr[t], dem, tong);
                    }
                }
                cout << loai_arr[t] << ": ";
                if (dem == 0) cout << "khong co xe\n";
                else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
            }
            break;
        }

        case 9:
            cout << "Dang thoat chuong trinh..." << endl;
            return;

        default:
            cout << "Lua chon khong hop le" << endl;
            break;
        }
    }
}

int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
